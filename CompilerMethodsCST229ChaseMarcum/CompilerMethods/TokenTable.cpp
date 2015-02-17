/***********************************************************
* Author:					Chase Marcum
* Date Created:				6/5/2014
* Last Modification Date:	6/11/2014
* Lab Number:				CST 320 Lab 1
* Filename:					TokenTable.cpp
*
* Overview:
*	Builds and sets a Token Table.  Set class to sort through
*	Tokens
*
*
************************************************************/

#include "TokenTable.h"

/**************************************************************
*	  Purpose:  Constructor of TokenTable no variable members
*				to set
*
*     Entry:	n/a
*
*     Exit:		n/a
****************************************************************/
TokenTable::TokenTable()
{
}

/**************************************************************
*	  Purpose:  Destructor of TokenTable
*
*     Entry:	n/a
*
*     Exit:		n/a
****************************************************************/
TokenTable::~TokenTable()
{
}

/**************************************************************
*	  Purpose:  Adds Token into tokenTable vector
*
*     Entry:	Token to add to vector
*
*     Exit:		n/a
****************************************************************/
void TokenTable::addToken(Token token)
{
	tokenTableVector.push_back(token);
}
