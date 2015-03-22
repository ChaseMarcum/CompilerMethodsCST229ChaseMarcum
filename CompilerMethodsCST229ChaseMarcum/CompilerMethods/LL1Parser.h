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
#include <set>
#include <stack>
#include <vector>

using namespace std;

class LL1Parser
{
public:
	Rules ruleSet;
	vector<Rules> myRules;
	stack<Token> tokenStack;
	stack<string> ruleStack;

	/**************************************************************
	*	  Purpose:  Constructor of LL1Parser
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	****************************************************************/
	LL1Parser(string fileName, TokenTable tokens);

	/**************************************************************
	*	  Purpose:  Constructor of LL1Parser
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	****************************************************************/
	LL1Parser();

	/**************************************************************
	*	  Purpose:  Constructor of LL1Parser
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	****************************************************************/
	~LL1Parser();
	void AddRules(int ruleNumber);
	bool Run();
};

#endif