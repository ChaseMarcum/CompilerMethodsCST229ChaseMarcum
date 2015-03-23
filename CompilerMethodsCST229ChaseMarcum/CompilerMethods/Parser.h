/***********************************************************
* Author:					Chase Marcum
* Date Created:				2014-03-01
* Last Modification Date:	2015-03-22
* Lab Number:				CST 320 Lab 2
* Filename:					Parser.h
*
* Overview:
*	Sets up and implements the Parser.
*
* Input:
*	n/a
*
* Output:
*	True or False
*
************************************************************/


#ifndef PARSER_H
#define PARSER_H
#include "State.h"
#include "LL1Parser.h"
#include "LanguageChecker.h"
#include <set>

using namespace std;
class Parser {

public:
	State symbolState_;
	State alphaNumState_;
	State numericState_;
	State startState_;
	State currentState_;
	State doubleSymbolState_;
	State illegalState_;
	State defineState_;
	LL1Parser ll1Parser_;
	bool ifPreprocess_;
	SymbolTable symbolTable_;
	TokenTable tokenTable_;
	string fileName_;
	string textString_;
	string partialString_;
	string preprocessString_;
	string doubleSymbols_;
	string invalidSymbols_;
	string tempTextString_;
	string::iterator iterator_;
	set<string> keywords_;
	char previousLetter_;

	Parser();
	~Parser();
	string GetFileName();
	
	void InitializeKeyword();

	void PrintPartial();

	void ProcessString();

	void ProcessIllegal();

	void ProcessDoubleSymbol();

	void ProcessStart();

	void ProcessNumeric();

	void ProcessAlphaNum();

	void ProcessSymbol();

	void ProcessDefine();

	void AddSymbol(string name, string value);

	void Start();

	
};

#endif