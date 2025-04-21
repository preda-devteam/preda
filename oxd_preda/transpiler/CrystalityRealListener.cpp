#include "CrystalityRealListener.h"

void CrystalityRealListener::enterSourceUnit(CrystalityParser::SourceUnitContext* ctx)
{
	/// pragmaDirective
	for (auto pragmaDirective : ctx->pragmaDirective()){
		m_codeSerializer.AddLine("pragma " + pragmaDirective->pragmaName()->getText() + " " + pragmaDirective->pragmaValue()->getText() + ";");
	}
	/// importDirective
	for (auto importDirective : ctx->importDirective()) {
		/// TODO : Add import directive
		m_codeSerializer.AddLine(importDirective->getText());
	}
	/// contractDefinition
	m_codeSerializer.AddLine("");
}

void CrystalityRealListener::exitSourceUnit(CrystalityParser::SourceUnitContext* ctx)
{

}

void CrystalityRealListener::enterContractDefinition(CrystalityParser::ContractDefinitionContext* ctx)
{
	m_pWalker->SkipCurrentRuleSubtree();
	/// contract identifier
	m_codeSerializer.AddLine("contract " + ctx->identifier()->getText());
	m_codeSerializer.AddLine("{");
	m_codeSerializer.PushIndent();
	/// contract part
	for (auto contractPart : ctx->contractPart())
	{
		if (contractPart->stateVariableDeclaration())
		{
			DefineStateVariable(contractPart->stateVariableDeclaration());
		}
		else if (contractPart->structDefinition())
		{
			DefineStruct(contractPart->structDefinition());
		}
		else if (contractPart->enumDefinition())
		{
			DefineEnum(contractPart->enumDefinition());
		}
		else if (contractPart->usingForDeclaration())
		{
			m_codeSerializer.AddLine(contractPart->usingForDeclaration()->getText());
		}
		else if (contractPart->functionDefinition())
		{
			DeclareFunction(contractPart->functionDefinition());
		}
		else if (contractPart->eventDefinition())
		{
			DefineEvent(contractPart->eventDefinition());
		}
	}
	/// GenerateCode for functions
	DefineFunctions();
}

void CrystalityRealListener::exitContractDefinition(CrystalityParser::ContractDefinitionContext* /*ctx*/)
{
	m_codeSerializer.PopIndent();
	m_codeSerializer.AddLine("}");
}

void CrystalityRealListener::DefineStateVariable(CrystalityParser::StateVariableDeclarationContext* ctx)
{
	/// Generate code for state variable definition
	std::string strStateVariableDefinition = "";
	m_stateVariables.insert({ ctx->identifier()->getText(), ctx });
	p_vizVariables.push_back({ctx->typeName()->getText(), ctx->identifier()->getText(), ctx->scope() ? ctx->scope()->getText().substr(1) : "global"});

	if (ctx->scope() && "@address" == ctx->scope()->getText())
		strStateVariableDefinition += "mapping (address => " + ctx->typeName()->getText() + ")";
	else if (ctx->scope() && ctx->scope()->Uint())
		strStateVariableDefinition += "mapping (" + ctx->scope()->Uint()->getText() + " => " + ctx->typeName()->getText() + ")";
	else
		strStateVariableDefinition += ctx->typeName()->getText();

	for (CrystalityParser::AccessSpecifierContext* asctx : ctx->accessSpecifier())
	{
		strStateVariableDefinition += " " + asctx->getText();
	}
	strStateVariableDefinition += " " + ctx->identifier()->getText();
	strStateVariableDefinition += ";";

	m_codeSerializer.AddLine(strStateVariableDefinition);
}

void CrystalityRealListener::DefineStruct(CrystalityParser::StructDefinitionContext* ctx)
{
	/// Generate code for struct head
	std::string struct_name = ctx->identifier()->getText();
	m_codeSerializer.AddLine("struct " + struct_name);
	m_codeSerializer.AddLine("{");
	m_codeSerializer.PushIndent();
	/// Generate code for struct body
	std::string type_name, var_name;
	for (auto variableDelaration : ctx->variableDeclaration())
	{
		type_name = variableDelaration->typeName()->getText();
		var_name = variableDelaration->identifier()->getText();
		m_codeSerializer.AddLine(type_name + " " +
								(variableDelaration->storageLocation()? variableDelaration->storageLocation()->getText() + " " : "") +
								 var_name + ";");
		m_structDefinitions[struct_name][var_name] = type_name;
	}
	m_codeSerializer.PopIndent();
	m_codeSerializer.AddLine("}");
}

void CrystalityRealListener::DefineEnum(CrystalityParser::EnumDefinitionContext* ctx)
{
	/// Generate code for enum head
	m_codeSerializer.AddLine("enum " + ctx->identifier()->getText());
	m_codeSerializer.AddLine("{");
	m_codeSerializer.PushIndent();
	/// Generate code for enum body
	for(size_t i = 0; i < ctx->enumValue().size(); ++i)
	{
		m_codeSerializer.AddLine(ctx->enumValue(i)->identifier()->getText() + ((i == (ctx->enumValue().size() - 1)) ? "" : ","));
	}
	m_codeSerializer.PopIndent();
	m_codeSerializer.AddLine("}");
}

void CrystalityRealListener::DeclareFunction(CrystalityParser::FunctionDefinitionContext* ctx)
{
	m_functions.push_back(ctx);
	m_stackFunctionLocalVariables.push(std::map<std::string, std::string>());
	/// Generate Function Signature
	std::string functionHead = "";
	std::string functionName = ctx->functionDescriptor()->ConstructorKeyword() ? "constructor" : ctx->functionDescriptor()->identifier()->getText();
	functionHead += functionName + "(";
	std::string scope_type = "";
	if (ctx->scope() && "@address" == ctx->scope()->getText())
		scope_type = "address";
	else if (ctx->scope() && ctx->scope()->Uint())
		scope_type = ctx->scope()->Uint()->getText();

	if(!scope_type.empty()) {
		functionHead += scope_type + ",";
		m_stackFunctionLocalVariables.top()["_scope"] = scope_type;
	}
	
	std::vector<CrystalityParser::ParameterContext*> parameters = ctx->parameterList()->parameter();
	for (size_t i = 0; i < parameters.size(); ++i) {
		std::string type_name;
		if("uint" == parameters[i]->typeName()->getText())
			type_name = "uint256";
		else if("uint[]" == parameters[i]->typeName()->getText())
			type_name = "uint256[]";
		else 
			type_name = parameters[i]->typeName()->getText();

		functionHead += type_name + ",";
		if(parameters[i]->identifier())
			m_stackFunctionLocalVariables.top()[parameters[i]->identifier()->getText()] = type_name; 
	}
	if(functionHead.back() == ',')
		functionHead.pop_back();
	functionHead += ")";
	m_functionDeclarations.insert({ functionName, functionHead });

	/// search for relay functions (internal -> public)
	SearchForCalledRelayFunctions(ctx->block());
	m_stackFunctionLocalVariables.pop();
}

void CrystalityRealListener::SearchForCalledRelayFunctions(CrystalityParser::BlockContext* ctx)
{
	m_bGenerateCode = false;
	PredaParseTreeWalker* oldWalker = m_pWalker;
	PredaParseTreeWalker newWalker;
	SetWalker(&newWalker);
	m_pWalker->walk(this, ctx);
	SetWalker(oldWalker);
}

void CrystalityRealListener::DefineEvent(CrystalityParser::EventDefinitionContext* ctx)
{
	if(ctx->natSpec()) return;
	std::string event("event ");
	event += ctx->identifier()->getText() + " (";
	for(auto p : ctx->eventParameterList()->eventParameter()){
		event += p->typeName()->getText();
		if(p->IndexedKeyword())
			event += " indexed";
		if(p->identifier())
			event += " " + p->identifier()->getText();
		event += ",";
	}
	if(!ctx->eventParameterList()->eventParameter().empty())
		event.pop_back();
	event += ")";
	if(ctx->AnonymousKeyword())
		event += " anonymous";
	event += ";";
	m_codeSerializer.AddLine(event);
}

void CrystalityRealListener::DefineFunctions()
{
	m_bGenerateCode = true;
	for (CrystalityParser::FunctionDefinitionContext* ctx : m_functions)
	{
		PredaParseTreeWalker* oldWalker = m_pWalker;
		PredaParseTreeWalker newWalker;
		SetWalker(&newWalker);
		m_pWalker->walk(this, ctx);
		SetWalker(oldWalker);
	}

	for (CrystalityParser::RelayLambdaDefinitionContext* ctx : m_relayLambdaFunctions)
	{
		PredaParseTreeWalker* oldWalker = m_pWalker;
		PredaParseTreeWalker newWalker;
		SetWalker(&newWalker);
		m_pWalker->walk(this, ctx);
		SetWalker(oldWalker);
	}

	if (m_getShardOrder)
	{
		DefineGetShardOrderFunction();
	}
}

void CrystalityRealListener::DefineGetShardOrderFunction()
{
	m_codeSerializer.AddLine("");
	m_codeSerializer.AddLine("function getShardOrder() internal returns (uint32)");
	m_codeSerializer.AddLine("{");
	m_codeSerializer.PushIndent();
	m_codeSerializer.AddLine("(bool success, bytes memory data) = address(555).call(");
	m_codeSerializer.PushIndent();
	m_codeSerializer.AddLine("abi.encodeWithSignature(\"getShardOrder()\")");
	m_codeSerializer.PopIndent();
	m_codeSerializer.AddLine(");");
	m_codeSerializer.AddLine("return abi.decode(data, (uint32));");
	m_codeSerializer.PopIndent();
	m_codeSerializer.AddLine("}");
}

void CrystalityRealListener::DeclareRelayLambdaFunction(CrystalityParser::RelayLambdaDefinitionContext* ctx)
{

}

std::string CrystalityRealListener::ProcessParameterList(CrystalityParser::ParameterListContext* parameterList)
{
	std::string strParameterList = "";
	std::vector<CrystalityParser::ParameterContext*> parameters = parameterList->parameter();
	for (size_t i = 0; i < parameters.size(); ++i)
	{
		strParameterList += parameters[i]->typeName()->getText() +
							(parameters[i]->storageLocation() ? " " + parameters[i]->storageLocation()->getText() : "") +
							(parameters[i]->identifier() ? " " + parameters[i]->identifier()->getText() : "");
		if (i < parameters.size() - 1) strParameterList += ", ";
	}
	return strParameterList;
}

std::string CrystalityRealListener::ProcessExpression(CrystalityParser::ExpressionContext* ctx)
{
	switch (ExtendSolidityExpressionType(ctx->expressionType))
	{

	case postOperation:
		return ProcessExpression(ctx->expression(0)) + ctx->postOperator()->getText();
	case bracket:
		return ProcessExpression(ctx->expression(0)) + "[" + ProcessExpression(ctx->expression(1)) + "]";
	case functionCall:
		return ProcessExpression(ctx->expression(0)) + "(" + ProcessFunctionCallArguments(ctx->functionCallArguments()) + ")";
	case dot:
		return ProcessDotExpressionInternal(ctx);
	case parentheses:
		return "(" + ProcessExpression(ctx->expression(0)) + ")";
	case preOperation:
		return ctx->preOperator()->getText() + 
			   (ctx->preOperator()->getText() == "++" || ctx->preOperator()->getText() == "--" || ctx->preOperator()->getText() == "!" || ctx->preOperator()->getText() == "~" ? "" : " ") + 
			   ProcessExpression(ctx->expression(0));
	case newOperation:
		return "new " + ctx->typeName()->getText();
	case midOperation:
		return ProcessExpression(ctx->expression(0)) + " " + ctx->midOperator()->getText() + " " + ProcessExpression(ctx->expression(1));
	case TernaryConditional:
		return ProcessExpression(ctx->expression(0)) + " ? " + ProcessExpression(ctx->expression(1)) + " : " + ProcessExpression(ctx->expression(2));
	case primary:
		return ProcessPrimaryExpression(ctx->primaryExpression());
	default:
		return "";
	}
}

std::string CrystalityRealListener::ProcessPrimaryExpression(CrystalityParser::PrimaryExpressionContext* ctx)
{
	if (ctx->identifier())
	{
		return ProcessIdentifier_Interval(ctx->identifier()) + (ctx->matchedParentheses() ? "[]" : "");
	}
	else if (ctx->tupleExpression())
	{
		return ProcessTupleExpression(ctx->tupleExpression());
	}
	else if (ctx->typeNameExpression())
	{
		return ctx->typeNameExpression()->getText() + (ctx->matchedParentheses() ? "[]" : "");
	}
	return ctx->getText();
}

std::string CrystalityRealListener::ProcessIdentifier_Interval(CrystalityParser::IdentifierContext* ctx)
{
	std::string identifier = ctx->getText();
	if(m_stateVariables.find(identifier) != m_stateVariables.end() && m_stateVariables[identifier]->scope()){
		std::string scope = m_stateVariables[identifier]->scope()->getText();
		if("@global" == scope || "@local" == scope)
			return identifier;
		else 
			return identifier + "[_scope]";
	}
	else 
		return identifier;
}

std::string CrystalityRealListener::ProcessExpressionList(CrystalityParser::ExpressionListContext* ctx)
{
	std::vector<CrystalityParser::ExpressionContext*> expressions = ctx->expression();
	std::string outResult = "";
	for (size_t i = 0; i < expressions.size(); ++i)
	{
		if (i > 0)
			outResult += ", ";
		outResult += ProcessExpression(expressions[i]);
	}
	return outResult;
}

std::string CrystalityRealListener::ProcessFunctionCallArguments(CrystalityParser::FunctionCallArgumentsContext* ctx)
{
	if (ctx->nameValueList())
	{
		return "{" + ProcessNameValueList(ctx->nameValueList()) + "}";
	}
	if (ctx->expressionList())
	{
		return ProcessExpressionList(ctx->expressionList());
	}
	return "";
}

std::string CrystalityRealListener::ProcessNameValue(CrystalityParser::NameValueContext* ctx)
{
	return ProcessIdentifier_Interval(ctx->identifier()) + " : " + ProcessExpression(ctx->expression());
}

std::string CrystalityRealListener::ProcessNameValueList(CrystalityParser::NameValueListContext* ctx)
{
	std::vector<CrystalityParser::NameValueContext*> nameValues = ctx->nameValue();
	std::string outResult = "";
	for (size_t i = 0; i < nameValues.size(); ++i)
	{
		if (i > 0)
			outResult += ", ";
		outResult += ProcessNameValue(nameValues[i]);
	}
	return outResult;
}

std::string CrystalityRealListener::ProcessTupleExpression(CrystalityParser::TupleExpressionContext* ctx)
{
	std::string outResult = "";
	if (ctx->bracketTupleExpression())
	{
		outResult += "(";
		if (ctx->bracketTupleExpression()->expression())
		{
			outResult += ProcessExpression(ctx->bracketTupleExpression()->expression());
		}
		std::vector<CrystalityParser::MoreExpressionContext*> moreExpressions = ctx->bracketTupleExpression()->moreExpression();
		for (size_t i = 0; i < moreExpressions.size(); ++i)
		{
			outResult += ", ";
			if (moreExpressions[i]->expression())
			{
				outResult += ProcessExpression(moreExpressions[i]->expression());
			}
		}
		outResult += ")";
	}
	else
	{
		outResult += "[";
		std::vector<CrystalityParser::ExpressionContext*> expressions = ctx->paranthesesTupleExpression()->expression();
		for (size_t i = 0; i < expressions.size(); ++i)
		{
			if (i > 0)
				outResult += ", ";
			outResult += ProcessExpression(expressions[i]);
		}
		outResult += "]";
	}
	return outResult;
}

std::string CrystalityRealListener::ProcessLocalVariableDeclaration(CrystalityParser::LocalVariableDeclarationContext* ctx)
{
	std::string strRes = "";
	if (ctx->identifierList())
	{
		strRes += "var " + ProcessIdentifierList(ctx->identifierList());
	}
	else if (ctx->variableDeclaration())
	{
		strRes += ProcessVariableDeclaration(ctx->variableDeclaration());
	}
	else if (ctx->variableDeclarationList())
	{
		strRes += ProcessVariableDeclarationList(ctx->variableDeclarationList());
	}
	strRes += (ctx->expression() ? " = " + ProcessExpression(ctx->expression()) : "");
	return strRes;
}

std::string CrystalityRealListener::ProcessVariableDeclaration(CrystalityParser::VariableDeclarationContext* ctx)
{
	std::string strRes = "";
	strRes += ctx->typeName()->getText();
	if (ctx->storageLocation())
	{
		strRes += " " + ctx->storageLocation()->getText();
	}
	strRes += " " + ProcessIdentifier_Interval(ctx->identifier());
	return strRes;
}

std::string CrystalityRealListener::ProcessVariableDeclarationList(CrystalityParser::VariableDeclarationListContext* ctx)
{
	std::string strRes = "";
	if (ctx->variableDeclaration())
	{
		strRes += ProcessVariableDeclaration(ctx->variableDeclaration());
	}
	for (size_t i = 0; i < ctx->moreVariableDeclaration().size(); ++i)
	{
		strRes += (ctx->moreVariableDeclaration(i)->variableDeclaration() ? ", " + ProcessVariableDeclaration(ctx->moreVariableDeclaration(i)->variableDeclaration()) : ", ");
	}
	return strRes;
}

std::string CrystalityRealListener::ProcessIdentifierList(CrystalityParser::IdentifierListContext* ctx)
{
	std::vector<CrystalityParser::MoreIdentifierContext*> identifiers = ctx->moreIdentifier();
	std::string strRes = "(";
	for (size_t i = 0; i < identifiers.size(); ++i)
	{
		strRes += (identifiers[i]->identifier() ? ProcessIdentifier_Interval(identifiers[i]->identifier()) + ", " : ", ");
	}
	if (ctx->identifier())
	{
		strRes += ProcessIdentifier_Interval(ctx->identifier());
	}
	strRes += ")";
	return strRes;
}

std::string CrystalityRealListener::ProcessDotExpressionInternal(CrystalityParser::ExpressionContext* ctx)
{
	if (ctx->getText() == "block.shardorder")
	{
		m_getShardOrder = true;
		return "getShardOrder()";
	}
	if (ctx->getText() == "msg.scope")
	{
		return "_scope";
	}
	return ProcessExpression(ctx->expression(0)) + "." + ctx->identifier()->getText();
}

bool CrystalityRealListener::ResolveExpressionTypeName(CrystalityParser::ExpressionContext* ctx, std::string& out)
{
	out = "";
	switch (ExtendSolidityExpressionType(ctx->expressionType))
	{
		case bracket:
			if (ResolveIdentifierTypeName(ctx->getText(), out))
				return true;
			if(!ResolveExpressionTypeName(ctx->expression(0), out))
				return false;
			if(out.find("[") != std::string::npos)
				out = out.substr(0, out.find("["));
			else if (out.find("mapping") != std::string::npos) {
				auto valueBegin = out.find("=>") + 2;
				auto valueEnd = out.find_last_of(")");
				out = out.substr(valueBegin, valueEnd - valueBegin);
			}
			return true;
		case dot:
		{
			if (ctx->getText() == "msg.scope") {
				out = "address";
				return true;
			}
			std::string struct_name;
			if(!ResolveExpressionTypeName(ctx->expression(0), struct_name))
				return false;
			std::string struct_member = ctx->identifier()->getText();
			if (m_structDefinitions.find(struct_name) != m_structDefinitions.end() && m_structDefinitions[struct_name].find(struct_member) != m_structDefinitions[struct_name].end()) {
				out = m_structDefinitions[struct_name][struct_member];
				return true;
			}
			else if ("length" == ctx->identifier()->getText()) {
				out = "uint256";
				return true;
			}
			return false;
		}
			break;
		case primary:
			if(ctx->primaryExpression()->identifier())
				return ResolveIdentifierTypeName(ctx->primaryExpression()->identifier()->getText(), out);
			break;
		default:
			return false;
	}
	return false;
}

bool CrystalityRealListener::ResolveIdentifierTypeName(std::string identifier, std::string& out)
{
	auto& block_var_map = m_stackBlockLocalVariables.top();
	if(block_var_map.find(identifier) != block_var_map.end()){
		out = block_var_map[identifier];
		return true;
	}
	auto& func_var_map = m_stackFunctionLocalVariables.top();
	if(func_var_map.find(identifier) != func_var_map.end()){
		out = func_var_map[identifier];
		return true;
	}
	if(m_stateVariables.find(identifier) != m_stateVariables.end())
	{
		out = m_stateVariables[identifier]->typeName()->getText();
		return true;
	}
	return false;
}

void CrystalityRealListener:: enterBlock(CrystalityParser::BlockContext* /*ctx*/) 
{
	if (m_bGenerateCode) {
		m_codeSerializer.AddLine("{");
		m_codeSerializer.PushIndent();
	}
	else if (m_bPushBlockStack) {
		m_stackBlockLocalVariables.push(std::map<std::string, std::string>());
	}
	else
		m_bPushBlockStack = true;
}

void CrystalityRealListener::exitBlock(CrystalityParser::BlockContext* /*ctx*/) 
{
	if(m_bGenerateCode){
		m_codeSerializer.PopIndent();
		m_codeSerializer.AddLine("}");
	}
	else if(m_bPopBlockStack){
		m_stackBlockLocalVariables.pop();
	}
}

void CrystalityRealListener::enterIfWithBlock(CrystalityParser::IfWithBlockContext* ctx)
{
	if(m_bGenerateCode){
		std::string expStr = ProcessExpression(ctx->expression());
		m_codeSerializer.AddLine("if (" + expStr + ")");
	}
}

void CrystalityRealListener::exitIfWithBlock(CrystalityParser::IfWithBlockContext* ctx)
{

}

void CrystalityRealListener::enterElseIfWithBlock(CrystalityParser::ElseIfWithBlockContext* ctx)
{
	if(m_bGenerateCode){
		std::string expStr = ProcessExpression(ctx->expression());

		m_codeSerializer.AddLine("else if (" + expStr + "){");
		m_codeSerializer.PushIndent();
	}
}

void CrystalityRealListener::exitElseIfWithBlock(CrystalityParser::ElseIfWithBlockContext* ctx)
{
	if(m_bGenerateCode){
		m_codeSerializer.PopIndent();
		m_codeSerializer.AddLine("}");
	}
}

void CrystalityRealListener::enterElseWithBlock(CrystalityParser::ElseWithBlockContext* /*ctx*/)
{
	if(m_bGenerateCode){
		m_codeSerializer.AddLine("else {");
		m_codeSerializer.PushIndent();
	}
}

void CrystalityRealListener::exitElseWithBlock(CrystalityParser::ElseWithBlockContext* /*ctx*/)
{
	if(m_bGenerateCode){
		m_codeSerializer.PopIndent();
		m_codeSerializer.AddLine("}");
	}
}

void CrystalityRealListener::enterWhileStatement(CrystalityParser::WhileStatementContext* ctx) 
{
	if(m_bGenerateCode){
		std::string expStr = ProcessExpression(ctx->expression());

		m_codeSerializer.AddLine("while (" + expStr + ")");
	}
}

void CrystalityRealListener::exitWhileStatement(CrystalityParser::WhileStatementContext* ctx) 
{
}

void CrystalityRealListener::enterForStatement(CrystalityParser::ForStatementContext* ctx)
{
	if(m_bGenerateCode){
		std::string forStatementStr = "for (";
		if (ctx->firstExpression)
		{
			forStatementStr += ProcessExpression(ctx->firstExpression);
		}
		else
		{
			forStatementStr += ProcessLocalVariableDeclaration(ctx->localVariableDeclaration());
		}
		forStatementStr += "; ";
		if (ctx->secondExpression)
		{
			forStatementStr += ProcessExpression(ctx->secondExpression);
		}
		forStatementStr += "; ";
		if (ctx->thirdExpression)
		{
			forStatementStr += ProcessExpression(ctx->thirdExpression);
		}
		forStatementStr += ")";
		m_codeSerializer.AddLine(forStatementStr);
	}
	else {
		m_stackBlockLocalVariables.push(std::map<std::string, std::string>());
		m_bPushBlockStack = false;
	}
}

void CrystalityRealListener::exitForStatement(CrystalityParser::ForStatementContext* /*ctx*/)
{

}

void CrystalityRealListener::enterInlineAssemblyStatement(CrystalityParser::InlineAssemblyStatementContext* /*ctx*/) 
{

}

void CrystalityRealListener::exitInlineAssemblyStatement(CrystalityParser::InlineAssemblyStatementContext* /*ctx*/) 
{
	
}

void CrystalityRealListener::enterDoWhileStatement(CrystalityParser::DoWhileStatementContext* ctx) 
{
	if(m_bGenerateCode){
		m_codeSerializer.AddLine("do {");
		m_codeSerializer.PushIndent();
	}
}
void CrystalityRealListener::exitDoWhileStatement(CrystalityParser::DoWhileStatementContext* ctx) 
{
	if(m_bGenerateCode){
		std::string expStr = ProcessExpression(ctx->expression());

		m_codeSerializer.PopIndent();
		m_codeSerializer.AddLine("} while (" + expStr + ");");
	}
}

void CrystalityRealListener::enterFunctionDefinition(CrystalityParser::FunctionDefinitionContext* ctx)
{
	if (ctx->natSpec())
	{
		m_codeSerializer.AddLine(ctx->natSpec()->getText());
	}
	m_codeSerializer.AddLine("");
	/// Generate code for function head
	{
		std::string functionName = ctx->functionDescriptor()->ConstructorKeyword() ? "constructor" : ctx->functionDescriptor()->identifier()->getText();
		std::string functionDefinition = (ctx->functionDescriptor()->ConstructorKeyword() ? "" : "function ") + functionName + "(";

		if (ctx->scope() && "@address" == ctx->scope()->getText())
		{
			functionDefinition += "address _scope";
			if (ctx->parameterList()->parameter().size()) functionDefinition += ", ";
		}
		else if (ctx->scope() && ctx->scope()->Uint())
		{
			functionDefinition += ctx->scope()->Uint()->getText() + " _scope";
			if (ctx->parameterList()->parameter().size()) functionDefinition += ", ";
		}
		std::string parameterList = ProcessParameterList(ctx->parameterList());
		functionDefinition += parameterList;
		functionDefinition += ")";

		CrystalityParser::ModifierListContext* modifierList = ctx->modifierList();
		std::string modifierListStr = "";
		for (size_t i = 0; i < modifierList->modifierInvocation().size(); ++i)
		{
			if (i > 0) modifierListStr += " ";
			modifierListStr += modifierList->modifierInvocation(i)->getText();
		}
		if (modifierList->modifierInvocation().size()) modifierListStr += " ";
		for (size_t i = 0; i < modifierList->stateMutability().size(); ++i)
		{
			if (i > 0) modifierListStr += " ";
			modifierListStr += modifierList->stateMutability(i)->getText();
		}
		if (modifierList->stateMutability().size()) modifierListStr += " ";
		for (size_t i = 0; i < modifierList->accessiblity().size(); ++i)
		{
			if (i > 0) modifierListStr += " ";
			if (modifierList->accessiblity(i)->getText() == "internal" && m_calledRelayFunctions.count(functionName))
			{
				modifierListStr += "public";
			}
			else modifierListStr += modifierList->accessiblity(i)->getText();
		}
		if (modifierList->overrideSpecifier().size())
			functionDefinition += " override";
		functionDefinition += " " + modifierListStr;

		if (ctx->returnParameters())
		{
			functionDefinition += " returns (";
			parameterList = ProcessParameterList(ctx->returnParameters()->parameterList());
			functionDefinition += parameterList + ")";
		}

		m_codeSerializer.AddLine(functionDefinition);
	}
}

void CrystalityRealListener::exitFunctionDefinition(CrystalityParser::FunctionDefinitionContext* /*ctx*/)
{

}

void CrystalityRealListener::enterExpressionStatement(CrystalityParser::ExpressionStatementContext* ctx)
{
	if(m_bGenerateCode)
		m_codeSerializer.AddLine(ProcessExpression(ctx->expression()) + ";");	
}

void CrystalityRealListener::enterContinueStatement(CrystalityParser::ContinueStatementContext* ctx) 
{
	if(m_bGenerateCode)
		m_codeSerializer.AddLine(ctx->getText());
}

void CrystalityRealListener::enterBreakStatement(CrystalityParser::BreakStatementContext* ctx)
{
	if(m_bGenerateCode)
		m_codeSerializer.AddLine(ctx->getText());
}

void CrystalityRealListener::enterReturnStatement(CrystalityParser::ReturnStatementContext* ctx) 
{
	if(m_bGenerateCode){
		if (ctx->expression())
		{
			m_codeSerializer.AddLine("return " + ProcessExpression(ctx->expression()) + ";");
		}
		else m_codeSerializer.AddLine("return;");
	}
}

void CrystalityRealListener::enterThrowStatement(CrystalityParser::ThrowStatementContext* /*ctx*/) 
{
	if(m_bGenerateCode)
		m_codeSerializer.AddLine("throw;");
}

void CrystalityRealListener::enterEmitStatement(CrystalityParser::EmitStatementContext* ctx) 
{
	if(m_bGenerateCode){
		std::string emit("emit ");
		emit += ctx->functionCall()->expression()->getText() + "(";
		emit += ProcessFunctionCallArguments(ctx->functionCall()->functionCallArguments());
		emit += ");";
		m_codeSerializer.AddLine(emit);
	}
}

void CrystalityRealListener::enterRelayStatement(CrystalityParser::RelayStatementContext* ctx) 
{
	if(m_bGenerateCode){
		m_codeSerializer.AddLine("address(" + m_relayFunctionsScope[ctx] + ").call(");
		m_codeSerializer.PushIndent();

		std::string strRes = "abi.encodeWithSignature(";

		if(ctx->functionCallArguments()){
			strRes += "\"" + m_functionDeclarations[ctx->identifier()->getText()] + "\"";
			if (ctx->relayScope()->expression())
				strRes += ", " + ProcessExpression(ctx->relayScope()->expression());
			std::string args = ProcessFunctionCallArguments(ctx->functionCallArguments());
			if (!args.empty())
				strRes += ", " + args;
			strRes += ")";
		}
		else if(ctx->relayLambdaDefinition())
		{
			m_pWalker->SkipCurrentRuleSubtree();
			strRes += "\"" + m_declaredRelayLambdaFunctions[ctx->relayLambdaDefinition()].first + "\"";
			if (ctx->relayScope()->expression())
				strRes += ", " + ProcessExpression(ctx->relayScope()->expression());
			for(auto param : ctx->relayLambdaDefinition()->relayLambdaParameter()){
				strRes += ", ";
				if(param->expression()) 
					strRes += ProcessExpression(param->expression());
				else 
					strRes += param->identifier()->getText();
			}
			strRes += ")";
		}

		m_codeSerializer.AddLine(strRes);

		m_codeSerializer.PopIndent();
		m_codeSerializer.AddLine(");");
	}
	else
	{
		if (ctx->functionCallArguments())
		{
			m_calledRelayFunctions.insert(ctx->identifier()->getText());
		}
		else if (ctx->relayLambdaDefinition())
		{
			std::string relay_lambda_function_head = "function ";
			std::string relay_lambda_function_sig = "_relay_lambda_" + std::to_string(m_declaredRelayLambdaFunctions.size()) + "(";
			relay_lambda_function_head += relay_lambda_function_sig;
			std::string type_name, var_name;
			std::map<std::string, std::string> lambda_function_variables;
			if (ctx->relayScope()->expression()) {
				if (!ResolveExpressionTypeName(ctx->relayScope()->expression(), type_name))
					return;
				relay_lambda_function_head += type_name + " _scope, ";
				relay_lambda_function_sig += type_name + ",";
				var_name = ctx->relayScope()->expression()->getText();
				lambda_function_variables[var_name] = type_name;
			}
			for (auto pCtx : ctx->relayLambdaDefinition()->relayLambdaParameter())
			{
				var_name = pCtx->identifier()->getText();
				if (pCtx->expression()) {
					if (pCtx->typeName())
						type_name = pCtx->typeName()->getText();
					else if (!ResolveExpressionTypeName(pCtx->expression(), type_name))
						return;
				}
				else if (!ResolveIdentifierTypeName(pCtx->identifier()->getText(), type_name))
					return;
				relay_lambda_function_sig += (type_name == "uint" ? "uint256" : type_name == "uint[]" ? "uint256[]" : type_name);
				relay_lambda_function_sig += ",";
				lambda_function_variables[var_name] = type_name;
				if (type_name.find("[") != std::string::npos || type_name.find("string") != std::string::npos)
					type_name += " memory";
				relay_lambda_function_head += type_name + " " + var_name + ", ";
			}

			if (relay_lambda_function_head.back() == ' ' && relay_lambda_function_head[relay_lambda_function_head.length() - 2] == ',') {
				relay_lambda_function_head.pop_back();
				relay_lambda_function_head.pop_back();
			}
			relay_lambda_function_head += ") public";

			if (relay_lambda_function_sig.back() == ',')
				relay_lambda_function_sig.pop_back();
			relay_lambda_function_sig += ")";


			m_declaredRelayLambdaFunctions[ctx->relayLambdaDefinition()].first = relay_lambda_function_sig;
			m_declaredRelayLambdaFunctions[ctx->relayLambdaDefinition()].second = relay_lambda_function_head;
			m_stackFunctionLocalVariables.push(lambda_function_variables);
			m_relayLambdaFunctions.push_back(ctx->relayLambdaDefinition());
		}
		/// global
		if ("@global" == ctx->relayScope()->getText())
			m_relayFunctionsScope[ctx] = "888";
		/// shards
		else if ("@locals" == ctx->relayScope()->getText())
			m_relayFunctionsScope[ctx] = "777";
		/// user-defined and address scope
		else if (ctx->relayScope()->expression())
		{
			std::string type_name;
			if (!ResolveExpressionTypeName(ctx->relayScope()->expression(), type_name))
				return;
			if (type_name.find("uint") != std::string::npos)
				m_relayFunctionsScope[ctx] = type_name.substr(4);
			else
				m_relayFunctionsScope[ctx] = "666";
		}
	}
}

void CrystalityRealListener::exitRelayLambdaDefinition(CrystalityParser::RelayLambdaDefinitionContext* ctx)
{
	if(!m_bGenerateCode)
		m_stackFunctionLocalVariables.pop();
}

void CrystalityRealListener::enterLocalVariableDeclaration(CrystalityParser::LocalVariableDeclarationContext* ctx) 
{
	if(!m_bGenerateCode)
	{
		auto daclareVariableOnStack = [&](CrystalityParser::VariableDeclarationContext* ctx){
			std::string type_name, var_name;
			type_name = ctx->typeName()->getText();
			var_name = ctx->identifier()->getText();
			m_stackBlockLocalVariables.top()[var_name] = type_name;
		};
		if(ctx->variableDeclaration()){
			daclareVariableOnStack(ctx->variableDeclaration());
		}
		else if(ctx->variableDeclarationList()){
			if(ctx->variableDeclarationList()->variableDeclaration())
				daclareVariableOnStack(ctx->variableDeclarationList()->variableDeclaration());
			for(auto vCtx : ctx->variableDeclarationList()->moreVariableDeclaration()){
				daclareVariableOnStack(vCtx->variableDeclaration());
			}
		}
	}
}

void CrystalityRealListener::enterVariableDeclarationStatement(CrystalityParser::VariableDeclarationStatementContext* ctx)
{
	if(m_bGenerateCode)
		m_codeSerializer.AddLine(ProcessLocalVariableDeclaration(ctx->localVariableDeclaration()) + ";");
}

void CrystalityRealListener::enterRelayLambdaDefinition(CrystalityParser::RelayLambdaDefinitionContext* ctx)
{
	if(m_bGenerateCode){
		m_codeSerializer.AddLine("");
		m_codeSerializer.AddLine(m_declaredRelayLambdaFunctions[ctx].second);
	}
}
