#include "precompiler.h"
#include "../ext/exprtk/exprtk.h"


namespace os
{


void Precompiler::PrintError(LPCSTR msg)
{
	_ErrorCount++;
	_LOG_ERROR(_SourceCodeFilename<<": error: "<<msg);
}

void Precompiler::PrintWarning(LPCSTR msg)
{
	_WarningCount++; 
	if(!_SuppressWarnings)
	{	_LOG_WARNING(_SourceCodeFilename<<": warning: "<<msg);
	}
}

void Precompiler::SetWarningLevel(int l)
{
	switch(l)
	{
		case 0: _SuppressWarnings = true; break;
		case 1: _SuppressWarnings = false; break;
	}
}

void Precompiler::Compile(LPCSTR filename, const rt::String_Ref& source_in)
{
	_SourceCodeFilename = filename;
	_SourceCodeFilename.NormalizePathSeparator('/');

	_ErrorCount = 0;
	_WarningCount = 0;

	_Compiled.clear();
	_MacroSubsituted.Empty();

	os::File::ResolveRelativePath(filename, _Root);
	_Root.NormalizePathSeparator('/');

	rt::String str;
	rt::String_Ref source;
	if(source_in.IsEmpty())
	{
		if(!_LoadFile(_Root, str))
		{	PrintError("failed to load the source code");
			return;
		}
		source = str;
	}
	else
	{	source = source_in;
	}

	_Compile(_Root, source);

	t_Codes::const_iterator it = _Compiled.find(_Root);
	if(it != _Compiled.end())
	{
		_SubsituteFile(it->second->Content, _MacroSubsituted);
	}
}

static const rt::SS _if("#if");
static const rt::SS _elif("#elif");
static const rt::SS _else("#else");
static const rt::SS _endif("#endif");
static const rt::CharacterSet_ControlChar _directive_sep(" \t");

bool Precompiler::_IsMacroBranchCloseDirective(const rt::String_Ref& directive)
{
	return directive == _elif || directive == _else || directive == _endif;
}

bool Precompiler::_IsMacroBranchOpenDirective(const rt::String_Ref& directive)
{
	return directive == _elif || directive == _else || directive.StartsWith(_if);
}

bool Precompiler::_EvalueMacroIf(const rt::String_Ref& directive, const rt::String_Ref& expr, bool& result)
{
	ASSERT(_IsMacroBranchOpenDirective(directive));

	static const rt::SS _ifdef("#ifdef");
	static const rt::SS _ifndef("#ifndef");

	if(directive == _ifdef)
	{	result = IsMacroDefined(expr);
		return true;
	}
	else if(directive == _ifndef)
	{	result = !IsMacroDefined(expr);
		return true;
	}
	else if(directive == _else)
	{	result = true;
		return true;
	}
	else if(directive == _if || directive == _elif)
	{	// #if, or #elif
		rt::String_Ref vars[1024];
		static rt::CharacterSet ops("()-=+!~:/?*&^%<> \t\r\n");
		UINT co = expr.Split<true>(vars, sizeofArray(vars)-1, ops);
		vars[co] = rt::String_Ref(expr.End(), expr.End());

		rt::String translated = rt::String_Ref(expr.Begin(), vars[0].Begin());

		for(UINT i=0; i<co; i++)
		{
			if(vars[i] == rt::SS("defined"))
			{	
				if(i+1==co)
				{
					PrintError("defined() expression missing argument");
					return false;
				}

				i++;

				translated += IsMacroDefined(vars[i])?" true ":" false ";
				auto op = rt::String_Ref(vars[i].End(), vars[i+1].Begin()).TrimSpace();
				if(op.IsEmpty() || op[0] != ')')
				{	
					PrintError("')' is missing in defined() expression");
					return false;
				}
				translated += op.SubStr(1);
				continue;
			}
			else
			{
				_SubsituteMacrosInline(vars[i], translated);
				translated += rt::String_Ref(vars[i].End(), vars[i+1].Begin()).TrimSpace();
			}
		}

		translated.Replace('"', '\'');

		ext::Expression<float> eval;
		if(eval.Compile(translated))
		{
			float r = eval.Evaluate();
			result = r > 0.0000001f || r < -0.0000001f;
			return true;
		}
		else
		{	PrintError(rt::SS("illegal expression: ") + expr + ": " + eval.GetLastError());
			return false;
		}
	}
	else
	{	PrintError(rt::SS("unknown directive: ") + expr);
		return false;
	}
}

bool Precompiler::_SeekToNextCloseDirective(const rt::String_Ref& content, rt::String_Ref& line)
{
	// end of accepted branch, skip all others
	int enclosure_level = 0;
	while(content.GetNextLine(line, true))
	{
		auto directive = line.TrimAfter(_directive_sep).TrimSpace();
		if(directive[0] == '#')
		{
			if(enclosure_level == 0 && _IsMacroBranchCloseDirective(directive))
				return true;

			if(directive.StartsWith(_if))
			{
				enclosure_level++;
			}
			else if(directive == _endif)
			{
				enclosure_level--;
			}
		}
	}

	return false;
}

void Precompiler::_SubsituteFile(const rt::String_Ref& content, rt::String& output)
{
	static const rt::SS _define("#define");
	static const rt::SS _undefine("#undef");

	output.SetLength(content.GetLength());
	output.Empty();
	
	rt::String_Ref line;
	int branch_level = 0;

	while(content.GetNextLine(line, false))
	{
		rt::String_Ref control_line = line.TrimSpace();
		if(control_line[0] == '#')
		{
			rt::String_Ref f[3];
			UINT co = control_line.Split<true, '\x0', '\x0'>(f,3,_directive_sep);

			// #define
			if(f[0] == _define)
			{	
				SSIZE_T func = f[1].FindCharacter('(');
				if(func > 0)
				{	// macro function
					SSIZE_T arg_start = (1 + func + f[1].Begin() - control_line.Begin());
					SSIZE_T arg_end = control_line.FindCharacter(')', arg_start);

					rt::String_Ref arg(&control_line[arg_start], &control_line[arg_end]);
					rt::String_Ref macro_name = f[1].SubStrHead(func);

					_DefineMacroFunction(macro_name, rt::String_Ref(&control_line[arg_end+1], control_line.End()).TrimSpace(), arg);
				}
				else
				{
					if(co == 3){ _DefineMacro(f[1], rt::String_Ref(f[2].Begin(), control_line.End())); }
					else{ _DefineMacro(f[1], nullptr); }
				}

				continue;
			}
			// #undef
			else if(f[0] == _undefine && co == 2)
			{	
				_UndefineMacro(f[1]);
				continue;
			}
			else if(f[0].StartsWith(_if))
			{
				for(;;)
				{	// iterate all branches
					bool go_if = false;
					if(!_EvalueMacroIf(f[0], co>1?rt::String_Ref(f[1].Begin(), control_line.End()):nullptr, go_if))
					{
						PrintError(rt::SS("illegal directive: ") + control_line);
						//_if_entered.last() = true;
					}
				
					if(go_if)
					{	// enter a new branch
						branch_level ++;
						break;
					}
					else
					{	// seek to next _IsMacroBranchCloseDirective
						if(_SeekToNextCloseDirective(content, line))
						{	
							control_line = line.TrimSpace();
							co = control_line.Split<true, '\x0', '\x0'>(f,3,_directive_sep);
							if(f[0] == _endif)break;
						}
						else
						{	PrintError(rt::SS("no matching #endif is found for ") + f[0]);
							break;
						}
					}
				}

				continue;
			}
			else if(_IsMacroBranchCloseDirective(f[0]))
			{
				while(f[0] != _endif)
				{	// skip all remaining branches
					if(_SeekToNextCloseDirective(content, line))
					{	co = line.TrimSpace().Split<true, '\x0', '\x0'>(f,3,_directive_sep);
						if(f[0] == _endif)break;
					}
					else
					{	PrintError(rt::SS("no matching #endif found"));
						break;
					}
				}

				if(branch_level>0)branch_level ++;
				else
					PrintError(f[0] + " is not matched with #if");

				continue;
			}
		}

		_SubsituteMacrosInline(line, output);
		output += '\r';
		output += '\n';
	}
}

bool Precompiler::_GetFirstToken(const rt::String_Ref& content, rt::String_Ref& token)
{
	static const rt::CharacterSet_Symbol token_charset;
	static const rt::CharacterSet_Alphabet token_charset_init("_");

	LPCSTR start = content.Begin();
	LPCSTR tail = content.End();

TRY_NEXT_TOKEN:
	if(_MacroPrefix.IsEmpty())
	{
		while(!token_charset_init.Has(*start))
		{	if(start<tail){	start++; }
			else return false;
		}
	}
	else
	{	
		LPCSTR end = content.End() - _MacroPrefix.GetLength() - 1;
		if(end - start < (SSIZE_T)_MacroPrefix.GetLength())return false;

		while(memcmp(start, _MacroPrefix.Begin(), _MacroPrefix.GetLength()) || !token_charset_init.Has(start[_MacroPrefix.GetLength()]))
		{	if(start<end){	start++; }
			else return false;
		}

		start += _MacroPrefix.GetLength();
	}

	LPCSTR token_end = start+1;
	while(token_charset.Has(*token_end) && token_end<tail)
		token_end++;

	if(!_MacroSuffix.IsEmpty() && *token_end != '(')
	{
		if(memcmp(token_end, _MacroSuffix.Begin(), _MacroSuffix.GetLength()))
		{
			start = token_end;
			goto TRY_NEXT_TOKEN;
		}
	}

	token = rt::String_Ref(start, token_end);
	return true;
}

void Precompiler::_SubsituteMacrosInline(const rt::String_Ref& content, rt::String& output)
{
	const rt::String* val = nullptr;

	if(content.IsEmpty())return;
	
	rt::String_Ref token;
	LPCSTR last_token_end = content.Begin();
	while(_GetFirstToken(rt::String_Ref(last_token_end, content.End()), token))
	{
		output += rt::String_Ref(last_token_end, token.Begin() - _MacroPrefix.GetLength());

		t_MacroTable::const_iterator it;
		if((it = _Macros.find(token)) != _Macros.end())
		{	
			bool is_token_as_func = !_MacroSuffix.IsEmpty() && *token.End() == '(';

			if(it->second.ArgmentCount == -1 && !is_token_as_func)
			{
				if(!_MacroConnectOp.IsEmpty() && output.EndsWith(_MacroConnectOp))
					output.SetLength(output.GetLength() - _MacroConnectOp.GetLength());

				_SubsituteMacrosInline(it->second.Value, output);
				last_token_end = token.End() + _MacroSuffix.GetLength();

				if(!_MacroConnectOp.IsEmpty() && rt::String_Ref(last_token_end, _MacroConnectOp.GetLength()) == _MacroConnectOp)
					last_token_end += _MacroConnectOp.GetLength();
			}
			else
			{	// Macro function
				if(!_MacroConnectOp.IsEmpty() && output.EndsWith(_MacroConnectOp))
					output.SetLength(output.GetLength() - _MacroConnectOp.GetLength());

				LPCSTR p = token.End();
				while(p<content.End())
					if(*p == '(')break;
				if(*p != '(')
				{
					PrintWarning(rt::SS("'(' is expected after macro function \"") + token + '"');
					goto UNMATCHED_TOKEN;
				}
				LPCSTR func_begin = p;
				int closure = 1;
				for(p++;p < content.End();p++)
				{	if(*p == '(')closure++;
					else if(*p == ')')
					{	if(!(--closure))break;
					}
				}
				if(p == content.End())
				{
					PrintWarning(rt::SS("')' is missing when parsing macro function \"") + token + '"');
					goto UNMATCHED_TOKEN;
				}
				ASSERT(*p == ')');

				if(!_MacroSuffix.IsEmpty() && memcmp(_MacroSuffix.Begin(), p+1, _MacroSuffix.GetLength()))
				{
					PrintWarning(rt::SS("\"") + _MacroSuffix + "\" is missing when parsing macro function \"" + token + '"');
					goto UNMATCHED_TOKEN;
				}

				rt::String_Ref arg[256];
				UINT co = rt::String_Ref(func_begin+1, p).Split(arg, 256, ',');

				if(co == it->second.ArgmentCount)
				{
					{	LPCSTR begin = it->second.Value.Begin();
						LPCSTR p = begin;
						LPCSTR end = it->second.Value.End();
						while(p<end)
						{
							while(*p != '\x1' && p<end)p++;
							if(p>begin)_SubsituteMacrosInline(rt::String_Ref(begin, p), output);
							if(p == end)break;
							UINT idx = p[1];
							if(idx < co)
								_SubsituteMacrosInline(arg[idx], output);
							p += 2;
							begin = p;
						}
					}

					last_token_end = p + 1 + _MacroSuffix.GetLength();

					if(!_MacroConnectOp.IsEmpty() && rt::String_Ref(last_token_end, _MacroConnectOp.GetLength()) == _MacroConnectOp)
						last_token_end += _MacroConnectOp.GetLength();

					continue;
				}
				else
				{	PrintError(rt::SS("macro function \"") + token + "\" expects " + it->second.ArgmentCount + " argments, but " + co + " provided");
					goto UNMATCHED_TOKEN;
				}
			}

			continue;
		}
		else if(_pPredefined && ((val = _pPredefined->Get(token))))
		{	
			if(!_MacroConnectOp.IsEmpty() && output.EndsWith(_MacroConnectOp))
				output.SetLength(output.GetLength() - _MacroConnectOp.GetLength());
			
			_SubsituteMacrosInline(*val, output);
			last_token_end = token.End() + _MacroSuffix.GetLength();

			if(!_MacroConnectOp.IsEmpty() && rt::String_Ref(last_token_end, _MacroConnectOp.GetLength()) == _MacroConnectOp)
				last_token_end += _MacroConnectOp.GetLength();

			continue;
		}

UNMATCHED_TOKEN:
		output += token;
		last_token_end = token.End() + _MacroSuffix.GetLength();
	}

	output += rt::String_Ref(last_token_end, content.End());
}

const rt::String_Ref& Precompiler::GetCompiled() const
{
	return _MacroSubsituted;
}

void Precompiler::SetEnvVars(const PrecompilerPredefinedMacros* pv)
{
	_pPredefined = pv;
}

Precompiler::Precompiler(const rt::String_Ref& macro_prefix, const rt::String_Ref& macro_suffix, const rt::String_Ref& macro_connect)
	:_MacroPrefix(macro_prefix)
	,_MacroSuffix(macro_suffix)
	,_MacroConnectOp(macro_connect)
{
	ASSERT(	(!_MacroPrefix.IsEmpty() && !_MacroSuffix.IsEmpty()) ||
			(_MacroPrefix.IsEmpty() && _MacroSuffix.IsEmpty())
	);

	_ErrorCount = 0;
	_WarningCount = 0;
	_SuppressWarnings = false;
	_pFileLoader = nullptr;
	_FileLoaderAllowFallback = true;

	_pPredefined = nullptr;
}

void Precompiler::SetIncludeSearchDirectories(const rt::String_Ref& dirs)
{
	rt::String_Ref paths[1024];
	UINT co = dirs.Split<true>(paths, sizeofArray(paths), ";|");

	_LoadFileSearchDirs.SetSize();

	for(UINT i=0; i<co; i++)
	{
		paths[i] = paths[i].TrimSpace();
		if(!paths[i].IsEmpty())
			AddIncludeSearchDirectory(paths[i]);
	}
}

void Precompiler::AddIncludeSearchDirectory(const rt::String_Ref& dir)
{
	ASSERT(!dir.IsEmpty());

	rt::String out;
	os::File::ResolveRelativePath(ALLOCA_C_STRING(dir), out);

	out.NormalizePathSeparator('/');
	if(out.Last() != '/')out += '/';

	_LoadFileSearchDirs.PushUnique(out);
}

void PrecompilerPredefinedMacros::ImportCmdLineOptions(const os::CommandLine& cmd)
{
	for(UINT i=0; i<cmd.GetOptionCount(); i++)
	{	
		rt::String_Ref name = cmd.GetOptionName(i);
		if(!name.IsEmpty())
			Set(name, cmd.GetOptionValue(i));
	}
}

void PrecompilerPredefinedMacros::Merge(const PrecompilerPredefinedMacros& x)
{
	auto it = x._PredefinedMacros.begin();
	for(; it != x._PredefinedMacros.end(); it++)
		_PredefinedMacros[it->first] = it->second;
}

void PrecompilerPredefinedMacros::Set(const rt::String_Ref& macro, const rt::String_Ref& value)
{
	_PredefinedMacros[macro] = value;
}

void PrecompilerPredefinedMacros::Set(const rt::String_Ref& macro)
{
	_PredefinedMacros[macro] = rt::String_Ref();
}

void PrecompilerPredefinedMacros::Unset(const rt::String_Ref& macro)
{
	_PredefinedMacros.erase(macro);
}

bool PrecompilerPredefinedMacros::IsDefined(const rt::String_Ref& macro) const
{
	return _PredefinedMacros.find(macro) != _PredefinedMacros.end();
}

const rt::String* PrecompilerPredefinedMacros::Get(const rt::String_Ref& macro) const
{
	auto it = _PredefinedMacros.find(macro);
	if(it == _PredefinedMacros.end())return nullptr;
	return &it->second;
}

void PrecompilerPredefinedMacros::Dump() const
{
	auto iter = _PredefinedMacros.begin();
	for(; iter != _PredefinedMacros.end(); iter++)
		_LOG("Macro: "<<iter->first<<" = "<<iter->second);
}

bool Precompiler::_DefineMacroFunction(const rt::String_Ref& macro, const rt::String_Ref& value, const rt::String_Ref& arg)
{
	if(_pPredefined && _pPredefined->IsDefined(macro))
	{
		PrintError(rt::SS("macro \"") + macro + rt::SS("\" has already been defined"));
		return false;
	}

	_macro& m = _Macros[macro];
	if(m.ArgmentCount != -2)
	{
		PrintError(rt::SS("macro function \"") + macro + rt::SS("\" has already been defined"));
		return false;
	}

	rt::String_Ref f[256];
	UINT co = arg.Split(f, 256, ',');

	m.ArgmentCount = co;

	if(co)
	{	rt::String		val = value;
		val.Replace('\x1', '\xff');

		int arg_len_min, arg_len_max;
		arg_len_min = arg_len_max = (int)f[0].GetLength();
		for(UINT i=1;i<co;i++)
		{	f[i] = f[i].TrimSpace();
			arg_len_min = rt::min(arg_len_min, (int)f[i].GetLength());
			arg_len_max = rt::max(arg_len_max, (int)f[i].GetLength());
		}

		static const rt::CharacterSet_Symbol symbol;
		rt::String_Ref token, non_token;
		while(value.GetNextToken(symbol, token, non_token))
		{
			if(((int)token.GetLength()) >= arg_len_min && ((int)token.GetLength()) <= arg_len_max)
				for(UINT i=0;i<co;i++)
					if(token == f[i])
					{	m.Value += '\x1';
						m.Value += (char)i;
						goto TOKEN_MAPPED;
					}
			m.Value += token;
TOKEN_MAPPED:
			m.Value += non_token;
		}
		return true;
	}
	else
	{	m.Value = value;
		return true;
	}
}

bool Precompiler::_DefineMacro(const rt::String_Ref& macro, const rt::String_Ref& value)
{
	if(_pPredefined && _pPredefined->IsDefined(macro))
	{
		PrintError(rt::SS("macro \"") + macro + rt::SS("\" is reserved as predefined macro"));
		return false;
	}

	_macro& m = _Macros[macro];
	if(m.ArgmentCount >= 0)
	{
		PrintError(rt::SS("macro \"") + macro + rt::SS("\" has already been defined as a macro function"));
		return false;
	}

	if(m.ArgmentCount == -1 && m.Value != value)
	{
		PrintError(rt::SS("macro \"") + macro + rt::SS("\" has already been defined as \"") + m.Value + '\"');
		return false;
	}

	m.ArgmentCount = -1;
	m.Value = value;

	return true;
}

void Precompiler::ClearMacros()
{
	_Macros.clear();
}

void Precompiler::DumpMacros() const
{
	if(_pPredefined)
	{
		_pPredefined->Dump();
	}

	auto iter = _Macros.begin();
	for(; iter != _Macros.end(); iter++)
		_LOG("Macro: "<<iter->first<<" = "<<iter->second.Value);
}

bool Precompiler::_UndefineMacro(const rt::String_Ref& key)
{
	if(_pPredefined && _pPredefined->IsDefined(key))
	{
		PrintError(rt::SS("macro \"") + key + rt::SS("\" is a predefined macro"));
		return false;
	}

	t_MacroTable::const_iterator it = _Macros.find(key);
	if(it != _Macros.end())
	{	_Macros.erase(it);
		return true;
	}

	PrintWarning(rt::SS("macro \"") + key + rt::SS("\" is not defined"));
	return false;
}

bool Precompiler::_LoadFile(LPCSTR fn, rt::String& out)
{
	if(_pFileLoader && _pFileLoader->Load(fn, out))
		return true;

	return _FileLoaderAllowFallback && os::File::LoadText(fn, out);
}

void Precompiler::SetFileLoader(FileLoad* f, bool allow_fallback)
{
	_pFileLoader = f;
	if(f)
		_FileLoaderAllowFallback = allow_fallback;
	else
		_FileLoaderAllowFallback = true;
}

int Precompiler::_MergeIncludedFile(const rt::String& import_filename, rt::String& compiled_code)
{
	{	t_Codes::const_iterator it = _Compiled.find(import_filename);
		if(it != _Compiled.end())
		{	
			if(it->second->State & CST_INCLUDE_ONCE)
			{	// do nothing
				//code.Content += rt::SS("/* SKIP: ");
				//code.Content += import_filename;
				//code.Content += rt::SS(" has been included */");
				return 1;
			}
			else if(it->second->State & CST_FINALIZED)
			{	compiled_code += it->second->Content;
				return 1;
			}
			else // error if there is a looped dependency
			{	
				PrintError(rt::SS("looped header dependency detected on file ") + import_filename);
				return -1;
			}
		}
	}

	rt::String str;
	if(_LoadFile(import_filename, str))
	{	
		rt::String_Ref import = _Compile(import_filename, str).TrimSpace();
		if(import.IsEmpty())
		{	PrintWarning(rt::SS("imported nothing from file ") + import_filename);
			//return *(const rt::String*)&rt::String_Ref::EmptyString();
		}
		else
			compiled_code += import;

		return 1;
	}
	else
	{	
		return 0;
	}
}

void Precompiler::Empty()
{
	ClearMacros();
	for(auto it = _Compiled.begin(); it != _Compiled.end(); it++)
		_SafeDel(it->second);

	_Compiled.clear();
}

const rt::String_Ref& Precompiler::_Compile(const rt::String_Ref& filename, const rt::String_Ref& source_in)
{
	static rt::CharacterSet sep(rt::SS("<>\""));
	static rt::CharacterSet sep_pragma(rt::SS(" \t"));

	ASSERT(_Compiled.find(filename) == _Compiled.end());

	Code& code = *(_New(Code));
	code.Filename = filename;
	code.State = 0;

	_Compiled[code.Filename] = &code;

	rt::String source;

	source.TrimCodeComments(source_in);

	rt::String_Ref line;
	rt::String fn;
	rt::String import_filename;
	while(source.GetNextLine(line, false))
	{
		rt::String_Ref t =  line.TrimSpace();
		
		static const rt::SS include("#include");
		static const rt::SS import("#import");

		if(t.StartsWith(include) || t.StartsWith(import))
		{
			rt::String_Ref f[3];
			if(t.Split<false, 0, 0>(f, 3, sep) == 3)
			{	
				fn.Empty();
				_SubsituteMacrosInline(f[1], fn);

				bool lib_mode = false;
				if(f[1].Begin()[-1] == '"' && f[1].End()[0] == '"'){}
				else if(f[1].Begin()[-1] == '<' && f[1].End()[0] == '>')
				{
					lib_mode = _LoadFileSearchDirs.GetSize();
				}
				else
				{	PrintError(rt::SS("illgeal header file include directive: ") + t);
					return *(const rt::String*)&rt::String_Ref::EmptyString();
				}

				int ret = 0;
				if(!lib_mode)
				{
					os::File::ResolveRelativePath((LPCSTR)(filename.GetDirectoryName() + fn), import_filename);
					import_filename.NormalizePathSeparator('/');

					ret = _MergeIncludedFile(import_filename, code.Content);
				}

				for(UINT si = 0; si<=_LoadFileSearchDirs.GetSize(); si++)
				{
					if(ret == -1)return *(const rt::String*)&rt::String_Ref::EmptyString();
					if(ret == 1)goto GO_NEXT_LINE;
					if(ret == 0 && si<_LoadFileSearchDirs.GetSize())
					{
						os::File::ResolveRelativePath((LPCSTR)(_LoadFileSearchDirs[si] + fn), import_filename);
						import_filename.NormalizePathSeparator('/');
						ret = _MergeIncludedFile(import_filename, code.Content);
					}
				}

				ASSERT(ret == 0);
				PrintError(rt::SS("failed to find header file ") + fn);
				return *(const rt::String*)&rt::String_Ref::EmptyString();
			}
		}
		else if(t.StartsWith(rt::SS("#pragma")))
		{
			rt::String_Ref f[3];
			UINT co = t.Split(f, 3, sep_pragma);
			if(co == 2 && f[1] == rt::SS("once"))
			{	code.State |= CST_INCLUDE_ONCE;
			}
			else
			{	
				PrintError(rt::SS("unknown pragma statement: ") + t);
				//code.Content += line;
			}
		}
		else
		{	// C-style line connecting
			if(!line.IsEmpty() && line.Last() == '\\')
			{	
				code.Content += line.TrimRight(1).TrimRightSpace();
				code.Content += ' ';
				while(source.GetNextLine(line, false))
				{	
					if(!line.IsEmpty() && line.Last() == '\\')
					{	code.Content += line.TrimRight(1).TrimSpace(); 
						code.Content += ' ';
					}
					else
					{	code.Content += line.TrimSpace();
						break;
					}
				}
			}
			else
			{	code.Content += line;
			}
		}
		
GO_NEXT_LINE:
		code.Content += '\n';
	}
	
	code.State |= CST_FINALIZED;
	return code.Content;
}

void Precompiler::SubsituteMacros(const rt::String_Ref& content, rt::String& output)
{
	_SubsituteMacrosInline(content, output);
}

bool Precompiler::IsMacroDefined(const rt::String_Ref& macro_name) const
{
	if(_pPredefined && _pPredefined->IsDefined(macro_name))
	{
		return true;
	}	

	auto iter = _Macros.find(macro_name);
	return iter != _Macros.end();
}

const rt::String_Ref& Precompiler::GetMacroDefinition(const rt::String_Ref& macro_name)
{
	auto iter = _Macros.find(macro_name);
	if(iter != _Macros.end())
		return iter->second.Value;
	return rt::String_Ref::EmptyString();
}



}