#include "exprtk.h"

namespace ext
{

namespace _details
{

void _translate_code_simple(rt::String_Ref& code)
{
	static const rt::CharacterSet_Alphabet	alpha_set("_");

	auto* p = code.Begin();
	if(*p < ' '){ *p = ' '; }
	p++;

	auto* end = code.End() - 1;
	while(p < end)
	{
		if(*p < ' '){ *p = ' '; }
		else if(*p == '.' && alpha_set.Has(p[1])){ *p = '_'; }

		p++;
	}

	if(*p < ' '){ *p = ' '; }
}

void _translate_code(const rt::String_Ref& code, std::string& out, bool simple_expression)
{
	if(simple_expression)
	{
		out.assign(code.Begin(), code.GetLength());
        auto t = rt::String_Ref(out.data(), code.GetLength());
		_translate_code_simple(t);
	}
	else
	{
		rt::String temp = code;

		// .length -> []
		temp.Replace(".length", "[]");
		temp.Replace("++", "+=1");
		temp.Replace("--", "-=1");
		temp.Replace("||", " or ");
		temp.Replace("&&", " and ");
		
		// '\t' -> ' ',   'xx.yy' -> 'xx_yy' 
		_translate_code_simple(temp);
		
		// = -> :=
		// ! -> not
		rt::CharacterSet	op_set("/-=+!<>:%");
		for(UINT i=0;i<temp.GetLength();i++)
		{
			if(i && temp[i] == '=' && !op_set.Has(temp[i-1]) && temp[i+1] != '=')
			{	
				temp.Insert(i, ':');
				i++;
				continue;
			}
		
			if(temp[i] == '!' && temp[i+1] != '=')
			{
				temp.Insert(i, rt::SS(" true nand"));
				temp[i+10] = ' ';
				i+=10;
				continue;
			}
		}

		out = temp.GetString();
	}
}

void _translate_symbol(const rt::String_Ref& code, std::string& out)
{
	rt::String_Ref x = ALLOCA_C_STRING(code);

	x.Replace('.', '_');
	out = x.GetString();
}

} // namespace _details
} // namespace rt

