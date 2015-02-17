/***********************************************************
* Author:					Chase Marcum
* Date Created:				6/5/2014
* Last Modification Date:	6/11/2014
* Lab Number:				CST 320 Lab 1
* Filename:					Symbol.h
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

#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>
#include <iostream>

using namespace std;

class Symbol
{
public:

	string symbolName;		// Name of Symbol
	string symbolType;		// Data Type of Symbol
	string symbolUse;		// Variable name, constant symbol, 
							// function name, class name, type name, etc.
	string symbolValue;		// Used for constant definitions

	/**************************************************************
	*	  Purpose:  Constructor of Symbol and sets initial
	*				state of variable members
	*
	*     Entry:	string name, string type, string use, string value
	*
	*     Exit:		n/a
	*
	****************************************************************/
	Symbol(string name, string type, string use, string value);

	/**************************************************************
	*	  Purpose:  Default constructor of Symbol no variable
	*				members set
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	*
	****************************************************************/
	Symbol();

	/**************************************************************
	*	  Purpose:  Destructor of Symbol
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	*
	****************************************************************/
	~Symbol();

	/**************************************************************
	*	  Purpose:  Operator overload to compares left-hand side Symbol
	*				to Right-hand side Symbol.
	*
	*     Entry:	string left-hand side Symbol, string Right-hand side
	*				Symbol.
	*
	*     Exit:		Returns true if lhs less than rhs, else false
	*
	****************************************************************/
	friend bool Symbol::operator<(const Symbol& lhs,
		const Symbol& rhs)
	{
		return(lhs.symbolName < rhs.symbolName);
	}

	/**************************************************************
	*	  Purpose:  Searches SymbolTableSet with given string name.
	*				if found then sets the name from fail, to pass.
	*
	*     Entry:	string name
	*
	*     Exit:		returns found located Symbol, if not found returns a
	*				Symbol with string "notFound" in symbolName
	*
	****************************************************************/
	friend bool Symbol::operator==(const Symbol& lhs,
		const Symbol& rhs)
	{
		return(lhs.symbolName == rhs.symbolName);
	}

	/**************************************************************
	*	  Purpose:  Operator overload to compares left-hand side Symbol
	*				to Right-hand side Symbol.
	*
	*     Entry:	string left-hand side Symbol, string Right-hand side
	*				Symbol.
	*
	*     Exit:		Returns true if lhs not equal rhs, else false
	*
	****************************************************************/
	friend bool Symbol::operator!=(const Symbol& lhs,
		const Symbol& rhs)
	{
		return(lhs.symbolName != rhs.symbolName);
	}
};
#endif