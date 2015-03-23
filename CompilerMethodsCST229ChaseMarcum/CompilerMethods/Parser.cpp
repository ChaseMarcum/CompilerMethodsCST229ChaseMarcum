#include "Parser.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

/**************************************************************
*	  Purpose:  Constructor of Parser and sets initial
*				variable members
*
*     Entry:	n/a
*
*     Exit:		Initiates call to start the Parser and ask user
*				to input filename.
*
****************************************************************/
Parser::Parser() {
	fileName_ =				GetFileName();
	startState_ =			State("startState");
	numericState_ =			State("numericState");
	alphaNumState_ =		State("alphaNumState");
	symbolState_ =			State("symbolState");
	doubleSymbolState_ =	State("doubleSymbolState");
	illegalState_ =			State("illegalState");
	defineState_ =			State("defineState");
	symbolTable_ =			SymbolTable();
	tokenTable_ =			TokenTable();
	ifPreprocess_ =			true;
	currentState_ =			startState_;
	partialString_ =		"";
	doubleSymbols_ =		"+-*/=|<>:&%!";
	invalidSymbols_ =		"$@~";
	previousLetter_ =		NULL;
	preprocessString_ =		"";

	InitializeKeyword();
}

/**************************************************************
*	  Purpose:  Deconstructor of Parser
*
*     Entry:	n/a
*
*     Exit:		n/a
****************************************************************/
Parser::~Parser() {}

/**************************************************************
*	  Purpose:  prompts the user for a file name to be parsed.
*
*     Entry:	n/a
*
*     Exit:		Returns File
****************************************************************/
string Parser::GetFileName() {

	string getFile;

	cout << "CST 320 Compiler Methods\n";
	cout << "Lab #1 Preprocessor & Lexical Analyzer\n\n";
	cout << "This program will analyze JavaScript files.\n";

	cout << "Please type the name of the JavaScript file \n"
		<< "you would like to analyze:\n\n"
		<< "Built in test files you may run:\n"
		<< "Test1.js, Test2.js, Test3.js\n\n";

	cin >> getFile;
	cout << endl;

	return getFile;
}

/**************************************************************
*	  Purpose:  Sets keywords.
*
*     Entry:	n/a
*
*     Exit:		n/a
****************************************************************/
void Parser::InitializeKeyword() {

	keywords_.insert = "break";
	keywords_.insert = "case";
	keywords_.insert = "catch";
	keywords_.insert = "continue";
	keywords_.insert = "debugger";
	keywords_.insert = "default";
	keywords_.insert = "delete";
	keywords_.insert = "do";
	keywords_.insert = "else";
	keywords_.insert = "finally";
	keywords_.insert = "for";
	keywords_.insert = "function";
	keywords_.insert = "if";
	keywords_.insert = "in";
	keywords_.insert = "instanceof";
	keywords_.insert = "new";
	keywords_.insert = "return";
	keywords_.insert = "switch";
	keywords_.insert = "this";
	keywords_.insert = "throw";
	keywords_.insert = "try";
	keywords_.insert = "typeof";
	keywords_.insert = "var";
	keywords_.insert = "void";
	keywords_.insert = "while";
	keywords_.insert = "with";
}

//This function reads in the text file specified by the user and sends it's contents into a string.
//It then creates the top of the word type pair list and creates an iterator to the string.
//It then loops through the string and calls the process function on each character.
void Parser::Start() {

	ifstream in;
	in.open(fileName_);

	if (in.fail()) {

		cout << "Error: Invalid File";
		exit(1);
	}

	string myString;

	while (!in.eof()) {

		getline(in, myString);

		if (myString[0] == '/' && myString[1] == '/') {
			//do nothing
		}
		else {
			textString_ += myString;
			textString_ += ' ';
		}
	}

	in.close();

	iterator_ = textString_.begin();

	cout << "Analyzing JavaScript File\n\n";
	cout << "=======================    ================\n";
	cout << "||   PARCED TOKEN    ||    || TOKEN TYPE ||\n";
	cout << "=======================    ================\n\n";


	while (iterator_ != textString_.end()) {

		if (*iterator_ != ' ' && *iterator_ != '\t') {

			ProcessString();
		}
		else {
			++iterator_;
		}
	}

	textString_ = tempTextString_;
	iterator_ = textString_.begin();
	ifPreprocess_ = false;
	while (iterator_ != textString_.end()) {

		if (*iterator_ != ' ' && *iterator_ != '\t') {

			ProcessString();
		}
		else {
			++iterator_;
		}
	}

	vector<Token>::iterator tokenIter = tokenTable_.tokenTableVector.begin();

	while (tokenIter != tokenTable_.tokenTableVector.end()) {

		cout << setw(20) << left << tokenIter->tokenName << tokenIter->tokenType << endl;
		++tokenIter;
	}

	
	cout << "\n\n";
	cout << "CST 320 Compiler Methods\n";
	cout << "Recursive Descent parser\n\n";
	cout << "This program will analyze the provious JavaScript file\n\n";
	cin >> fileName_;
	ll1Parser_ = LL1Parser(fileName_, tokenTable_);
}

//This function sends the program to the correct process function based on the current state.
void Parser::ProcessString() {

	if (currentState_.stateName == "startState") {
		ProcessStart();
	}
	else if (currentState_.stateName == "numericState") {
		ProcessNumeric();
	}
	else if (currentState_.stateName == "alphaNumState") {
		ProcessAlphaNum();
	}
	else if (currentState_.stateName == "symbolState") {
		ProcessSymbol();
	}
	else if (currentState_.stateName == "doubleSymbolState") {
		ProcessDoubleSymbol();
	}
	else if (currentState_.stateName == "defineState") {
		ProcessDefine();
	}
	else if (currentState_.stateName == "illegalState") {
		ProcessIllegal();
	}
}

//This function places each parsed word into a token table which is later printed out. its type is based on current state 
//and whether or not it is in the keyword list.  It then resets to Startstate;
void Parser::PrintPartial() {

	Symbol checkSymbol = Symbol("failed", "", "", "");

	if (symbolTable_.FindSymbol(partialString_) != checkSymbol) {
		partialString_ = symbolTable_.FindSymbol(partialString_).symbolValue;
	}

	if (ifPreprocess_ == true) {

		tempTextString_ += partialString_;
		tempTextString_ += ' ';
		partialString_ = "";
		currentState_ = startState_;
	}
	else if (keywords_.find(partialString_) != keywords_.end()) {

		tokenTable_.addToken(Token(partialString_, "KeyWord"));
		partialString_ = "";
		currentState_ = startState_;
	}
	else if (currentState_.stateName == "illegalState") {

		tokenTable_.addToken(Token(partialString_, "Invalid Input"));
		partialString_ = "";
		currentState_ = startState_;

	}
	else if (currentState_.stateName == "symbolState" || 
		     currentState_.stateName == "doubleSymbolState") {

		if (invalidSymbols_.find(partialString_) != string::npos) {

			tokenTable_.addToken(Token(partialString_, "Invalid Symbol"));
		}
		else {
			tokenTable_.addToken(Token(partialString_, "Operator"));
		}

		partialString_ = "";
		currentState_ = startState_;
	}
	else if (currentState_.stateName == "numericState") {

		if (partialString_.find('.') != string::npos) {
			tokenTable_.addToken(Token(partialString_, "Float/Double"));
		}
		else {
			tokenTable_.addToken(Token(partialString_, "Integer"));
		}

		partialString_ = "";
		currentState_ = startState_;
	}
	else {

		tokenTable_.addToken(Token(partialString_, "Identifier"));
		partialString_ = "";
		currentState_ = startState_;
	}
}

//This function is used at the beginning of each new string and
//decides which state the program should be in.
void Parser::ProcessStart() {

	if (*iterator_ == '#') {

		currentState_ = defineState_;
	}
	else if (isdigit(*iterator_)) {

		currentState_ = numericState_;
	}
	else if (isalpha(*iterator_) || *iterator_ == '_') {

		currentState_ = alphaNumState_;
	}
	else if (!isalnum(*iterator_) && *iterator_ != '_') {

		currentState_ = symbolState_;
	}
}

//This function adds the current location in the string to the partial string
//and then acts on it based on what is at the next location.
//It can either send the partial string to be printed, or just keep going or send
//it to an illegal state.
void Parser::ProcessNumeric() {

	partialString_ += *iterator_;
	++iterator_;

	if (iterator_ == textString_.end()) {

		PrintPartial();
	}
	else if (*iterator_ == ' ' || *iterator_ == '\t') {

		PrintPartial();
		++iterator_;
	}
	else if (*iterator_ == '.') {

		partialString_ += *iterator_;
		++iterator_;
	}
	else if (isalpha(*iterator_)) {

		currentState_ = illegalState_;
	}
	else if (!isalnum(*iterator_)) {

		PrintPartial();
	}
}


//this function takes preprocess statements and handles them accordingly.
void Parser::ProcessDefine() {

	string defineType;

	while (*iterator_ != ' ') {

		defineType += *iterator_;
		++iterator_;

	}

	++iterator_;

	if (defineType == "#define") {

		while (*iterator_ != ' ') {
			partialString_ += *iterator_;
			++iterator_;
		}

		++iterator_;

		while (*iterator_ != ' ') {

			preprocessString_ += *iterator_;
			++iterator_;
		}

		AddSymbol(partialString_, preprocessString_);
		partialString_ = "";
		preprocessString_ = "";
		currentState_ = startState_;
	}
	else if (defineType == "#ifdef") {

		while (*iterator_ != ' ') {

			partialString_ += *iterator_;

			++iterator_;
		}

		if (symbolTable_.FindSymbol(partialString_) != Symbol(partialString_, "", "", "")) {
			if (textString_.find("#else", distance(
				textString_.begin(), iterator_)) != string::npos) {

				int tempNumber = textString_.find("#else", distance(
					textString_.begin(), iterator_));

				iterator_ = textString_.begin();

				for (int i = 0; i < tempNumber; i++) {
					++iterator_;
				}

				while (*iterator_ != ' ') {
					++iterator_;
				}
			}
			else {

				int tempNumber = textString_.find(
					"#endif", distance(textString_.begin(), iterator_));
				iterator_ = textString_.begin();

				for (int i = 0; i < tempNumber; i++) {
					++iterator_;
				}

				while (*iterator_ != ' ') {
					++iterator_;
				}
			}
		}

		currentState_ = startState_;
	}
	else if (defineType == "#ifndef") {

		while (*iterator_ != ' ') {

			partialString_ += *iterator_;
			++iterator_;
		}

		if (symbolTable_.FindSymbol(partialString_).symbolName.compare("failed")) {

			if (textString_.find("#else", distance(
				textString_.begin(), iterator_)) != string::npos) {

				int tempNumber = textString_.find(
					"#else", distance(textString_.begin(), iterator_)
					);

				iterator_ = textString_.begin();
				for (int i = 0; i < tempNumber; i++)
				{
					++iterator_;
				}
				while (*iterator_ != ' ')
				{
					++iterator_;
				}
			}
		}

		currentState_ = startState_;
	}
	else if (defineType == "#endif") {

		currentState_ = startState_;
	}
	else if (defineType == "#else") {

		int tempNumber = textString_.find(
			"#endif", distance(textString_.begin(), iterator_)
			);

		iterator_ = textString_.begin();

		for (int i = 0; i < tempNumber; i++) {

			++iterator_;
		}

		while (*iterator_ != ' ') {

			++iterator_;
		}
	}
	else {
		// Do nothing
	}

	partialString_ = "";
}

void Parser::AddSymbol(string name, string value) {

	Symbol symbol = Symbol(partialString_, preprocessString_, "the type", "the Use");

	symbolTable_.AddSymbol(symbol);
}



//This function handles strings while in the illegal state.
//This either involves adding the next item to the string, or
//printing the string and moving on.
void Parser::ProcessIllegal(){

	partialString_ += *iterator_;
	++iterator_;

	if (iterator_ == textString_.end()) {

		PrintPartial();
	}

	else if (*iterator_ == ' ' || *iterator_ == '\t') {

		PrintPartial();
		++iterator_;
	}
	else if (*iterator_ == '.') {

		PrintPartial();
	}
	else if (!isalnum(*iterator_) && *iterator_ != '_') {

		PrintPartial();
		currentState_ = symbolState_;
	}
}

//This function handles the alphanumeric state.  It adds the current iter value to the
//partial and then either prints and moves on, or moves on.
void Parser::ProcessAlphaNum() {

	partialString_ += *iterator_;
	++iterator_;

	if (iterator_ == textString_.end()) {

		PrintPartial();
	}
	else if (*iterator_ == ' ' || *iterator_ == '\t') {

		PrintPartial();
		++iterator_;
	}
	else if (*iterator_ == '.') {

		PrintPartial();
	}
	else if (!isalnum(*iterator_) && *iterator_ != '_') {

		PrintPartial();
		currentState_ = symbolState_;
	}
}

//This function handles the Symbol state by checking if it could be a doubled symbol
//and then handling it like any other.
void Parser::ProcessSymbol() {

	if (doubleSymbols_.find(*iterator_) != string::npos) {

		currentState_ = doubleSymbolState_;
		previousLetter_ = *iterator_;
	}

	partialString_ += *iterator_;
	++iterator_;

	if (iterator_ == textString_.end()) {

		PrintPartial();
	}
	else if (*iterator_ == ' ' || *iterator_ == '\t') {

		PrintPartial();
		++iterator_;
	}
	else if (isalnum(*iterator_) || *iterator_ == '_') {

		PrintPartial();
	}
	else if (currentState_.stateName != "doubleSymbolState" && 
		!isalnum(*iterator_) && 
		*iterator_ != '_') {

		PrintPartial();
	}
}

//This function handles the double symbol state.  It checks for symbols that can be two characters.
void Parser::ProcessDoubleSymbol() {

	if (previousLetter_ == *iterator_ && 
		previousLetter_ != '!' && 
		previousLetter_ != '*' && 
		previousLetter_ != '%') {

		partialString_ += *iterator_;
		PrintPartial();
		++iterator_;
	}
	else if (*iterator_ == '=' && 
		previousLetter_ != '|' && 
		previousLetter_ != ':' && 
		previousLetter_ != '&') {

		partialString_ += *iterator_;
		PrintPartial();
		++iterator_;
	}
	else {
		PrintPartial();
	}
}