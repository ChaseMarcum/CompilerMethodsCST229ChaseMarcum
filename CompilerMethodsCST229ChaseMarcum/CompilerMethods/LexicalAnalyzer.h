/***********************************************************
* Author:					Chase Marcum
* Date Created:				2014-03-01
* Last Modification Date:	2015-03-21
* Lab Number:				CST 320 Compiler Methods 
* Filename:					LexicalAnalyzer.h
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

************************************************************/

#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H
#include "SymbolTable.h"
#include "Symbol.h"
#include "TokenTable.h"
#include "LanguageChecker.h"
#include <string>
#include <Windows.h>
#include <fstream>

using namespace std;

class LexicalAnalyzer
{
public:
	const static int NUMBER_OF_SYMBLES = 28;				// Number of symbols in JavaScript
	const static int NUMBER_OF_KEYWORDS = 26;				// Number of Keywords in JavaScript
	const static int NUMBER_OF_PREPROCESSORDIRECTIVE = 6;	/* Number of Preprocessor Directives
															   in JavaScript */

	/**************************************************************
	*	  Purpose:  Constructor of Lexical Analyzer
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	****************************************************************/
	LexicalAnalyzer();

	/**************************************************************
	*	  Purpose:  Deconstructor of Lexical Analyzer
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	****************************************************************/
	~LexicalAnalyzer();

	/**************************************************************
	*	  Purpose:  Opens JavaScript file and reads it
	*
	*     Entry:	file name
	*
	*     Exit:		n/a
	****************************************************************/
	void Start();

private:
	size_t position_;										// Iterates position of lineOfCode initially set at 0
	char currentChar_;										// Current char fron lineOfCode
	string currentToken_;									// Current string from lineOfCode
	string lineOfCode_;										// Sinlge line of code from file
	string filename_;										// User input of JavaScript filename
	ifstream inputFile_;										// Used to open a file connection
	char validSymbols_[NUMBER_OF_SYMBLES];					// Array of valid JavaScript symbols
	string validKeywords_[NUMBER_OF_KEYWORDS];				// Array of valid JavaScript keywords
	string validPreprocessorDirective_[NUMBER_OF_PREPROCESSORDIRECTIVE];	/* Array of vailid JavaScript
																			   Preprocessor Directives */
	HANDLE hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);		// A HANDLE used for font color
	Symbol currentSymbol_;									/* Symbol class that holds string name,
															   string type, string use, string value */
	SymbolTable symbolTable_;								// Set of Symbols
	TokenTable tokenTable_;									// vector of tokens
	Token currentVectorToken_;								// token class for vector Token Table
	LanguageChecker recursiveDescentParser_;

	/**************************************************************
	*	  Purpose:  Asks user for a JavaScript filename
	*
	*     Entry:	User input on Javascript location and name
	*
	*     Exit:		n/a
	****************************************************************/
	string ConsoleDisplay();

	/**************************************************************
	*	  Purpose:  Reads in lines of code from a JavaScript file and
	*				calls to the appropriate validation method based on input
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	****************************************************************/
	void ReadFile();

	/**************************************************************
	*	  Purpose:  Checks if character is a vailid JavaScript interger
	*
	*     Entry:	The current character as a char
	*
	*     Exit:		A Boolean if char is an vailid interger
	****************************************************************/
	bool isInt(char currentChar);

	/**************************************************************
	*	  Purpose:  Checks if character is a vailid JavaScript Identifier
	*
	*     Entry:	The current character as a char
	*
	*     Exit:		A Boolean if char is an Identifier
	****************************************************************/
	bool isIdentifier(char currentChar);

	/**************************************************************
	*	  Purpose:  Checks if character is a vailid JavaScript Symbol
	*
	*     Entry:	The current character as a char
	*
	*     Exit:		A Boolean if char is an valid symbol
	****************************************************************/
	bool isSymbol(char currentChar);

	/**************************************************************
	*	  Purpose:  Checks if word is a JavaScript Keyword
	*
	*     Entry:	The current word as a string
	*
	*     Exit:		A Boolean if word is an Keyword
	****************************************************************/
	bool isKeyword(string currentWord);

	/**************************************************************
	*	  Purpose:  Checks if character is a JavaScript Operator
	*
	*     Entry:	The current character as a char
	*
	*     Exit:		A Boolean if character is an Operator
	****************************************************************/
	bool isOperator(char currentChar);

	/**************************************************************
	*	  Purpose:  Checks if character is a JavaScript Preprocessor
	*				Directives
	*
	*     Entry:	The current character as a char
	*
	*     Exit:		A Boolean if character is an Operator
	****************************************************************/
	bool isPreprocessorDirective(string currentWord);

	/**************************************************************
	*	  Purpose:  Reads file input until the Identifier is done
	*
	*     Entry:	A validation boolean
	*
	*     Exit:		n/a
	****************************************************************/
	void ReadIdentifier(bool valid = true);

	/**************************************************************
	*	  Purpose:  Reads file input until the Int is done
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	****************************************************************/
	void ReadInt();

	/**************************************************************
	*	  Purpose:  Reads file input for that symbol
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	****************************************************************/
	void ReadSymbol();

	/**************************************************************
	*	  Purpose:  Displays the current token and type to screen
	*
	*     Entry:	Token string and error message string
	*
	*     Exit:		Error message
	****************************************************************/
	void Print(string type, string errorMessage = " ");

	/**************************************************************
	*	  Purpose:  Displays the current token, type, and that it
	*				has been added to the Symbol Table to screen.
	*				Then adds Token to Symbol Table
	*
	*     Entry:	Token string and error message string
	*
	*     Exit:		Error message
	****************************************************************/
	void AddToSymbolTable(string type, string errorMessage = " ");

	/**************************************************************
	*	  Purpose:
	*
	*     Entry:	Token string and error message string
	*
	*     Exit:		Error message
	****************************************************************/
	void HandlePreprocessorDirective(char currentChar, string type, string errorMessage = " ");

	/**************************************************************
	*	  Purpose:  Reads file input until the Identifier is done
	*
	*     Entry:	A validation boolean
	*
	*     Exit:		n/a
	****************************************************************/
	void ReadIdentifierForPreDirective(bool valid = true);

	/**************************************************************
	*	  Purpose:  Reads file input until the Comment is done
	*
	*     Entry:	A validation boolean
	*
	*     Exit:		n/a
	****************************************************************/
	void ReadComment(bool valid = true);

	/**************************************************************
	*	  Purpose:  To build an Array of Valid symbols and keywords
	*               in JavaScript
	*
	*     Entry:	n/a
	*
	*     Exit:		n/a
	****************************************************************/
	void InitializeArrays();
};
#endif