grammar PredaScript;
scripts: (script)* EOF;

script: chainOperation | variableDeclaration | config | issueTxn | debugInfo | viz;
	chainOperation: awaitChain | stepChain | runChain | stopChain | getChainInfo | deployContractOnChain | batchInsertTxnOnChain | setGasLimit;
		awaitChain: 'chain.await';
		stepChain: 'chain.step';
		runChain: 'chain.run';
		stopChain: 'chain.stop';
		getChainInfo: 'chain.info';
		deployContractOnChain: 'chain.deploy' (addressScope | shardScope) contractProperties;
			contractProperties: contractProperty*;
			contractProperty: (predaFile | xtlFile) ('=' jsonParameters)?;
				predaFile: directivePath? identifier '.prd' (':' (NATIVE | WASM))?;
				xtlFile: directivePath? identifier '.xtl';
		batchInsertTxnOnChain: 'chain.batch_insert_txn' varName;
		setGasLimit: 'chain.gaslimit' ('.' GLOBAL)? numberLiteral;

	variableDeclaration: variableAssign | dataReadFromFile;
		variableAssign: varName '=' varValue;
			varName: identifier;
			varValue: identifier | stringLiteral | numberLiteral;
		dataReadFromFile: varName '=' 'csv.from' '(' csvfilePath ')';
			csvfilePath: directivePath? fileName '.csv';

	config: configState | configAddress | configRandomizer;
		configState: setContractState | updateState | tokenState | loadState | saveState;
			setContractState: 'state.set' contractId '.' stateScope scope? jsonParameters;
				stateScope: GLOBAL | SHARD | ADDRESS;
			updateState: 'state.update' contractId '.' stateScope scope? jsonParameters;
			tokenState: mintToken;
				mintToken: 'state' '.' 'token' identifier tokenSymbol 'by' contractId;
					tokenSymbol: (identifier | '-')*;
			loadState: 'state.load' '<' stateScope '>' jsonFilePath;
				jsonFilePath: directivePath? fileName ('.json')?;
			saveState: 'state.save' stateScope '.' (contractId | ALL) fileName;
		configAddress: 'allocate.address' numberLiteral?;
		configRandomizer: RANDOM '.' 'reseed' numberLiteral?;

	issueTxn: (txnReturnInfo '=')? contractId '.' functionName count? scope? jsonParameters? ('<=' suppliedTokens)?;
		txnReturnInfo: identifier ('['']')?;
		contractId: contractName | cvid;
			contractName: (dappName = identifier '.')? identifier;
			cvid: numberLiteral;
		functionName: identifier;
		count: '*' numberLiteral;
		scope: shardScope | addressScope;
		shardScope: '#g' | ('#' (numberLiteral | identifier | RANDOM | ALL));
		addressScope: '@' (numberLiteral | identifier | RANDOM | ALL | ed25519Address);
		jsonParameters: '{' jsonParameter? (',' jsonParameter)* '}';
			jsonParameter: jsonKey ':' jsonValue;
				jsonKey: identifier | concreteValue;
				jsonValue: jsonParameters | primaryValue | identifier;
					primaryValue: arrayValue | concreteValue | toBeAssignedValue;
						arrayValue: '[' jsonValue? (',' jsonValue)* ']';
						concreteValue: numberLiteral | stringLiteral | boolLiteral | hexLiteral;
						toBeAssignedValue: '$' (addressScope | bigintRandom | intExpression) '$';
							bigintRandom: BIGINT '.' RANDOM '(' numberLiteral ')';
							intExpression locals [int type = -1]
							: intExpression '*' intExpression		{$type = 0;}
							| intExpression '/' intExpression		{$type = 1;}
							| intExpression '+' intExpression		{$type = 2;}
							| intExpression '-' intExpression		{$type = 3;}
							| intRandom								{$type = 4;}
							| numberLiteral							{$type = 5;};						
								intRandom: RANDOM (randomRange)?;
									randomRange: '(' min = intExpression ',' max = intExpression ')';
		suppliedTokens: '(' token? (',' token)* ')';
			token: (numberLiteral | ('$' intExpression '$')) identifier;

	debugInfo: logInfo | timeInfo;
		logInfo: normalLog | logHighlight | logWarning | logError;
			normalLog: 'log' stringLiteral;
			logHighlight : 'log.highlight' stringLiteral;
			logWarning: 'log.warning' stringLiteral;
			logError: 'log.error' stringLiteral;
		timeInfo: stopWatchRestart | stopWatchReport;
			stopWatchRestart: 'stopwatch.restart';
			stopWatchReport: 'stopwatch.report';

	viz: vizBlock | vizAddr | vizShard | vizTxn | vizTrace | vizSection | vizProfiling | vizUintScope;
		vizBlock: 'viz.block' shardScope (':' numberLiteral)?;
		vizAddr: 'viz.addr' addressScope contractName?;
		vizShard: 'viz.shard' shardScope contractName?;
		vizTxn: 'viz.txn' txnReturnInfo ('[' numberLiteral ']')?;
		vizTrace: 'viz.trace' txnReturnInfo ('[' numberLiteral ']')?;
		vizSection: 'viz.section' stringLiteral;
		vizProfiling: 'viz.profiling';
		vizUintScope: 'viz.uint_scope' uintScope contractName ':' scopeTarget;
			uintScope: '#' (ALL | numberLiteral);
			scopeTarget: ALL | numberLiteral;


numberLiteral: ('-') ? DecimalNumber;
hexLiteral: HexNumber;
stringLiteral: StringLiteral;
boolLiteral: TrueKeyword | FalseKeyword;
ed25519Address: Ed25519Address;
identifier: Identifier;
fileName: (Identifier | '-')*;
directivePath: WINPATH | UNIXPATH;

/*=======================================================lexer part=======================================================*/
WASM: 'wasm' | 'WASM';
NATIVE: 'native' | 'NATIVE';
RANDOM: 'random';
BIGINT: 'bigint';
ALL: 'all';
GLOBAL: 'global';
SHARD: 'shard';
ADDRESS: 'address';
TrueKeyword: 'true';
FalseKeyword: 'false';

DecimalNumber: ( DecimalDigits | (DecimalDigits? '.' DecimalDigits) ) ( [eE] DecimalDigits )?;
	fragment DecimalDigits: [0-9] ([0-9])*;
HexNumber : '0' [xX] HexCharacter*;
	fragment HexCharacter: [0-9A-Fa-f];
StringLiteral: '"' StringCharacter* '"';
	fragment StringCharacter: ~["\r\n\\] | ('\\' .);
Ed25519Address: [a-z0-9]+ ':ed25519';

Identifier: IdentifierStart IdentifierPart*;
	fragment IdentifierStart: [a-zA-Z_];
	fragment IdentifierPart: [a-zA-Z0-9_];

WINPATH: WIN_ABSOLUTE_PATH | WIN_REALATIVE_PATH;
	WIN_ABSOLUTE_PATH: DRIVE? WIN_SLASH (DIRNAME WIN_SLASH)*;
	WIN_REALATIVE_PATH: (DIRNAME WIN_SLASH)+;
		fragment DRIVE: [a-zA-Z] ':';
		fragment WIN_SLASH: '\\';
		fragment DIRNAME: FILENAME* | '.' | '..';
		fragment FILENAME: (Identifier | '-');
UNIXPATH: UNIX_ABSOLUTE_PATH | UNIX_REALATIVE_PATH;
	UNIX_ABSOLUTE_PATH: UNIX_SLASH (DIRNAME UNIX_SLASH)*;
	UNIX_REALATIVE_PATH: (DIRNAME UNIX_SLASH)+;
		fragment UNIX_SLASH: '/';

// error texts
NotDefinedValue: '$~' Identifier '$';

// skip texts
NewLineBackSlash: ('\\\n' | '\\\r\n') ->skip;
WS: [ \t\r\n\u000C]+ -> skip;
CommentSingleLine: '//' ~[\r\n]* -> channel(HIDDEN);
CommentMultiLine: '/*' .*? '*/' -> channel(HIDDEN);