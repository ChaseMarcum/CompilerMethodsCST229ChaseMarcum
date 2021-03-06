/***********************************************************
* Author:					Chase Marcum
* Date Created:				2014-06-05
* Last Modification Date:	2015-03-21
* Lab Number:				CST 320 Lab 1
* Filename:					Token.cpp
*
* Overview:
*	Sets Token
*
*
************************************************************/

#include "Token.h"

/**************************************************************
*	  Purpose:  Constructor of Token and sets initial
*				state of variable members
*
*     Entry:	string name, string type
*
*     Exit:		n/a
****************************************************************/
Token::Token(string name, string type, string use, string value)
{
	tokenName	= name;
	tokenType	= type;
	tokenUse	= use;
	tokenValue	= value;
}

/**************************************************************
*	  Purpose:  Default constructor of Token no variable
*				members set
*
*     Entry:  n/a
*
*     Exit:  n/a
****************************************************************/
Token::Token()
{
}

/**************************************************************
*	  Purpose:  Destructor of Token
*
*     Entry:  n/a
*
*     Exit:  n/a
****************************************************************/
Token::~Token()
{
}
