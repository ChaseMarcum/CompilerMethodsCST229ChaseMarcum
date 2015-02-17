/***********************************************************
* Author:					Chase Marcum
* Date Created:				3/01/2014
* Last Modification Date:	3/19/2014
* Lab Number:				CST 229 Lab 2
* Filename:					RecursiveDescentParser.cpp
*
* Overview:
*
* Input:
*
* Output:
*
************************************************************/

#include "RecursiveDescentParser.h"


RecursiveDescentParser::RecursiveDescentParser(TokenTable passedTokenTable, SymbolTable passedSymbolTable)
{
	_tokenTable = TokenTable(passedTokenTable);
	_tokenTableIterator = vector<Token>::iterator(passedTokenTable.tokenTableVector.begin());
	_tempTokenTableIterator = vector<Token>::iterator(passedTokenTable.tokenTableVector.begin());
	_endOfTokenTableIterator = vector<Token>::iterator(passedTokenTable.tokenTableVector.begin());
	_symbolTable = SymbolTable(passedSymbolTable);
	_symbolTableIterator = set<Symbol>::iterator(passedSymbolTable.SymbolTableSet.begin());
	_tempSymbolTableIterator = set<Symbol>::iterator(passedSymbolTable.SymbolTableSet.begin());
	_endOfSymbolTableIterator = set<Symbol>::iterator(passedSymbolTable.SymbolTableSet.begin());
}

RecursiveDescentParser::RecursiveDescentParser()
{
}


RecursiveDescentParser::~RecursiveDescentParser()
{
}

void RecursiveDescentParser::Start(TokenTable passedTokenTable, SymbolTable passedSymbolTable)
{
	RecursiveDescentParser(passedTokenTable, passedSymbolTable);

}

bool isDeclarationStatement() 
{
	return false;
}

bool isFunctionStatemant()
{
	return false;
}

bool isForLoopStatement()
{
	return false;
}

bool isIncrementOrDecrementStatement()
{
	return false;
}

bool isInputOrOutputStatement()
{
	return false;
}

bool isReturnStatement()
{
	return false;
}

bool isRELOPStatement()
{
	return false;
}

bool isVariableList()
{
	return false;
}

bool isVariable()
{
	return false;
}

bool isIdentifier()
{
	return false;
}

bool isType()
{
	return false;
}

bool isValue()
{
	return false;
}
