/***********************************************************
* Author:					Chase Marcum
* Date Created:				2014-01-01
* Last Modification Date:	2015-03-21
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
	inputFile_.close();
}

/**************************************************************
*	  Purpose:  Opens JavaScript file and reads it
*
*     Entry:	file name
*
*     Exit:		n/a
****************************************************************/
void LexicalAnalyzer::Start() {
	filename_ = ConsoleDisplay();
	inputFile_.open(filename_);

	while (!inputFile_.is_open())
	{
		cout << "\n\nFile is invalid.";
		filename_ = ConsoleDisplay();
		inputFile_.open(filename_);
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
	cout << "This program will analyze JavaScript files.\n";

	cout << "Please type the name of the JavaScript file \n"
		<< "you would like to analyze:\n\n"
		<< "Built in test files you may run:\n"
		<< "Test1.js, Test2.js, Test3.js\n\n";
	cin >> filename;

	return filename;

	cout << "\n\n";
	cout << "CST 320 Compiler Methods\n";
	cout << "Lab #2 Recursive Descent Parser(List of statements & Some Semantic Analysis)\n\n";
	cout << "This program will analyze the provious JavaScript file\n\n";

	recursiveDescentParser_.Start(tokenTable_, symbolTable_);
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

	while (!inputFile_.eof())
	{
		position_ = 0;

		getline(inputFile_, lineOfCode_);

		while (lineOfCode_.length() > position_)
		{
			currentChar = lineOfCode_.at(position_);

			if (isInt(currentChar))
			{
				ReadInt();
			}
			else if (currentChar == ' ' || currentChar == '\t')
			{
				position_++;
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
		if (currentChar == validSymbols_[i])
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
		if (currentWord == validKeywords_[i])
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
		int tempPosition = position_;
		tempToken = lineOfCode_.at(tempPosition);
		tempToken += lineOfCode_.at(tempPosition++);

		if (tempToken == "//" || tempToken == "/*" || tempToken == "*/")
		{
			currentToken_ = tempToken;
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
		if (currentWord == validPreprocessorDirective_[i])
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
	while (lineOfCode_.length() > position_ &&
		(isIdentifier(lineOfCode_.at(position_)) ||
		isInt(lineOfCode_.at(position_))))
	{
		currentToken_ += lineOfCode_.at(position_++);
	}

	if (isPreprocessorDirective(currentToken_))
	{
		HandlePreprocessorDirective(currentChar_, "PreprocessorDirective");
	}
	else if (isKeyword(currentToken_))
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

	while (lineOfCode_.length() > position_ && (isInt(lineOfCode_.at(position_)) ||
		(lineOfCode_.at(position_) == '.' && !isFloat))) {
		if (lineOfCode_.at(position_) == '.')
		{
			isFloat = true;
		}

		currentToken_ += lineOfCode_.at(position_++);
	}

	if (lineOfCode_.length() > position_ &&  isIdentifier(lineOfCode_.at(position_))) {
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
	if (isOperator(lineOfCode_.at(position_)))
	{
		currentToken_ = lineOfCode_.at(position_++);
		AddToSymbolTable("Operator");
	}
	else if (isSymbol(lineOfCode_.at(position_)))
	{
		currentToken_ = lineOfCode_.at(position_++);
		AddToSymbolTable("Symbol");
	}
	else
	{
		currentToken_ = lineOfCode_.at(position_++);
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
		SetConsoleTextAttribute(hConsole_, 0xc);
	}
	else if (type == "Keyword")
	{
		SetConsoleTextAttribute(hConsole_, 0xa);
	}

	cout << setw(28) << left << currentToken_;
	cout << left << type << errorMessage << endl;
	SetConsoleTextAttribute(hConsole_, 0xf);

	currentToken_ = "";
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
			SetConsoleTextAttribute(hConsole_, 0xc);
		}
		else if (type == "Keyword")
		{
			SetConsoleTextAttribute(hConsole_, 0xa);
		}

		currentSymbol_.symbolName = currentToken_;
		currentSymbol_.symbolType = type;
		currentVectorToken_.tokenName = currentToken_;
		currentVectorToken_.tokenType = type;

		symbolTable_.addSymbol(currentSymbol_);
		tokenTable_.addToken(currentVectorToken_);

		cout << "   " << setw(28) << left << currentSymbol_.symbolName;
		cout << setw(24) << left << currentSymbol_.symbolType << errorMessage;
		cout << left << "YES" << endl;
		SetConsoleTextAttribute(hConsole_, 0xf);

		currentToken_ = "";
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
		SetConsoleTextAttribute(hConsole_, 0xc);
	}
	else if (currentToken_ == "#define")
	{
		currentSymbol_.symbolName = currentToken_;
		currentSymbol_.symbolType = type;
		currentVectorToken_.tokenName = currentToken_;
		currentVectorToken_.tokenType = type;

		currentToken_ = "";

		while (lineOfCode_.length() > position_)
		{
			currentChar = lineOfCode_.at(position_);

			if (isInt(currentChar))
			{
				bool isFloat = false;

				while (lineOfCode_.length() > position_ && (isInt(lineOfCode_.at(position_)) ||
					(lineOfCode_.at(position_) == '.' && !isFloat))) {
					if (lineOfCode_.at(position_) == '.')
					{
						isFloat = true;
					}

					currentToken_ += lineOfCode_.at(position_++);
				}

				if (lineOfCode_.length() > position_ &&  isIdentifier(lineOfCode_.at(position_))) {
					ReadIdentifier(false);
				}
				else if (isFloat)
				{
					currentSymbol_.symbolValue = currentToken_;
					currentVectorToken_.tokenValue = currentToken_;
					symbolTable_.addSymbol(currentSymbol_);
					tokenTable_.addToken(currentVectorToken_);

					SetConsoleTextAttribute(hConsole_, 0xb);
					cout << "   " << setw(28) << left << currentSymbol_.symbolName;
					cout << setw(24) << left << currentSymbol_.symbolType << errorMessage;
					cout << left << "YES w/ " << currentSymbol_.symbolUse << " = " << currentSymbol_.symbolValue << endl;
					SetConsoleTextAttribute(hConsole_, 0xf);

					currentToken_ = "";

					position_++;

					while (lineOfCode_.length() > position_)
					{
						currentChar = lineOfCode_.at(position_);

						if (isInt(currentChar))
						{
							ReadInt();
						}
						else if (currentChar == ' ' || currentChar == '\t')
						{
							position_++;
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
					currentSymbol_.symbolValue = currentToken_;
					currentVectorToken_.tokenValue = currentToken_;
					symbolTable_.addSymbol(currentSymbol_);
					tokenTable_.addToken(currentVectorToken_);

					SetConsoleTextAttribute(hConsole_, 0xb);
					cout << "   " << setw(28) << left << currentSymbol_.symbolName;
					cout << setw(24) << left << currentSymbol_.symbolType << errorMessage;
					cout << left << "YES w/ " << currentSymbol_.symbolUse << " = " << currentSymbol_.symbolValue << endl;
					SetConsoleTextAttribute(hConsole_, 0xf);

					currentToken_ = "";

					position_++;

					while (lineOfCode_.length() > position_)
					{
						currentChar = lineOfCode_.at(position_);

						if (isInt(currentChar))
						{
							ReadInt();
						}
						else if (currentChar == ' ' || currentChar == '\t')
						{
							position_++;
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
				position_++;
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
	else if (currentToken_ == "#ifndef")
	{
	}
	else if (currentToken_ == "#endif")
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
	while (lineOfCode_.length() > position_ &&
		(isIdentifier(lineOfCode_.at(position_)) ||
		isInt(lineOfCode_.at(position_))))
	{
		currentToken_ += lineOfCode_.at(position_++);
	}

	if (isKeyword(currentToken_))
	{
		AddToSymbolTable("Keyword");
	}
	else if (valid)
	{
		currentSymbol_.symbolUse = currentToken_;
		currentVectorToken_.tokenValue = currentToken_;
		currentToken_ = "";
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
	if (currentToken_ == "/*")
	{
		while (lineOfCode_.length() > position_)
		{
			currentChar_ = lineOfCode_.at(position_);

			if (currentChar_ == '*')
			{
				currentToken_ = "*";
				currentToken_ += lineOfCode_.at(position_++);

				if (currentToken_ == "*/")
				{
					ReadFile();
				}
			}

			position_++;
		}

		while (!inputFile_.eof())
		{
			position_ = 0;
			getline(inputFile_, lineOfCode_);

			while (lineOfCode_.length() > position_)
			{
				currentChar_ = lineOfCode_.at(position_);

				if (currentChar_ == '*')
				{
					currentToken_ = "*";
					currentToken_ += lineOfCode_.at(position_++);

					if (currentToken_ == "*/")
					{
						ReadFile();
					}
				}

				position_++;
			}
		}
	}
	else if (currentToken_ == "//")
	{
		position_ = lineOfCode_.length() - 1;
		currentToken_ = "";
		AddToSymbolTable("Comment");
	}
	else if (currentToken_ == "*/")
	{
		currentToken_ = "";

		while (lineOfCode_.length() > position_)
		{
			currentChar_ = lineOfCode_.at(position_);

			if (isInt(currentChar_))
			{
				ReadInt();
			}
			else if (currentChar_ == ' ' || currentChar_ == '\t')
			{
				position_++;
			}
			else if (isIdentifier(currentChar_))
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
	validSymbols_[0] = '~';
	validSymbols_[1] = '!';
	validSymbols_[2] = '$';
	validSymbols_[3] = '%';
	validSymbols_[4] = '^';
	validSymbols_[5] = '&';
	validSymbols_[6] = '*';
	validSymbols_[7] = '(';
	validSymbols_[8] = ')';
	validSymbols_[9] = '-';
	validSymbols_[10] = '+';
	validSymbols_[11] = '=';
	validSymbols_[12] = '{';
	validSymbols_[13] = '}';
	validSymbols_[14] = '[';
	validSymbols_[15] = ']';
	validSymbols_[16] = ';';
	validSymbols_[17] = ':';
	validSymbols_[18] = '\'';
	validSymbols_[19] = '"';
	validSymbols_[20] = ',';
	validSymbols_[21] = '<';
	validSymbols_[22] = '>';
	validSymbols_[23] = '?';
	validSymbols_[24] = '/';
	validSymbols_[25] = '.';
	validSymbols_[26] = '|';
	validSymbols_[27] = '\\';

	validKeywords_[0] = "break";
	validKeywords_[1] = "case";
	validKeywords_[2] = "catch";
	validKeywords_[3] = "continue";
	validKeywords_[4] = "debugger";
	validKeywords_[5] = "default";
	validKeywords_[6] = "delete";
	validKeywords_[7] = "do";
	validKeywords_[8] = "else";
	validKeywords_[9] = "finally";
	validKeywords_[10] = "for";
	validKeywords_[11] = "function";
	validKeywords_[12] = "if";
	validKeywords_[13] = "in";
	validKeywords_[14] = "instanceof";
	validKeywords_[15] = "new";
	validKeywords_[16] = "return";
	validKeywords_[17] = "switch";
	validKeywords_[18] = "this";
	validKeywords_[19] = "throw";
	validKeywords_[20] = "try";
	validKeywords_[21] = "typeof";
	validKeywords_[22] = "var";
	validKeywords_[23] = "void";
	validKeywords_[24] = "while";
	validKeywords_[25] = "with";

	validPreprocessorDirective_[0] = "//";
	validPreprocessorDirective_[1] = "/*";
	validPreprocessorDirective_[2] = "*/";
	validPreprocessorDirective_[3] = "#define";
	validPreprocessorDirective_[4] = "#ifndef";
	validPreprocessorDirective_[5] = "#endif";
};