/***********************************************************
* Author:					Chase Marcum
* Date Created:				2014-03-01
* Last Modification Date:	2015-02-02
* Lab Number:				CST 320 Compiler Method
* Filename:					RecursiveDescentParser.h
*
* Overview:
*	A top-down recursive descent parser.
*
* Input:
*	List of tokens from lexical analyzer.
*
* Output:
*	Yes or No.
*
************************************************************/

#ifndef RECURSIVEDESCENTPARSER_H
#define RECURSIVEDESCENTPARSER_H
#include "TokenTable.h"
#include "SymbolTable.h"
#include <iostream>
#include <string>
#include <set>

class RecursiveDescentParser
{
public:

	TokenTable _tokenTable;
	Token _token;
	vector<Token>::iterator _tokenTableIterator;
	vector<Token>::iterator _tempTokenTableIterator;
	vector<Token>::iterator _endOfTokenTableIterator;
	SymbolTable _symbolTable;
	Symbol _symbol;
	set<Symbol>::iterator _symbolTableIterator;
	set<Symbol>::iterator _tempSymbolTableIterator;
	set<Symbol>::iterator _endOfSymbolTableIterator;

	bool syntaxError = false;

	RecursiveDescentParser(TokenTable passedTokenTable, SymbolTable passedSymbolTable);
	RecursiveDescentParser();
	~RecursiveDescentParser();

	bool Start(TokenTable passedTokenTable, SymbolTable passedSymbolTable);

	/**************************************************************
	*	  Purpose:  Checks if Token is a vailid JavaScript
	*				Declaration Statement
	*
	*     Entry:	The current Token
	*
	*     Exit:		A Boolean if Token is an valid Declaration Statement
	****************************************************************/
	bool isDeclarationStatement();

	/**************************************************************
	*	  Purpose:  Checks if Token is a vailid JavaScript
	*				Function Statement
	*
	*     Entry:	The current Token
	*
	*     Exit:		A Boolean if Token is an valid Function Statement
	****************************************************************/
	bool isFunctionStatemant();

	/**************************************************************
	*	  Purpose:  Checks if Token is a vailid JavaScript
	*				For Loop Statement
	*
	*     Entry:	The current Token
	*
	*     Exit:		A Boolean if Token is an valid For Loop Statement
	****************************************************************/
	bool isForLoopStatement();

	/**************************************************************
	*	  Purpose:  Checks if Token is a vailid JavaScript
	*				Increment Or Decrement Statement
	*
	*     Entry:	The current Token
	*
	*     Exit:		A Boolean if Token is an valid Increment Or
	*				Decrement Statement
	****************************************************************/
	bool isIncrementOrDecrementStatement();

	/**************************************************************
	*	  Purpose:  Checks if Token is a vailid JavaScript
	*				Input Or Output Statement
	*
	*     Entry:	The current Token
	*
	*     Exit:		A Boolean if Token is an valid symbol Input Or
	*				Output Statement
	****************************************************************/
	bool isInputOrOutputStatement();

	/**************************************************************
	*	  Purpose:  Checks if Token is a vailid JavaScript
	*				Return Statement
	*
	*     Entry:	The current Token
	*
	*     Exit:		A Boolean if Token is an valid Return Statement
	****************************************************************/
	bool isReturnStatement();

	/**************************************************************
	*	  Purpose:  Checks if Token is a vailid JavaScript
	*				RELOP Statement
	*
	*     Entry:	The current Token
	*
	*     Exit:		A Boolean if Token is an valid RELOP Statement
	****************************************************************/
	bool isRELOPStatement();

	/**************************************************************
	*	  Purpose:  Checks if Token is a vailid JavaScript
	*				Variable List
	*
	*     Entry:	The current Token
	*
	*     Exit:		A Boolean if Token is an valid Variable List
	****************************************************************/
	bool isVariableList();

	/**************************************************************
	*	  Purpose:  Checks if Token is a vailid JavaScript Variable
	*
	*     Entry:	The current Token
	*
	*     Exit:		A Boolean if Token is an valid Variable
	****************************************************************/
	bool isVariable();

	/**************************************************************
	*	  Purpose:  Checks if Token is a vailid JavaScript Identifier
	*
	*     Entry:	The current Token
	*
	*     Exit:		A Boolean if Token is an valid Identifier
	****************************************************************/
	bool isIdentifier();

	/**************************************************************
	*	  Purpose:  Checks if Token is a vailid JavaScript Type
	*
	*     Entry:	The current Token
	*
	*     Exit:		A Boolean if Token is an valid Type
	****************************************************************/
	bool isType();

	/**************************************************************
	*	  Purpose:  Checks if Token is a vailid JavaScript Value
	*
	*     Entry:	The current Token
	*
	*     Exit:		A Boolean if Token is an valid Value
	****************************************************************/
	bool isValue();
};
#endif
