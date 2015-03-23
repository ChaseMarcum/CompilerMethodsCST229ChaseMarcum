/***********************************************************
* Author:					Chase Marcum
* Date Created:				2015-01-03
* Last Modification Date:	2015-03-22
* Lab Number:				CST 320 Lab 3
* Filename:					Rules.cpp
*
* Overview:
*	Sets Rules outline.
*
************************************************************/

#include "Rules.h"

/**************************************************************
*	  Purpose:  Constructor of Rules and sets initial
*				state of variable members
*
*     Entry:	string key, string value, string elements
*
*     Exit:		n/a
*
****************************************************************/
Rules::Rules(string key, string value, string elements)
{
	key_ = key;
	value_ = value;
	elements_ = elements;
}

/**************************************************************
*	  Purpose:  Default constructor for Rules no variable
*				members set
*
*     Entry:	n/a
*
*     Exit:		n/a
*
****************************************************************/
Rules::Rules()
{
}

/**************************************************************
*	  Purpose:  Destructor of Rules
*
*     Entry:	n/a
*
*     Exit:		n/a
*
****************************************************************/
Rules::~Rules()
{
}

/**************************************************************
*	  Purpose:  
*
*     Entry:	n/a
*
*     Exit:		n/a
*
****************************************************************/
string Rules::GetKey() {
	return key_;
}

/**************************************************************
*	  Purpose:
*
*     Entry:	n/a
*
*     Exit:		n/a
*
****************************************************************/
string Rules::GetValue() {
	return value_;
}

/**************************************************************
*	  Purpose:
*
*     Entry:	n/a
*
*     Exit:		n/a
*
****************************************************************/
string Rules::GetElements() {
	return elements_;
}
