/***********************************************************
* Author:					Chase Marcum
* Date Created:				2014-03-01
* Last Modification Date:	2015-03-21
* Lab Number:				CST 320 Lab 3
* Filename:					LL1Parser.h
*
* Overview:  Implementation of the LL1Parser.
*
* Input:
*
* Output:
*
************************************************************/


#ifndef LL1PARSER_H
#define LL1PARSER_H
#include <string>
#include "Rules.h"
#include "TokenTable.h"
#include <stack>
#include <vector>

using namespace std;

class LL1Parser {
public:
	Rules ruleSet;
	vector<Rules> rules_;
	stack<Token> tokenStack_;
	stack<string> ruleStack_;

	/**************************************************************
	*	  Purpose:  Constructor of LL1Parser and sets initial
	*				state of variable members
	*
	*     Entry:	string filName, TokenTable tokens
	*
	*     Exit:		n/a
	*
	****************************************************************/
	LL1Parser(string fileName, TokenTable tokens);

	/**************************************************************
	*	  Purpose:  Default constructor for LL1Parser no variable
	*				members set
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	*
	****************************************************************/
	LL1Parser();

	/**************************************************************
	*	  Purpose:  Destructor of LL1Parser
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	*
	****************************************************************/
	~LL1Parser();

	/**************************************************************
	*	  Purpose:  Adds element to Rule
	*
	*     Entry:	The int of rule number
	*
	*     Exit:		n/a
	*
	****************************************************************/
	void AddRule(int ruleNumber);

	/**************************************************************
	*	  Purpose:  Compares the rules table with the current input
	*				pushes rules onto the rule stack when appropriate.
	*				Returns true if rules are met, and false if they
	*				are not.
	*
	*     Entry:	The current Token
	*
	*     Exit:		A Boolean if Token is an valid RELOP Statement
	****************************************************************/
	bool Run();
};

#endif