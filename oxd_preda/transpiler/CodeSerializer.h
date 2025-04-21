#pragma once
#include <vector>
#include <string>

class CodeSerializer {
private:
	int currentIndentLevel = 0;
	std::vector<std::string> lines;

public:
	void AddLine(const std::string &line);
	void AddMacroLine(const std::string& line);
	void PushIndent();
	void PopIndent();
	std::string GetCode() const;
};