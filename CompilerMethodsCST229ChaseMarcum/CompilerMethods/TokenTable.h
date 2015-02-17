#pragma once
/***********************************************************
* Author:					Chase Marcum
* Date Created:				6/5/2014
* Last Modification Date:	6/11/2014
* Lab Number:				CST 320 Lab 1
* Filename:					TokenTable.h
*
* Overview:
*	Builds and sets a Token Table.  Set class to sort through
*	Tokens
*
*
************************************************************/

#ifndef TOKENTABLE_H
#define TOKENTABLE_H
#include "Token.h"
#include <string>
#include <vector>

using namespace std;

class TokenTable
{
public:

	vector<Token> tokenTableVector;		// Vector of Tokens

	/**************************************************************
	*	  Purpose:  Constructor of TokenTable no variable members
	*				to set
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	****************************************************************/
	TokenTable();

	/**************************************************************
	*	  Purpose:  Destructor of TokenTable
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	****************************************************************/
	~TokenTable();

	/**************************************************************
	*	  Purpose:  Adds Token into tokenTable vector
	*
	*     Entry:	Token to add to vector
	*
	*     Exit:		n/a
	****************************************************************/
	void addToken(Token token);
};

#endif