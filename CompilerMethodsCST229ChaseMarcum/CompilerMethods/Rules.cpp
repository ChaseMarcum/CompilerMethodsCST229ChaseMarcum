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
Rules::Rules(string passedKey, string passedValue, string passedElements)
{
	key = passedKey;
	value = passedValue;
	elements = passedElements;
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
