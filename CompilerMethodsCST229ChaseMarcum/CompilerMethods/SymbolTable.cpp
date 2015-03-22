/***********************************************************
* Author:					Chase Marcum
* Date Created:				2014-06-05
* Last Modification Date:	2015-03-21
* Lab Number:				CST 320 Lab 1
* Filename:					SymbolTable.cpp
*
* Overview:
*	Builds a Symbol Table set, adds Symbols to Symbol Table set,
*	and compares Symbols.
*
************************************************************/

#include "SymbolTable.h"

/**************************************************************
*	  Purpose:  Constructor of SymbolTable class no variable members
*				to set
*
*     Entry:	n/a
*
*     Exit:		n/a
*
****************************************************************/
SymbolTable::SymbolTable()
{
}

/**************************************************************
*	  Purpose:  Destructor of SymbolTable class
*
*     Entry:	n/a
*
*     Exit:		n/a
*
****************************************************************/
SymbolTable::~SymbolTable()
{
}

/**************************************************************
*	  Purpose:  Adds Symbol into a set of Symbols, SymbolTableSet
*
*     Entry:	Symbol symbol
*
*     Exit:		n/a
*
****************************************************************/
void SymbolTable::addSymbol(Symbol symbol)
{
	SymbolTableSet.insert(symbol);
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
Symbol SymbolTable::findSymbol(string name)
{
	Symbol locateSymbol;
	Symbol searchSymbol = Symbol(name, "", "", "");

	set<Symbol>::iterator symbolIterator = SymbolTableSet.find(searchSymbol);

	if (symbolIterator == SymbolTableSet.end())
	{
		return Symbol("failed", "", "", "");
	}
	else
	{
		locateSymbol = Symbol(symbolIterator->symbolName,
			symbolIterator->symbolType,
			symbolIterator->symbolUse,
			symbolIterator->symbolValue);
	}

	return locateSymbol;
}