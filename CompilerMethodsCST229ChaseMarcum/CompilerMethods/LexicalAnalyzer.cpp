/***********************************************************
* Author:					Chase Marcum
* Date Created:				2014-01-01
* Last Modification Date:	2015-02-02
* Lab Number:				CST 320 Compiler Methods
* Filename:					LexicalAnalyzer.cpp
*
* Overview:
*	This program will identify the tokens for JavaScript file and
*   recognize legal tokens and identify errors in tokens. It doesn't
*   check for syntax errors.
*
* Input:
*	The input will consist of JavaScript file location and users
*   repsonce if they would like to continure running the program
*
* Output:
*	The output of this program will be a list of the tokens of the
*   code provided, thier type, and if they are valid.
*
************************************************************/

#include "LexicalAnalyzer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>
#include <Windows.h>

/**************************************************************
*	  Purpose:  Constructor of Lexical Analyzer
*
*     Entry:	n/a
*
*     Exit:		n/a
****************************************************************/
LexicalAnalyzer::LexicalAnalyzer()
{
	InitializeArrays();	//initialize valid JS symbol and keyword arrays
}

/**************************************************************
*	  Purpose:  Deconstructor of Lexical Analyzer
*
*     Entry:	n/a
*
*     Exit:		n/a
****************************************************************/
LexicalAnalyzer::~LexicalAnalyzer()
{
	inputFile.close();
}

/**************************************************************
*	  Purpose:  Opens JavaScript file and reads it
*
*     Entry:	file name
*
*     Exit:		n/a
****************************************************************/
void LexicalAnalyzer::Start() {
	filename = ConsoleDisplay();
	inputFile.open(filename);

	while (!inputFile.is_open())
	{
		cout << "\n\nFile is invalid.";
		filename = ConsoleDisplay();
		inputFile.open(filename);
	}

	cout << "Analyzing JavaScript File\n\n";
	cout << "=======================    ================    ===========================\n";
	cout << "||       TOKEN       ||    || TOKEN TYPE ||    || ADDED TO SYMBOL TABLE ||\n";
	cout << "=======================    ================    ===========================\n\n";

	ReadFile();
}

/**************************************************************
*	  Purpose:  Asks user for a JavaScript filename
*
*     Entry:	User input on Javascript location and name
*
*     Exit:		n/a
****************************************************************/
string LexicalAnalyzer::ConsoleDisplay() {
	string filename;

	system("cls");
	cout << "CST 320 Compiler Methods\n";
	cout << "Lab #1 Preprocessor & Lexical Analyzer\n\n";
	cout << "This program will analyze JavaScript files\n";

	cout << "Please type the name of the JavaScript file: \n"
		<< "JavaScript code:\n\n";
	cin >> filename;

	return filename;

	cout << "\n\n";
	cout << "CST 320 Compiler Methods\n";
	cout << "Lab #2 Recursive Descent Parser(List of statements & Some Semantic Analysis)\n\n";
	cout << "This program will analyze the provious JavaScript file\n\n";

	_recursiveDescentParser.Start(_tokenTable, _symbolTable);
}

/**************************************************************
*	  Purpose:  Reads in lines of code from a JavaScript file and
*				calls to the appropriate validation method based on input
*
*     Entry:	n/a
*
*     Exit:		n/a
****************************************************************/
void LexicalAnalyzer::ReadFile()
{
	char currentChar;

	while (!inputFile.eof())
	{
		position = 0;

		getline(inputFile, lineOfCode);

		while (lineOfCode.length() > position)
		{
			currentChar = lineOfCode.at(position);

			if (isInt(currentChar))
			{
				ReadInt();
			}
			else if (currentChar == ' ' || currentChar == '\t')
			{
				position++;
			}
			else if (isIdentifier(currentChar))
			{
				ReadIdentifier();
			}
			else
			{
				ReadSymbol();
			}
		}
	}
}

/**************************************************************
*	  Purpose:  Checks if character is a vailid JavaScript interger
*
*     Entry:	The current character as a char
*
*     Exit:		A Boolean if char is an vailid interger
****************************************************************/
bool LexicalAnalyzer::isInt(char currentChar) {
	if (isdigit(currentChar))
	{
		return true;
	}

	return false;
}

/**************************************************************
*	  Purpose:  Checks if character is a vailid JavaScript Identifier
*
*     Entry:	The current character as a char
*
*     Exit:		A Boolean if char is an Identifier
****************************************************************/
bool LexicalAnalyzer::isIdentifier(char currentChar) {
	if (isalpha(currentChar) || currentChar == '_' || currentChar == '#')
	{
		return true;
	}

	return false;
}

/**************************************************************
*	  Purpose:  Checks if character is a vailid JavaScript Symbol
*
*     Entry:	The current character as a char
*
*     Exit:		A Boolean if char is an valid symbol
****************************************************************/
bool LexicalAnalyzer::isSymbol(char currentChar) {
	for (int i = 0; i < NUMBER_OF_SYMBLES; i++) {
		if (currentChar == _validSymbols[i])
			return true;
	}

	return false;
}

/**************************************************************
*	  Purpose:  Checks if word is a JavaScript Keyword
*
*     Entry:	The current word as a string
*
*     Exit:		A Boolean if word is an Keyword
****************************************************************/
bool LexicalAnalyzer::isKeyword(string currentWord) {
	for (int i = 0; i < NUMBER_OF_KEYWORDS; i++) {
		if (currentWord == _validKeywords[i])
		{
			return true;
		}
	}

	return false;
}

/**************************************************************
*	  Purpose:  Checks if character is a JavaScript Operator
*
*     Entry:	The current character as a char
*
*     Exit:		A Boolean if character is an Operator
****************************************************************/
bool LexicalAnalyzer::isOperator(char currentChar) {
	//check for all symbols that ARE operators in JS
	if (currentChar == '~' || currentChar == '!' || currentChar == '%' ||
		currentChar == '^' || currentChar == '&' || currentChar == '|' ||
		currentChar == '-' || currentChar == '+' || currentChar == '=' ||
		currentChar == '<' || currentChar == '>' || currentChar == '?' ||
		currentChar == '.')
	{
		return true;
	}
	else if (currentChar == '/' || currentChar == '*')
	{
		string tempToken;
		int tempPosition = position;
		tempToken = lineOfCode.at(tempPosition);
		tempToken += lineOfCode.at(tempPosition++);

		if (tempToken == "//" || tempToken == "/*" || tempToken == "*/")
		{
			currentToken = tempToken;
			ReadComment();
		}
		else
		{
			return true;
		}
	}

	return false;
}

/**************************************************************
*	  Purpose:  Checks if character is a JavaScript Preprocessor
*				Directives
*
*     Entry:	The current character as a char
*
*     Exit:		A Boolean if character is an Operator
****************************************************************/
bool LexicalAnalyzer::isPreprocessorDirective(string currentWord) {
	// Check for all symbols that ARE preprocessor directives in JS
	for (int i = 0; i < NUMBER_OF_PREPROCESSORDIRECTIVE; i++) {
		if (currentWord == _validPreprocessorDirective[i])
		{
			return true;
		}
	}
	return false;
}

/**************************************************************
*	  Purpose:  Reads file input until the Identifier is done
*
*     Entry:	A validation boolean
*
*     Exit:		n/a
****************************************************************/
void LexicalAnalyzer::ReadIdentifier(bool valid) {
	while (lineOfCode.length() > position &&
		(isIdentifier(lineOfCode.at(position)) ||
		isInt(lineOfCode.at(position))))
	{
		currentToken += lineOfCode.at(position++);
	}

	if (isPreprocessorDirective(currentToken))
	{
		HandlePreprocessorDirective(currentChar, "PreprocessorDirective");
	}
	else if (isKeyword(currentToken))
	{
		AddToSymbolTable("Keyword");
	}
	else if (valid)
	{
		AddToSymbolTable("Identifier");
	}
	else
	{
		AddToSymbolTable("ERROR", "\tIllegal Identifier or Integer");
	}
}

/**************************************************************
*	  Purpose:  Reads file input until the Int is done
*
*     Entry:	n/a
*
*     Exit:		n/a
****************************************************************/
void LexicalAnalyzer::ReadInt() {
	bool isFloat = false;

	while (lineOfCode.length() > position && (isInt(lineOfCode.at(position)) ||
		(lineOfCode.at(position) == '.' && !isFloat))) {
		if (lineOfCode.at(position) == '.')
		{
			isFloat = true;
		}

		currentToken += lineOfCode.at(position++);
	}

	if (lineOfCode.length() > position &&  isIdentifier(lineOfCode.at(position))) {
		ReadIdentifier(false);
	}
	else if (isFloat)
	{
		AddToSymbolTable("Float");
	}
	else
	{
		AddToSymbolTable("Integer");
	}
}

/**************************************************************
*	  Purpose:  Reads file input for that symbol
*
*     Entry:	n/a
*
*     Exit:		n/a
****************************************************************/
void LexicalAnalyzer::ReadSymbol() {
	if (isOperator(lineOfCode.at(position)))
	{
		currentToken = lineOfCode.at(position++);
		AddToSymbolTable("Operator");
	}
	else if (isSymbol(lineOfCode.at(position)))
	{
		currentToken = lineOfCode.at(position++);
		AddToSymbolTable("Symbol");
	}
	else
	{
		currentToken = lineOfCode.at(position++);
		AddToSymbolTable("ERROR", "\tIllegal symbol");
	}
}

/**************************************************************
*	  Purpose:  Displays the current token and type to screen
*
*     Entry:	Token string and error message string
*
*     Exit:		Error message
****************************************************************/
void LexicalAnalyzer::Print(string type, string errorMessage) {
	if (type == "ERROR")
	{
		SetConsoleTextAttribute(hConsole, 0xc);
	}
	else if (type == "Keyword")
	{
		SetConsoleTextAttribute(hConsole, 0xa);
	}

	cout << setw(28) << left << currentToken;
	cout << left << type << errorMessage << endl;
	SetConsoleTextAttribute(hConsole, 0xf);

	currentToken = "";
}

/**************************************************************
*	  Purpose:  Displays the current token, type, and that it
*				has been added to the Symbol Table to screen.
*				Then adds Token to Symbol Table
*
*     Entry:	Token string and error message string
*
*     Exit:		Error message
****************************************************************/
void LexicalAnalyzer::AddToSymbolTable(string type, string errorMessage)
{
	if (type != "Comment"){
		if (type == "ERROR")
		{
			SetConsoleTextAttribute(hConsole, 0xc);
		}
		else if (type == "Keyword")
		{
			SetConsoleTextAttribute(hConsole, 0xa);
		}

		_currentSymbol.symbolName = currentToken;
		_currentSymbol.symbolType = type;
		_currentVectorToken.tokenName = currentToken;
		_currentVectorToken.tokenType = type;

		_symbolTable.addSymbol(_currentSymbol);
		_tokenTable.addToken(_currentVectorToken);

		cout << "   " << setw(28) << left << _currentSymbol.symbolName;
		cout << setw(24) << left << _currentSymbol.symbolType << errorMessage;
		cout << left << "YES" << endl;
		SetConsoleTextAttribute(hConsole, 0xf);

		currentToken = "";
	}
}

/**************************************************************
*	  Purpose:	Displays the current token, type, and that it
*				has been added to the Symbol Table to screen.
*				Then adds Token to Symbol Table
*
*     Entry:	Token string and error message string
*
*     Exit:		Error message
****************************************************************/
void LexicalAnalyzer::HandlePreprocessorDirective(char currentChar, string type, string errorMessage){
	if (type == "ERROR")
	{
		SetConsoleTextAttribute(hConsole, 0xc);
	}
	else if (currentToken == "#define")
	{
		_currentSymbol.symbolName = currentToken;
		_currentSymbol.symbolType = type;
		_currentVectorToken.tokenName = currentToken;
		_currentVectorToken.tokenType = type;

		currentToken = "";

		while (lineOfCode.length() > position)
		{
			currentChar = lineOfCode.at(position);

			if (isInt(currentChar))
			{
				bool isFloat = false;

				while (lineOfCode.length() > position && (isInt(lineOfCode.at(position)) ||
					(lineOfCode.at(position) == '.' && !isFloat))) {
					if (lineOfCode.at(position) == '.')
					{
						isFloat = true;
					}

					currentToken += lineOfCode.at(position++);
				}

				if (lineOfCode.length() > position &&  isIdentifier(lineOfCode.at(position))) {
					ReadIdentifier(false);
				}
				else if (isFloat)
				{
					_currentSymbol.symbolValue = currentToken;
					_currentVectorToken.tokenValue = currentToken;
					_symbolTable.addSymbol(_currentSymbol);
					_tokenTable.addToken(_currentVectorToken);

					SetConsoleTextAttribute(hConsole, 0xb);
					cout << "   " << setw(28) << left << _currentSymbol.symbolName;
					cout << setw(24) << left << _currentSymbol.symbolType << errorMessage;
					cout << left << "YES w/ " << _currentSymbol.symbolUse << " = " << _currentSymbol.symbolValue << endl;
					SetConsoleTextAttribute(hConsole, 0xf);

					currentToken = "";

					position++;

					while (lineOfCode.length() > position)
					{
						currentChar = lineOfCode.at(position);

						if (isInt(currentChar))
						{
							ReadInt();
						}
						else if (currentChar == ' ' || currentChar == '\t')
						{
							position++;
						}
						else if (isIdentifier(currentChar))
						{
							ReadIdentifier();
						}
						else
						{
							ReadSymbol();
						}
					}

					ReadFile();
				}
				else
				{
					_currentSymbol.symbolValue = currentToken;
					_currentVectorToken.tokenValue = currentToken;
					_symbolTable.addSymbol(_currentSymbol);
					_tokenTable.addToken(_currentVectorToken);

					SetConsoleTextAttribute(hConsole, 0xb);
					cout << "   " << setw(28) << left << _currentSymbol.symbolName;
					cout << setw(24) << left << _currentSymbol.symbolType << errorMessage;
					cout << left << "YES w/ " << _currentSymbol.symbolUse << " = " << _currentSymbol.symbolValue << endl;
					SetConsoleTextAttribute(hConsole, 0xf);

					currentToken = "";

					position++;

					while (lineOfCode.length() > position)
					{
						currentChar = lineOfCode.at(position);

						if (isInt(currentChar))
						{
							ReadInt();
						}
						else if (currentChar == ' ' || currentChar == '\t')
						{
							position++;
						}
						else if (isIdentifier(currentChar))
						{
							ReadIdentifier();
						}
						else
						{
							ReadSymbol();
						}
					}

					ReadFile();
				}
			}
			else if (currentChar == ' ' || currentChar == '\t' || currentChar == '=')
			{
				position++;
			}
			else if (isIdentifier(currentChar))
			{
				ReadIdentifierForPreDirective();
			}
			else
			{
				AddToSymbolTable("ERROR", "\tIllegal Identifier or Integer");
			}
		}
	}
	else if (currentToken == "#ifndef")
	{
	}
	else if (currentToken == "#endif")
	{
	}
}

/**************************************************************
*	  Purpose:  Reads file input until the Identifier is done
*
*     Entry:	A validation boolean
*
*     Exit:		n/a
****************************************************************/
void LexicalAnalyzer::ReadIdentifierForPreDirective(bool valid) {
	while (lineOfCode.length() > position &&
		(isIdentifier(lineOfCode.at(position)) ||
		isInt(lineOfCode.at(position))))
	{
		currentToken += lineOfCode.at(position++);
	}

	if (isKeyword(currentToken))
	{
		AddToSymbolTable("Keyword");
	}
	else if (valid)
	{
		_currentSymbol.symbolUse = currentToken;
		_currentVectorToken.tokenValue = currentToken;
		currentToken = "";
	}
	else
	{
		AddToSymbolTable("ERROR", "\tIllegal Identifier or Integer");
	}
}

/**************************************************************
*	  Purpose:  Reads file input until the Comment is done
*
*     Entry:	A validation boolean
*
*     Exit:		n/a
****************************************************************/
void LexicalAnalyzer::ReadComment(bool valid)
{
	if (currentToken == "/*")
	{
		while (lineOfCode.length() > position)
		{
			currentChar = lineOfCode.at(position);

			if (currentChar == '*')
			{
				currentToken = "*";
				currentToken += lineOfCode.at(position++);

				if (currentToken == "*/")
				{
					ReadFile();
				}
			}

			position++;
		}

		while (!inputFile.eof())
		{
			position = 0;
			getline(inputFile, lineOfCode);

			while (lineOfCode.length() > position)
			{
				currentChar = lineOfCode.at(position);

				if (currentChar == '*')
				{
					currentToken = "*";
					currentToken += lineOfCode.at(position++);

					if (currentToken == "*/")
					{
						ReadFile();
					}
				}

				position++;
			}
		}
	}
	else if (currentToken == "//")
	{
		position = lineOfCode.length() - 1;
		currentToken = "";
		AddToSymbolTable("Comment");
	}
	else if (currentToken == "*/")
	{
		currentToken = "";

		while (lineOfCode.length() > position)
		{
			currentChar = lineOfCode.at(position);

			if (isInt(currentChar))
			{
				ReadInt();
			}
			else if (currentChar == ' ' || currentChar == '\t')
			{
				position++;
			}
			else if (isIdentifier(currentChar))
			{
				ReadIdentifier();
			}
			else
			{
				ReadSymbol();
			}
		}

		ReadFile();
	}
}

/**************************************************************
*	  Purpose:  To build an Array of Valid symbols and keywords
*               in JavaScript
*
*     Entry:	n/a
*
*     Exit:		n/a
****************************************************************/
void LexicalAnalyzer::InitializeArrays() {
	_validSymbols[0] = '~';
	_validSymbols[1] = '!';
	_validSymbols[2] = '$';
	_validSymbols[3] = '%';
	_validSymbols[4] = '^';
	_validSymbols[5] = '&';
	_validSymbols[6] = '*';
	_validSymbols[7] = '(';
	_validSymbols[8] = ')';
	_validSymbols[9] = '-';
	_validSymbols[10] = '+';
	_validSymbols[11] = '=';
	_validSymbols[12] = '{';
	_validSymbols[13] = '}';
	_validSymbols[14] = '[';
	_validSymbols[15] = ']';
	_validSymbols[16] = ';';
	_validSymbols[17] = ':';
	_validSymbols[18] = '\'';
	_validSymbols[19] = '"';
	_validSymbols[20] = ',';
	_validSymbols[21] = '<';
	_validSymbols[22] = '>';
	_validSymbols[23] = '?';
	_validSymbols[24] = '/';
	_validSymbols[25] = '.';
	_validSymbols[26] = '|';
	_validSymbols[27] = '\\';

	_validKeywords[0] = "break";
	_validKeywords[1] = "case";
	_validKeywords[2] = "catch";
	_validKeywords[3] = "continue";
	_validKeywords[4] = "debugger";
	_validKeywords[5] = "default";
	_validKeywords[6] = "delete";
	_validKeywords[7] = "do";
	_validKeywords[8] = "else";
	_validKeywords[9] = "finally";
	_validKeywords[10] = "for";
	_validKeywords[11] = "function";
	_validKeywords[12] = "if";
	_validKeywords[13] = "in";
	_validKeywords[14] = "instanceof";
	_validKeywords[15] = "new";
	_validKeywords[16] = "return";
	_validKeywords[17] = "switch";
	_validKeywords[18] = "this";
	_validKeywords[19] = "throw";
	_validKeywords[20] = "try";
	_validKeywords[21] = "typeof";
	_validKeywords[22] = "var";
	_validKeywords[23] = "void";
	_validKeywords[24] = "while";
	_validKeywords[25] = "with";

	_validPreprocessorDirective[0] = "//";
	_validPreprocessorDirective[1] = "/*";
	_validPreprocessorDirective[2] = "*/";
	_validPreprocessorDirective[3] = "#define";
	_validPreprocessorDirective[4] = "#ifndef";
	_validPreprocessorDirective[5] = "#endif";
};