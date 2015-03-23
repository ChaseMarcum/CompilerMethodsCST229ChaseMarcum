/***********************************************************
* Author:					Chase Marcum
* Date Created:				2014-03-01
* Last Modification Date:	2015-03-22
* Lab Number:				CST 320 Lab 2
* Filename:					LanguageChecker.h
*
* Overview:
*	A top-down recursive descent parser.
*
* Input:
*	List of tokens from lexical analyzer.
*
* Output:
*	True or False
*
************************************************************/

#ifndef RECURSIVEDESCENTPARSER_H
#define RECURSIVEDESCENTPARSER_H
#include "TokenTable.h"
#include "SymbolTable.h"
#include "Parser.h"
#include <set>

using namespace std;

class LanguageChecker {

public:
	TokenTable tokenTable_;

	Token token_;
	vector<Token>::iterator tokenTableIterator_;
	vector<Token>::iterator tempTokenTableIterator_;
	vector<Token>::iterator endOfTokenTableIterator_;

	SymbolTable symbolTable_;

	Symbol symbol_;
	set<Symbol>::iterator symbolTableIterator_;
	set<Symbol>::iterator tempSymbolTableIterator_;
	set<Symbol>::iterator endOfSymbolTableIterator_;

	bool syntaxError = false;

	/**************************************************************
	*	  Purpose:  Constructor of LanguageChecker and sets initial
	*				variable members
	*
	*     Entry:	string key, string value, string elements
	*
	*     Exit:		n/a
	*
	****************************************************************/
	LanguageChecker(TokenTable tokenTable, SymbolTable &symbolTable);

	/**************************************************************
	*	  Purpose:  Default constructor for LanguageChecker no variable
	*				members set
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	*
	****************************************************************/
	LanguageChecker();

	/**************************************************************
	*	  Purpose:  Destructor of LanguageChecker
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	*
	****************************************************************/
	~LanguageChecker();

	/**************************************************************
	*	  Purpose:
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	*
	****************************************************************/
	void AddSymbol(Symbol symbol);

	/**************************************************************
	*	  Purpose:
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	*
	****************************************************************/
	bool Start();

	/**************************************************************
	*	  Purpose:  Checks if Token is a vailid JavaScript
	*			    Statement List
	*
	*     Entry:	The current Token
	*
	*     Exit:		A Boolean if Token is an valid Statement List
	****************************************************************/
	bool isStatementList();

	/**************************************************************
	*	  Purpose:  Checks if Token is a vailid JavaScript
	*				Statement
	*
	*     Entry:	The current Token
	*
	*     Exit:		A Boolean if Token is an valid Statement
	****************************************************************/
	bool isStatement();

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
	*				If Else Statement
	*
	*     Entry:	The current Token
	*
	*     Exit:		A Boolean if Token is an valid If Else Statement
	****************************************************************/
	bool isIfElseStatement();

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
	bool isComparativeStatement();

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
