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

class Rules {

public:
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
	*	  Purpose:  Returns member variable of key
	*
	*     Entry:	n/a
	*
	*     Exit:		Returns member variable of key
	*
	****************************************************************/
	string GetKey();

	/**************************************************************
	*	  Purpose:  Returns member variable of value
	*
	*     Entry:	n/a
	*
	*     Exit:		Returns member variable of value
	*
	****************************************************************/
	string GetValue();

	/**************************************************************
	*	  Purpose:  Returns member variable of element
	*
	*     Entry:	n/a
	*
	*     Exit:		Returns member variable of element
	*
	****************************************************************/
	string GetElements();

private:
	string key_;			// 
	string value_;			// 
	string elements_;		// 
};
#endif