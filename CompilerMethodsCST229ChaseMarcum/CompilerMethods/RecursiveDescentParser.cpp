/***********************************************************
* Author:					Chase Marcum
* Date Created:				2014-03-01
* Last Modification Date:	2015-03-21
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

bool RecursiveDescentParser::Start(TokenTable passedTokenTable, SymbolTable passedSymbolTable)
{
	if (checkStatList())
	{
		cout << "Passed!" << endl;
		return true;
	}
	cout << "failed!!!!!" << endl;
	return false;
}

bool isDeclarationStatement() 
{
	if (checkVariable())
	{
		if (_tempTokenTableIterator->tokenName == "=")
		{
			_tempTokenTableIterator++;
			if (checkValue())
			{
				if (_tempTokenTableIterator->tokenName == ";")
				{
					_symbol.symbolUse = "Variable";
					addSymbol(_symbol);
					_symbol = Symbol();
					_tempTokenTableIterator++;
					return true;
				}
				_tempTokenTableIterator = _tokenTableIterator;
				cout << "Error: Missing semicolon in declaration statement." << endl;
				return false;
			}
			else if (checkId())
			{
				if (_tempTokenTableIterator->tokenName == ";")
				{
					_symbol.symbolUse = "Variable";
					addSymbol(_symbol);
					_symbol = Symbol();
					_tempTokenTableIterator++;
					return true;
				}
				_tempTokenTableIterator = _tokenTableIterator;
				cout << "Error: Missing semicolon in declaration statement." << endl;
				return false;
			}
			cout << "Error: missing right hand side of assignment." << endl;

		}
		else if (_tempTokenTableIterator->tokenName == ";")
		{
			_symbol.symbolUse = "Variable";
			addSymbol(_symbol);
			_symbol = Symbol();
			++_tempTokenTableIterator;
			return true;
		}
	}
	_tempTokenTableIterator = _tokenTableIterator;
	_symbol = Symbol();
	return false;
}


bool isFunctionStatemant()
{
	if (checkVariable())
	{
		if (_tempTokenTableIterator->tokenName == "(")
		{
			_tempTokenTableIterator++;
			newSymbol.symbolUse = "Function";
			addSymbol(newSymbol);
			newSymbol = Symbol();
			if (checkVarList())
			{
				if (_tempTokenTableIterator->tokenName == ")")
				{
					_tempTokenTableIterator++;
					if (_tempTokenTableIterator->tokenName == "{")
					{
						_tempTokenTableIterator++;
						if (checkStatList())
						{
							if (_tempTokenTableIterator->tokenName == "}")
							{
								_tempTokenTableIterator++;
								return true;
							}
							cout << "Error: Missing closing bracket on function statement." << endl;
							_tempTokenTableIterator = _tokenTableIterator;
							return false;
						}
						cout << "Error: Missing operations in function body." << endl;
						_tempTokenTableIterator = _tokenTableIterator;
						return false;
					}
					if (_tempTokenTableIterator->tokenName == ";")
					{
						_tempTokenTableIterator++;
						return true;
					}
					_tempTokenTableIterator = _tokenTableIterator;
					cout << "Error: Missing semicolon in function statement." << endl;
					return false;
				}

			}
		}
	}
	_tempTokenTableIterator = _tokenTableIterator;
	return false;
}

bool isForLoopStatement()
{
	return false;
}

bool isIncrementOrDecrementStatement()
{
	if (checkId())
	{
		addSymbol(newSymbol);
		newSymbol = Symbol();

		if (tempIter->tokenName == "++" || tempIter->tokenName == "--")
		{
			tempIter++;
			if (tempIter->tokenName == ";")
			{
				tempIter++;
				return true;
			}
			cout << "Error: Missing semicolon on increment decrement statement." << endl;
		}
		tempIter = tokenIter;
		return false;
	}
	return false;
}

bool isInputOrOutputStatement()
{
	return false;
}

bool isReturnStatement()
{
	if (tempIter->tokenName == "return")
	{
		tempIter++;
		if (checkValue())
		{

			if (tempIter->tokenName == ";")
			{
				tempIter++;
				return true;
			}
			return false;
		}
		else if (checkId())
		{
			if (tempIter->tokenName == ";")
			{
				addSymbol(newSymbol);
				newSymbol = Symbol();
				tempIter++;
				return true;
			}
		}
	}

	tempIter = tokenIter;
	return false;
}

bool isRELOPStatement()
{
	vector<Token>::iterator myNewTempIter = tempIter;
	//	cout << "checking varlist" << endl;
	if (checkVariable())
	{
		addSymbol(newSymbol);
		newSymbol = Symbol();
		if (tempIter->tokenName == ",")
		{
			tempIter++;
			return checkVarList();
		}
		return true;
	}
	tempIter = myNewTempIter;;
	return true;
}

bool isVariableList()
{
	//	cout << "checking variable" << endl;
	//tempIter = tokenIter;
	if (checkType())
	{
		return checkId();
	}
	else return checkId();
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
