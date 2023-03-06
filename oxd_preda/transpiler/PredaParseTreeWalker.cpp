#include "PredaParseTreeWalker.h"

void PredaParseTreeWalker::walk(antlr4::tree::ParseTreeListener *listener, antlr4::tree::ParseTree *t) const
{
	//basically a copy of ParseTreeWalker::walk()
	if (antlrcpp::is<antlr4::tree::ErrorNode *>(t)) {
		listener->visitErrorNode(dynamic_cast<antlr4::tree::ErrorNode *>(t));
		return;
	}
	else if (antlrcpp::is<antlr4::tree::TerminalNode *>(t)) {
		listener->visitTerminal(dynamic_cast<antlr4::tree::TerminalNode *>(t));
		return;
	}

	enterRule(listener, t);
	if (m_bSkipCurrentRuleSubtree)
	{
		m_bSkipCurrentRuleSubtree = false;
	}
	else
	{
		for (auto& child : t->children) {
			walk(listener, child);
		}
	}
	exitRule(listener, t);
}

PredaParseTreeWalker::~PredaParseTreeWalker()
{
}