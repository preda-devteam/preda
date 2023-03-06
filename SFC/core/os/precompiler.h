#pragma once
/**
 * @file precompiler.h
 * @author SFC dev team
 * @brief 
 * @version 1.0
 * @date 2021-04-30
 * 
 * @copyright  
 * System Foundation Classes(SFC)
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *      * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials provided
 *        with the distribution.
 *      * Neither the name of SFC.  nor the names of its
 *        contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *  
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   
 */
/** \defgroup os os 
 * @ingroup SFC
 *  @{
 */
#include "predefines.h"
#include "../rt/string_type.h"
#include "multi_thread.h"
#include "file_dir.h"


namespace os
{
/** \defgroup precomplier precomplier
 * @ingroup os
 *  @{
 */
 
// 
// for C/C++/Java/Javascript code
// 
// handles: #ifdef/#ifndef/#elif/#else/#endif, #if with macro expression like defined(...)
// 
// support macro prefix and suffix
//  
// #include, #import, #pragma once
// comment by // and /* *\/
// #include "..." search order: same directory of the source file than directories by SetIncludeSearchDirectories
// #include <...> search order: directories by SetIncludeSearchDirectories
// 
class PrecompilerPredefinedMacros
{
	rt::hash_map<rt::String, rt::String, rt::String::hash_compare> _PredefinedMacros;

public:
	void	ImportCmdLineOptions(const os::CommandLine& cmd);
	void	Set(const rt::String_Ref& macro, const rt::String_Ref& value);
	void	Set(const rt::String_Ref& macro);
	void	Unset(const rt::String_Ref& macro);
	bool	IsDefined(const rt::String_Ref& macro) const;
	void	Dump() const;
	void 	Merge(const PrecompilerPredefinedMacros& x);
	const rt::String* Get(const rt::String_Ref& macro) const;
};

class Precompiler
{
public:
	struct FileLoad
	{
		virtual bool Load(LPCSTR fn, rt::String& out) = 0;
	};

protected:
	rt::BufferEx<rt::String>	_LoadFileSearchDirs;
	FileLoad*					_pFileLoader;
	bool						_FileLoaderAllowFallback;
	bool						_LoadFile(LPCSTR fn, rt::String& out);

	int							_MergeIncludedFile(const rt::String& fn, rt::String& compiled_code); // 0: file missing, 1: ok, -1: error

protected:
	enum _tagCodeState
	{	CST_FINALIZED		= 0x0001,
		CST_INCLUDE_ONCE	= 0x0002,
	};
	struct Code
	{	rt::String	Filename;
		rt::String	Content;
		DWORD		State;
	};

	typedef rt::hash_map<rt::String_Ref, Code*, rt::String_Ref::hash_compare> t_Codes;
	t_Codes					_Compiled;
	rt::String				_Root;
	rt::String				_SourceCodeFilename;

	rt::String				_MacroPrefix;
	rt::String				_MacroSuffix;
	rt::String				_MacroConnectOp;
	bool					_SuppressWarnings;

	struct _macro
	{	int			ArgmentCount;
		rt::String	Value;
		_macro(){ ArgmentCount = -2; }
	};
	UINT					_ErrorCount;
	UINT					_WarningCount;

	const PrecompilerPredefinedMacros*	_pPredefined;
	typedef rt::hash_map<rt::String, _macro, rt::String::hash_compare> t_MacroTable;
	t_MacroTable			_Macros;
	rt::String				_MacroSubsituted;

	const rt::String_Ref& _Compile(const rt::String_Ref& filename, const rt::String_Ref& source);
	void	_SubsituteFile(const rt::String_Ref& content, rt::String& output);
	void	_SubsituteMacrosInline(const rt::String_Ref& content, rt::String& output);
	bool	_GetFirstToken(const rt::String_Ref& content, rt::String_Ref& token);
	bool	_EvalueMacroIf(const rt::String_Ref& directive, const rt::String_Ref& expr, bool& result);
	bool	_IsMacroBranchCloseDirective(const rt::String_Ref& directive);
	bool	_IsMacroBranchOpenDirective(const rt::String_Ref& directive);
	bool	_SeekToNextCloseDirective(const rt::String_Ref& content, rt::String_Ref& line);

	bool	_DefineMacroFunction(const rt::String_Ref& macro, const rt::String_Ref& value, const rt::String_Ref& arg);
	bool	_DefineMacro(const rt::String_Ref& macro, const rt::String_Ref& value);
	bool	_UndefineMacro(const rt::String_Ref& macro);

public:
	Precompiler(const rt::String_Ref& macro_prefix = nullptr, const rt::String_Ref& macro_suffix = nullptr, const rt::String_Ref& macro_connect = "##");
	~Precompiler(){ Empty(); }

	void	PrintError(LPCSTR msg);
	void	PrintWarning(LPCSTR msg);
	void	SetWarningLevel(int l);
	void	DumpMacros() const;
	void	ClearMacros();
	void	Empty();

	void	SetSourceFilename(const rt::String_Ref& fn){ _SourceCodeFilename = fn; }

	void	Compile(LPCSTR filename, const rt::String_Ref& source = nullptr);
	const	rt::String_Ref& GetCompiled() const;

	UINT	GetErrorCount() const { return _ErrorCount; };
	UINT	GetWarningCount() const { return _WarningCount; }

	void	SubsituteMacros(const rt::String_Ref& content, rt::String& output);
	bool	IsMacroDefined(const rt::String_Ref& macro_name) const;
	const	rt::String_Ref& GetMacroDefinition(const rt::String_Ref& macro_name);

	void	SetEnvVars(const PrecompilerPredefinedMacros* pv);
	void	SetFileLoader(FileLoad* f, bool allow_fallback = true);
	void	SetIncludeSearchDirectories(const rt::String_Ref& dirs); ///< will be converted to absolute directory based on current directory, dir is seperated by ';' or '|'
	void	AddIncludeSearchDirectory(const rt::String_Ref& dir);

	bool	DefineMacro(const rt::String_Ref& macro, const rt::String_Ref& value){ return _DefineMacro(macro, value); }
	bool	UndefineMacro(const rt::String_Ref& macro){ return _UndefineMacro(macro); }
};


/** @}*/

} // namespace os
/** @}*/