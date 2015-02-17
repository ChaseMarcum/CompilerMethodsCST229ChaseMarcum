/***********************************************************
* Author:					Chase Marcum
* Date Created:				6/5/2014
* Last Modification Date:	6/11/2014
* Lab Number:				CST 320 Lab 1
* Filename:					Token.h
*
* Overview:
*	Sets Token
*
*
************************************************************/

#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>

using namespace std;

class Token
{
public:

	string tokenName;		// Name of Token
	string tokenType;		// Type of Token
	string tokenUse;		// Use of Token
	string tokenValue;		// Value of Token

	/**************************************************************
	*	  Purpose:  Constructor of Token and sets initial
	*				state of variable members
	*
	*     Entry:  string name, string type
	*
	*     Exit:  n/a
	****************************************************************/
	Token(string name, string type, string use = "", string value = "");

	/**************************************************************
	*	  Purpose:  Default constructor of Token no variable
	*				members set
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	****************************************************************/
	Token();

	/**************************************************************
	*	  Purpose:  Destructor of Token
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	****************************************************************/
	~Token();

	/**************************************************************
	*	  Purpose:  Compares left-hand side Token to Right-hand side
	*				Token.
	*
	*     Entry:	string left-hand side Token, string Right-hand side
	*				Token.
	*
	*     Exit:		Returns true if lhs less than rhs, else false
	****************************************************************/
	friend bool Token::operator<(const Token& lhs,
		const Token& rhs)
	{
		return(lhs.tokenName < rhs.tokenName);
	}
};
#endif