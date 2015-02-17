/* **********************************************************
* Author:					Chase Marcum
* Date Created:				2014-03-01
* Last Modification Date:	2015-02-02
* Lab Number:				CST 229 Lab 2
* Filename:					main.cpp
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

*********************************************************** */

#include "LexicalAnalyzer.h"

using namespace std;

void main()
{
	bool ifContinue = true;
	string userInput;

	while (ifContinue) {
		LexicalAnalyzer _lexicalAnalyzer;

		_lexicalAnalyzer.Start();

		cout << "\nWould you like to run another file? (y/n): ";
		cin >> userInput;

		if (userInput == "n" || userInput == "N") {
			ifContinue = false;
		}
	}
}