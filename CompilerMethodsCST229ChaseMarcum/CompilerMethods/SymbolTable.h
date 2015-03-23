/***********************************************************
* Author:					Chase Marcum
* Date Created:				6/5/2014
* Last Modification Date:	6/11/2014
* Lab Number:				CST 320 Lab 1
* Filename:					SymbolTable.h
*
* Overview:
*	Builds a Symbol Table set, adds Symbols to Symbol Table set,
*	and compares Symbols.
*
************************************************************/

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "Symbol.h"
#include <string>
#include <set>

using namespace std;

class SymbolTable {

public:

	set<Symbol> SymbolTableSet;		// A set container of Symbols

	/**************************************************************
	*	  Purpose:  Constructor of SymbolTable class no variable members
	*				to set
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	****************************************************************/
	SymbolTable();

	/**************************************************************
	*	  Purpose:  Destructor of SymbolTable class
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	*
	****************************************************************/
	~SymbolTable();

	/**************************************************************
	*	  Purpose:  Adds Symbol into a set of Symbols, SymbolTableSet
	*
	*     Entry:	Symbol symbol
	*
	*     Exit:		n/a
	*
	****************************************************************/
	void AddSymbol(Symbol symbol);

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
	Symbol FindSymbol(string name);
};
#endif