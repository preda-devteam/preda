#include "CodeSerializer.h"

void CodeSerializer::AddLine(const std::string &line)
{
	std::string newLine;
	for (int i = 0; i < currentIndentLevel; i++)
		newLine += "    ";
	lines.push_back(newLine + line);
}

void CodeSerializer::AddMacroLine(const std::string& line)
{
	lines.push_back(line);
}

void CodeSerializer::PushIndent()
{
	currentIndentLevel++;
}

void CodeSerializer::PopIndent()
{
	//assert(currentIndentLevel > 0);
	if (currentIndentLevel > 0)
		currentIndentLevel--;
}

std::string CodeSerializer::GetCode() const
{
	std::string ret;
	for (auto line : lines)
	{
		ret += line + '\n';
	}

	return ret;
}