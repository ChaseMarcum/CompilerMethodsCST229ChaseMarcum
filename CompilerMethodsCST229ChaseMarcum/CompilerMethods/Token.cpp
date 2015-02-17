/***********************************************************
* Author:					Chase Marcum
* Date Created:				6/5/2014
* Last Modification Date:	6/11/2014
* Lab Number:				CST 320 Lab 1
* Filename:					Token.cpp
*
* Overview:
*	Sets Token
*
*
************************************************************/

#include "Token.h"
#include <iostream>

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
