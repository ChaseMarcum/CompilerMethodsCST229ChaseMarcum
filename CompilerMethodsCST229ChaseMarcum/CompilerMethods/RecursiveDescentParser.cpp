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


RecursiveDescentParser::RecursiveDescentParser(TokenTable tokenTable, SymbolTable symbolTable)
{
	_tokenTable = TokenTable(tokenTable);
	_tokenTableIterator = vector<Token>::iterator(tokenTable.tokenTableVector.begin());
	_tempTokenTableIterator = vector<Token>::iterator(tokenTable.tokenTableVector.begin());
	_endOfTokenTableIterator = vector<Token>::iterator(tokenTable.tokenTableVector.begin());
	_symbolTable = SymbolTable(symbolTable);
	_symbolTableIterator = set<Symbol>::iterator(symbolTable.SymbolTableSet.begin());
	_tempSymbolTableIterator = set<Symbol>::iterator(symbolTable.SymbolTableSet.begin());
	_endOfSymbolTableIterator = set<Symbol>::iterator(symbolTable.SymbolTableSet.begin());
}

RecursiveDescentParser::RecursiveDescentParser()
{
}


RecursiveDescentParser::~RecursiveDescentParser()
{
}

bool RecursiveDescentParser::Start(TokenTable passedTokenTable, SymbolTable passedSymbolTable)
{
	if (isStatList())
	{
		cout << "Passed!" << endl;
		return true;
	}
	cout << "failed!!!!!" << endl;
	return false;
}

bool isDeclarationStatement() 
{
	if (isVariable())
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
	if (isVariable())
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
	if (isIdentifier())
	{
		addSymbol(newSymbol);
		newSymbol = Symbol();

		if (_tempTokenTableIterator->tokenName == "++" || _tempTokenTableIterator->tokenName == "--")
		{
			_tempTokenTableIterator++;
			if (_tempTokenTableIterator->tokenName == ";")
			{
				_tempTokenTableIterator++;
				return true;
			}
			cout << "Error: Missing semicolon on increment decrement statement." << endl;
		}
		_tempTokenTableIterator = _tokenTableIterator;
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
	if (_tempTokenTableIterator->tokenName == "return")
	{
		++_tempTokenTableIterator;
		if (isValue())
		{

			if (_tempTokenTableIterator->tokenName == ";")
			{
				++_tempTokenTableIterator;
				return true;
			}
			return false;
		}
		else if (isIdentifier())
		{
			if (_tempTokenTableIterator->tokenName == ";")
			{
				AddSymbol(newSymbol);
				newSymbol = Symbol();
				_tempTokenTableIterator++;
				return true;
			}
		}
	}

	_tempTokenTableIterator = _tokenTableIterator;

	return false;
}

bool isRELOPStatement()
{
	vector<Token>::iterator _newTempIterator = _tempTokenTableIterator;
	if (isVariable())
	{
		addSymbol(newSymbol);
		newSymbol = Symbol();
		if (_tempTokenTableIterator->tokenName == ",")
		{
			++_tempTokenTableIterator;
			return isVariableList();
		}
		return true;
	}

	_tempTokenTableIterator = _newTempIterator;

	return true;
}

bool isVariableList()
{
	if (isType())
	{
		return isIdentifier();
	}
	else return isIdentifier();
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
