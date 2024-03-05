grammar Preda;
predaSource
  : (directive)* contractDefinition EOF ;

directive
  : importDirective;

importDirective
  : ImportKeyword (dAppName = identifier '.')? contractName = identifier (AsKeyword alias = identifier)? ';';

annotation
  : '[' annotationItem? (',' annotationItem)* ']';

annotationItem
  : identifier '=' (BooleanLiteral | DecimalIntegerLiteral | DecimalFloatLiteral | HexIntegerLiteral | StringLiteral);

DoxygenSingle
  : [\t]? '///' .*? [\r\n];
DoxygenMulti
  : '/**' .*? '**/';
doxygen
  : DoxygenSingle+ | DoxygenMulti ;

contractDefinition
  : doxygen? annotation? 'contract' identifier (ImplementsKeyword interfaceRef (',' interfaceRef)*)? '{' contractPart* '}';
  
interfaceRef
  : (contractName = identifier '.')? interfaceName = identifier;

contractPart
  : stateVariableDeclaration
  | constVariableDeclaration
  | structDefinition
  | enumDefinition
  | interfaceDefinition
  | functionDefinition;

stateVariableDeclaration
  : doxygen? annotation? scope? typeName identifier ';';

constVariableDeclaration
  : ConstantKeyword typeName identifier '=' expression ';'; 

scope
  : '@'(ShardKeyword | GlobalKeyword | AddressKeyword | UintType);

structDefinition
  : doxygen? annotation? StructKeyword identifier '{'
       (variableDeclaration ';')*
    '}' ;

interfaceDefinition
  : InterfaceKeyword identifier '{'
       (functionDeclaration ';')*
    '}' ;

enumDefinition
  : doxygen? annotation? EnumKeyword identifier '{' identifier? (',' identifier)* '}' ;

functionDefinition
  : functionDeclaration '{' statement* '}' ;
  
functionDeclaration
  : doxygen? annotation? scope? FunctionKeyword functionReturnTypeName? identifier '(' functionParameterList ')' accessSpecifier* ConstantKeyword? ;

functionReturnTypeName
  : ConstantKeyword? typeName;

functionParameterList
  : ( functionParameter (',' functionParameter)* )? ;

functionParameter
  : ConstantKeyword? typeName identifier ;

accessSpecifier
  : (PublicKeyword | ExportKeyword);

variableDeclaration
  : typeName identifier;

typeNameOrAuto
  : ConstantKeyword? (typeName | AutoKeyword);
  
typeName
  : fundamentalTypeName
  | builtInContainerTypeName
  | userDefinedTypeName;

fundamentalTypeName
  : 'bool' | IntType | UintType | FloatType | 'string' | 'blob' | 'hash' | 'bigint' | AddressKeyword;

builtInContainerTypeName
  : mapTypeName | arrayTypeName;

mapKeyTypeName
  : 'bool' | IntType | UintType | FloatType | 'blob' | 'hash' | AddressKeyword;

mapTypeName
  : 'map' '<' mapKeyTypeName ',' typeName '>';

arrayTypeName
  : 'array' '<' typeName '>';
  
userDefinedTypeName
  : (identifier '.')* identifier ;       //append "( '.' identifier )*" to support nested type definition

userBlockStatement
  : '{' statement* '}' ;

statement
  : ifStatement
  | whileStatement
  | forStatement
  | userBlockStatement
  | doWhileStatement
  | continueStatement
  | breakStatement
  | returnStatement
  | relayStatement
  | variableDeclarationStatement
  | expressionStatement ;

expressionStatement
  : expression ';' ;

ifStatement
  : ifWithBlock elseIfWithBlock* elseWithBlock?;

ifWithBlock
  : IfKeyword '(' expression ')' '{' statement* '}';

elseWithBlock
  : ElseKeyword '{' statement* '}';

elseIfWithBlock
  : ElseKeyword IfKeyword '(' expression ')' '{' statement* '}';

whileStatement
  : 'while' '(' expression ')' '{' statement* '}';

relayStatement
  : RelayKeyword '@' relayType ((identifier '(' functionCallArguments ')' ';') | relayLambdaDefinition);
  
relayType
  : (expression | ShardsKeyword | GlobalKeyword | NextKeyword);

relayLambdaDefinition
  : '(' (relayLambdaParameter (',' relayLambdaParameter)*)? ')' ConstantKeyword? '{' statement* '}';

relayLambdaParameter
  : (typeNameOrAuto identifier '=' expression) | ('^' identifier) ;
  
forStatement
  : 'for' '(' (localVariableDeclaration | firstExpression = expression)? ';' secondExpression = expression? ';' thirdExpression = expression? ')' '{' statement* '}';

doWhileStatement
  : 'do' '{' statement* '}' 'while' '(' expression ')' ';' ;

continueStatement
  : 'continue' ';' ;

breakStatement
  : 'break' ';' ;

returnStatement
  : 'return' expression? ';';

variableDeclarationStatement
  : localVariableDeclaration ';' ;

localVariableDeclaration
  : typeNameOrAuto identifier ('=' expression)? ;

//identifierList
//  : '(' ( identifier? ',' )* identifier? ')' ;

expression locals [int expressionType = -1]
  : expression '++'                                                                                            {$expressionType = 0;}
  | expression '--'                                                                                            {$expressionType = 1;}
  | expression '[' expression ']'                                                                              {$expressionType = 2;}
  | expression '(' functionCallArguments ')'                                                                   {$expressionType = 3;}
  | expression '.' identifier                                                                                  {$expressionType = 4;}
  | '(' expression ')'                                                                                         {$expressionType = 5;}
  | '++' expression                                                                                            {$expressionType = 6;}
  | '--' expression                                                                                            {$expressionType = 7;}
  | '+' expression                                                                                             {$expressionType = 8;}
  | '-' expression                                                                                             {$expressionType = 9;}
  | '!' expression                                                                                             {$expressionType = 10;}
  | '~' expression                                                                                             {$expressionType = 11;}
  | DeployKeyword expression '(' functionCallArguments ')'                                                     {$expressionType = 12;}
  | expression '*' expression                                                                                  {$expressionType = 13;}
  | expression '/' expression                                                                                  {$expressionType = 14;}
  | expression '%' expression                                                                                  {$expressionType = 15;}
  | expression '+' expression                                                                                  {$expressionType = 16;}
  | expression '-' expression                                                                                  {$expressionType = 17;}
  | expression '<<' expression                                                                                 {$expressionType = 18;}
  | expression '>' '>' expression                                                                              {$expressionType = 19;}
  | expression '<' expression                                                                                  {$expressionType = 20;}
  | expression '>' expression                                                                                  {$expressionType = 21;}
  | expression '<=' expression                                                                                 {$expressionType = 22;}
  | expression '>=' expression                                                                                 {$expressionType = 23;}
  | expression '==' expression                                                                                 {$expressionType = 24;}
  | expression '!=' expression                                                                                 {$expressionType = 25;}
  | expression '&' expression                                                                                  {$expressionType = 26;}
  | expression '^' expression                                                                                  {$expressionType = 27;}
  | expression '|' expression                                                                                  {$expressionType = 28;}
  | expression '&&' expression                                                                                 {$expressionType = 29;}
  | expression '||' expression                                                                                 {$expressionType = 30;}
  | expression '?' expression ':' expression                                                                   {$expressionType = 31;}
  | expression '=' expression                                                                                  {$expressionType = 32;}
  | expression '+=' expression                                                                                 {$expressionType = 33;}
  | expression '-=' expression                                                                                 {$expressionType = 34;}
  | expression '*=' expression                                                                                 {$expressionType = 35;}
  | expression '/=' expression                                                                                 {$expressionType = 36;}
  | expression '%=' expression                                                                                 {$expressionType = 37;}
  | expression '<<=' expression                                                                                {$expressionType = 38;}
  | expression '>>=' expression                                                                                {$expressionType = 39;}
  | expression '&=' expression                                                                                 {$expressionType = 40;}
  | expression '^=' expression                                                                                 {$expressionType = 41;}
  | expression '|=' expression                                                                                 {$expressionType = 42;}
  | primaryExpression                                                                                          {$expressionType = 43;}
  ;

primaryExpression
  : BooleanLiteral
  | DecimalIntegerLiteral
  | DecimalFloatLiteral
  | HexIntegerLiteral
  | DecimalBigIntegerLiteral
  | HexBigIntegerLiteral
  | StringLiteral
  | AddressLiteral
  | HashLiteral
  | identifier
  | fundamentalTypeName
  | builtInContainerTypeName;

functionCallArguments
  : (expression (',' expression)*)? ;

identifier
  : Identifier ;

BreakKeyword : 'break' ;
ConstantKeyword : 'const' ;
ContinueKeyword : 'continue' ;
RelayKeyword : 'relay';
SupplyKeyword : 'supply';
IfKeyword : 'if';
ElseKeyword : 'else';
ShardKeyword : 'shard';
ShardsKeyword : 'shards';
GlobalKeyword : 'global';
AddressKeyword: 'address';
AutoKeyword : 'auto';
MinerKeyword : 'miner';
StructKeyword : 'struct';
EnumKeyword : 'enum';
ContractKeyword : 'contract';
ImportKeyword : 'import';
FunctionKeyword : 'function';
PublicKeyword : 'public';
ExportKeyword : 'export';
AsKeyword : 'as';
UsingKeyword : 'using';
InterfaceKeyword : 'interface';
ImplementsKeyword : 'implements';
DeployKeyword : 'deploy';
ConstructorKeyword : 'constructor';
NextKeyword : 'next';

FloatType
  : 'float256' | 'float512' | 'float1024' ;

IntType
  : 'int8' | 'int16' | 'int32' | 'int64' | 'int128' | 'int256' | 'int512';

UintType
  : 'uint8' | 'uint16' | 'uint32' | 'uint64' | 'uint128' | 'uint256' | 'uint512';

BooleanLiteral
  : 'true' | 'false' ;

DecimalFloatLiteral
  : DecimalDigit* '.' DecimalDigit+ FloatLiteralSuffix?;

DecimalIntegerLiteral
  : DecimalIntegerLiteralBody IntegerLiteralSuffix?;

DecimalIntegerLiteralBody
  : DecimalDigit+;
  
AddressLiteral
  : Base32Len58':'('ed25519'|'contract');

HashLiteral
  : Base32Len52':''hash';

fragment
Base32Len58
  : Base32Len7 Base32Len7 Base32Len7 Base32Len7 Base32Len7 Base32Len7 Base32Len7 Base32Len7 Base32 Base32;

fragment
Base32Len52
  : Base32Len7 Base32Len7 Base32Len7 Base32Len7 Base32Len7 Base32Len7 Base32Len7 Base32 Base32 Base32;

fragment
Base32Len7
  : Base32 Base32 Base32 Base32 Base32 Base32 Base32;

fragment
Base32
  : [0-9A-Za-z@];

fragment
IntegerLiteralSuffix
  : ('u' | 'i') ('8' | '16' | '32' | '64' | '128' | '256' | '512')?;

fragment
FloatLiteralSuffix
  : 'f' ('256' | '512' | '1024')?;
fragment
DecimalDigit
  : [0-9] ;

HexIntegerLiteral
  : HexIntegerLiteralBody IntegerLiteralSuffix?;

HexIntegerLiteralBody
  : '0' [xX] HexDigit ( HexDigit )*;

DecimalBigIntegerLiteral
  : DecimalIntegerLiteralBody 'ib';

HexBigIntegerLiteral
  : HexIntegerLiteralBody 'ib';

fragment
HexDigit
  : [0-9A-Fa-f] ;

Identifier
  : IdentifierStart IdentifierBody* ;

fragment
IdentifierStart
  : [a-zA-Z_] ;

fragment
IdentifierBody
  : [a-zA-Z0-9_] ;

StringLiteral
  : '"' StringCharacter* '"';

fragment
StringCharacter
  : ~["\r\n\\] | ('\\' .) ;

WS
  : [ \t\r\n\u000C]+ -> skip ;

COMMENT
  : '/*' .*? '*/' -> channel(HIDDEN) ;

LINE_COMMENT
  : '//' ~[\r\n]* -> channel(HIDDEN) ;