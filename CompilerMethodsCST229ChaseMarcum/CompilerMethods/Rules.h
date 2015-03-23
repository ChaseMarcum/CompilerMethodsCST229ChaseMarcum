/***********************************************************
* Author:					Chase Marcum
* Date Created:				2015-01-03
* Last Modification Date:	2015-03-22
* Lab Number:				CST 320 Lab 3
* Filename:					Rule.h
*
* Overview:
*	Sets Rules outline.
*
************************************************************/

#ifndef RULES_H
#define RULES_H
#include <string>

using namespace std;

class Rules
{
public:
	string key;
	string value;
	string elements;

	/**************************************************************
	*	  Purpose:  Constructor of Rules and sets initial
	*				state of variable members
	*
	*     Entry:	string key, string value, string elements
	*
	*     Exit:		n/a
	*
	****************************************************************/
	Rules(string passedKey, string passedValue, string passedElements);

	/**************************************************************
	*	  Purpose:  Default constructor for Rules no variable
	*				members set
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	*
	****************************************************************/
	Rules();

	/**************************************************************
	*	  Purpose:  Destructor of Rules
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	*
	****************************************************************/
	~Rules();

	/**************************************************************
	*	  Purpose:
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	*
	****************************************************************/
	string GetKey();

	/**************************************************************
	*	  Purpose:
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	*
	****************************************************************/
	string GetValue();

	/**************************************************************
	*	  Purpose:
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	*
	****************************************************************/
	string GetElements();

private:
	string key_;			// 
	string value_;			// 
	string elements_;		// 
};
#endif