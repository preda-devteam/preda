#pragma once
#include "antlr_generated/crystality/CrystalityBaseListener.h"
#include "antlr_generated/crystality/CrystalityLexer.h"
#include "antlr_generated/crystality/CrystalityParser.h"
#include "CodeSerializer.h"
#include "PredaParseTreeWalker.h"

#define _LOG(str) std::cout << str << std::endl

enum ExtendSolidityExpressionType
{
    postOperation,
    bracket,
    functionCall,
    dot,
    parentheses,
    preOperation,
    newOperation,
    midOperation,
    TernaryConditional,
    primary
};

class CustomErrorListener : public antlr4::BaseErrorListener {
public:
	virtual void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine,
		const std::string &msg, std::exception_ptr e) override{    
		p_errors.push_back(err_file_path + ":" + std::to_string(line) + ":" + std::to_string(charPositionInLine) + ": " + msg);
    }
	std::vector<std::string> p_errors;
	std::string err_file_path;
};

class CrystalityRealListener :
    public CrystalityBaseListener,
	public CustomErrorListener
{
private:
    CodeSerializer m_codeSerializer;
    mutable std::string m_transpiledCode;
    PredaParseTreeWalker* m_pWalker = nullptr;
    std::map<std::string, CrystalityParser::StateVariableDeclarationContext*> m_stateVariables;
	std::map<std::string, std::map<std::string, std::string>> m_structDefinitions;
    std::vector<CrystalityParser::FunctionDefinitionContext* > m_functions;
	std::vector<CrystalityParser::RelayLambdaDefinitionContext*> m_relayLambdaFunctions;
	std::map<CrystalityParser::RelayLambdaDefinitionContext*, std::pair<std::string, std::string>> m_declaredRelayLambdaFunctions;
    std::map<CrystalityParser::RelayStatementContext*, std::string> m_relayFunctionsScope;
	std::stack<std::map<std::string, std::string>> m_stackBlockLocalVariables;
	std::stack<std::map<std::string, std::string>> m_stackFunctionLocalVariables;
    std::map<std::string, std::string> m_functionDeclarations;
    std::set<std::string> m_calledRelayFunctions;
    bool m_getShardOrder = false;
	bool m_bGenerateCode = false;
	bool m_bPushBlockStack = true;
	bool m_bPopBlockStack = true;
public:
    struct StorageVariable
    {
        std::string type;
        std::string name;
        std::string scope;
    };
	std::vector<StorageVariable> p_vizVariables;

public:
    const char* GetStandardSolidityCode() const
	{ 
        m_transpiledCode = m_codeSerializer.GetCode();
        return m_transpiledCode.c_str();
	}
	auto GetErrorSize() 
	{ 
		return p_errors.size();
	}
public:
    void SetWalker(PredaParseTreeWalker* pWalker) 
	{ 
		m_pWalker = pWalker;
	}
public:
    virtual void enterSourceUnit(CrystalityParser::SourceUnitContext* /*ctx*/) override;
    virtual void exitSourceUnit(CrystalityParser::SourceUnitContext* /*ctx*/) override;
    virtual void enterContractDefinition(CrystalityParser::ContractDefinitionContext* /*ctx*/) override;
    virtual void exitContractDefinition(CrystalityParser::ContractDefinitionContext* /*ctx*/) override;
    
    virtual void enterBlock(CrystalityParser::BlockContext* /*ctx*/) override;
    virtual void exitBlock(CrystalityParser::BlockContext* /*ctx*/) override;
    virtual void enterIfWithBlock(CrystalityParser::IfWithBlockContext* /*ctx*/) override;
    virtual void exitIfWithBlock(CrystalityParser::IfWithBlockContext* /*ctx*/) override;
    virtual void enterElseIfWithBlock(CrystalityParser::ElseIfWithBlockContext* /*ctx*/) override;
    virtual void exitElseIfWithBlock(CrystalityParser::ElseIfWithBlockContext* /*ctx*/) override;
    virtual void enterElseWithBlock(CrystalityParser::ElseWithBlockContext* /*ctx*/) override;
    virtual void exitElseWithBlock(CrystalityParser::ElseWithBlockContext* /*ctx*/) override;
    virtual void enterWhileStatement(CrystalityParser::WhileStatementContext* /*ctx*/) override;
    virtual void exitWhileStatement(CrystalityParser::WhileStatementContext* /*ctx*/) override;
    virtual void enterForStatement(CrystalityParser::ForStatementContext* /*ctx*/) override;
    virtual void exitForStatement(CrystalityParser::ForStatementContext* /*ctx*/) override;
    virtual void enterInlineAssemblyStatement(CrystalityParser::InlineAssemblyStatementContext* /*ctx*/) override;
    virtual void exitInlineAssemblyStatement(CrystalityParser::InlineAssemblyStatementContext* /*ctx*/) override;
    virtual void enterDoWhileStatement(CrystalityParser::DoWhileStatementContext* /*ctx*/) override;
    virtual void exitDoWhileStatement(CrystalityParser::DoWhileStatementContext* /*ctx*/) override;
    virtual void enterFunctionDefinition(CrystalityParser::FunctionDefinitionContext* /*ctx*/) override;
    virtual void exitFunctionDefinition(CrystalityParser::FunctionDefinitionContext* /*ctx*/) override;

    virtual void enterContinueStatement(CrystalityParser::ContinueStatementContext* /*ctx*/) override;
    virtual void enterBreakStatement(CrystalityParser::BreakStatementContext* /*ctx*/) override;
    virtual void enterReturnStatement(CrystalityParser::ReturnStatementContext* /*ctx*/) override;
    virtual void enterThrowStatement(CrystalityParser::ThrowStatementContext* /*ctx*/) override;
    virtual void enterEmitStatement(CrystalityParser::EmitStatementContext* /*ctx*/) override;
    virtual void enterRelayStatement(CrystalityParser::RelayStatementContext* /*ctx*/) override;
	virtual void enterRelayLambdaDefinition(CrystalityParser::RelayLambdaDefinitionContext* ctx) override;
    virtual void exitRelayLambdaDefinition(CrystalityParser::RelayLambdaDefinitionContext* /*ctx*/) override;
    virtual void enterExpressionStatement(CrystalityParser::ExpressionStatementContext* /*ctx*/) override;
    virtual void enterLocalVariableDeclaration(CrystalityParser::LocalVariableDeclarationContext* /*ctx*/) override;
	virtual void enterVariableDeclarationStatement(CrystalityParser::VariableDeclarationStatementContext* ctx) override;

private:
    void DefineStateVariable(CrystalityParser::StateVariableDeclarationContext* /*ctx*/);
    void DefineStruct(CrystalityParser::StructDefinitionContext* /*ctx*/);
    void DefineEnum(CrystalityParser::EnumDefinitionContext* /*ctx*/);
    void DeclareFunction(CrystalityParser::FunctionDefinitionContext* /*ctx*/);
    void SearchForCalledRelayFunctions(CrystalityParser::BlockContext* /*ctx*/);
	void DefineEvent(CrystalityParser::EventDefinitionContext* ctx);
    void DefineFunctions();
    void DefineGetShardOrderFunction();
	void DeclareRelayLambdaFunction(CrystalityParser::RelayLambdaDefinitionContext* ctx);

    std::string ProcessParameterList(CrystalityParser::ParameterListContext* /*ctx*/);
    std::string ProcessExpression(CrystalityParser::ExpressionContext* /*ctx*/);
    std::string ProcessPrimaryExpression(CrystalityParser::PrimaryExpressionContext* /*ctx*/);
    std::string ProcessIdentifier_Interval(CrystalityParser::IdentifierContext* /*ctx*/);
    std::string ProcessExpressionList(CrystalityParser::ExpressionListContext* /*ctx*/);
    std::string ProcessFunctionCallArguments(CrystalityParser::FunctionCallArgumentsContext* /*ctx*/);
    std::string ProcessNameValue(CrystalityParser::NameValueContext* /*ctx*/);
    std::string ProcessNameValueList(CrystalityParser::NameValueListContext* /*ctx*/);
    std::string ProcessTupleExpression(CrystalityParser::TupleExpressionContext* /*ctx*/);
    std::string ProcessLocalVariableDeclaration(CrystalityParser::LocalVariableDeclarationContext* /*ctx*/);
    std::string ProcessVariableDeclaration(CrystalityParser::VariableDeclarationContext* /*ctx*/);
    std::string ProcessVariableDeclarationList(CrystalityParser::VariableDeclarationListContext* /*ctx*/);
    std::string ProcessIdentifierList(CrystalityParser::IdentifierListContext* /*ctx*/);
    std::string ProcessDotExpressionInternal(CrystalityParser::ExpressionContext* /*ctx*/);

	bool ResolveExpressionTypeName(CrystalityParser::ExpressionContext* ctx, std::string& out);
	bool ResolveIdentifierTypeName(std::string identifier_str, std::string& out);

};

