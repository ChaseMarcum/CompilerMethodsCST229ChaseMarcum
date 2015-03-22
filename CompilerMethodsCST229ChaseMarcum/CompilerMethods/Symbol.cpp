/***********************************************************
* Author:					Chase Marcum
* Date Created:				2014-06-05
* Last Modification Date:	2015-03-21
* Lab Number:				CST 320 Lab 1
* Filename:					Symbol.cpp
*
* Overview:
*	A symbol table to store preprocessor-defined symbols and
*   constants.
*
*	Symbol table stores information about a symbol:
*			- Name
*			- Type (data type)
*			- Use (variable name, constant symbol, function name,
*				class name, type name, etc.)
*			- Value (used for constant definitions)
*
************************************************************/

#include "Symbol.h"

/**************************************************************
*	  Purpose:  Constructor of Symbol and sets initial
*				state of variable members
*
*     Entry:	string name, string type, string use, string value
*
*     Exit:		n/a
*
****************************************************************/
Symbol::Symbol(string name, string type, string use, string value)
{
	symbolName	= name;		// Name of Symbol
	symbolType	= type;		// Data Type of Symbol
	symbolUse	= use;		/* Variable name, constant symbol, function
							   name, class name, type name, etc. */
	symbolValue = value;	// Used for constant definitions
}

/**************************************************************
*	  Purpose:  Default constructor for Symbol no variable
*				members set
*
*     Entry:	n/a
*
*     Exit:		n/a
*
****************************************************************/
Symbol::Symbol()
{
}

/**************************************************************
*	  Purpose:  Destructor of Symbol
*
*     Entry:	n/a
*
*     Exit:		n/a
*
****************************************************************/
Symbol::~Symbol()
{
}