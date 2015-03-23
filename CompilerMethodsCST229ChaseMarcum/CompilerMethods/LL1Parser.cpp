/***********************************************************
* Author:					Chase Marcum
* Date Created:				2014-03-01
* Last Modification Date:	2015-03-21
* Lab Number:				CST 320 Lab 3
* Filename:					LL1Parser.cpp
*
* Overview:  Implementation of the LL1Parser.
*
* Input:
*
* Output:
*
************************************************************/
#include "LL1Parser.h"
#include <fstream>
#include <iostream>

LL1Parser::LL1Parser(string fileName, TokenTable tokens)
{
	ifstream in;
	in.open(fileName);

	if (in.fail())
	{
		cout << "Error: File not found. Closing program.";
		exit(1);
	}

	string myString;

	while (!in.eof())
	{
		getline(in, myString);
		cout << myString << endl;
		unsigned firstEnd = myString.find(" ");
		string first = myString.substr(0, firstEnd);
		string firstSub = myString.substr(firstEnd + 1, myString.length());
		unsigned secondEnd = firstSub.find(" ");
		string second = firstSub.substr(0, secondEnd);
		string secondSub = firstSub.substr(secondEnd + 1, firstSub.length());
		string third = secondSub.substr(0, secondSub.length());
		cout << first << endl;
		cout << second << endl;
		cout << third << endl;
		Rules tempRule = Rules(first, second, third);
		rules_.push_back(tempRule);
	}

	vector<Token>::iterator tokenIterator = tokens.tokenTableVector.end();
	vector<Token>::iterator stop = tokens.tokenTableVector.begin();
	--tokenIterator;
	tokenStack_.push(Token("$", "end"));

	while (tokenIterator != stop)
	{
		tokenStack_.push(*tokenIterator);
		cout << tokenIterator->tokenName << endl;
		--tokenIterator;
	}

	tokenStack_.push(*tokenIterator);
	cout << tokenIterator->tokenName << endl;

	bool hasRulesBeenMet = Run();

	if (hasRulesBeenMet)
	{
		cout << "true";
	}
	else
	{
		cout << "failed";
	}
}

LL1Parser::LL1Parser()
{
}

LL1Parser::~LL1Parser()
{
}

/**************************************************************
*	  Purpose:  Adds element to Rule
*
*     Entry:	The int of rule number
*
*     Exit:		n/a
*
****************************************************************/
void LL1Parser::AddRule(int ruleNumber) {

	string ruleString = rules_[ruleNumber].GetElements();
	stack<string> tempStack;

	while (ruleString.find(" ") != string::npos) {

		string tempString;

		unsigned end = ruleString.find(" ");

		tempString = ruleString.substr(0, end);
		ruleString = ruleString.substr(end + 1, ruleString.length());
		cout << tempString << endl;

		tempStack.push(tempString);
	}

	tempStack.push(ruleString.substr(0, ruleString.length()));

	while (!tempStack.empty()) {

		ruleStack_.push(tempStack.top());
		cout << "Push Rule - " << tempStack.top() << " is Pushed to Rule Stack" << endl;
		tempStack.pop();
	}
}

/**************************************************************
*	  Purpose:  Compares the rules table with the current input 
*				pushes rules onto the rule stack when appropriate. 
*				Returns true if rules are met, and false if they 
*				are not.
*
*     Entry:	The current Token
*
*     Exit:		A Boolean if Token is an valid RELOP Statement
****************************************************************/
bool LL1Parser::Run() {

	ruleStack_.push("$");
	ruleStack_.push("S");

	while (!ruleStack_.empty() && !tokenStack_.empty()) {

		string currentKey = ruleStack_.top();
		Token currentToken = tokenStack_.top();
		int ruleNumber = 0;

		bool isARule = false;
		bool isRuleAdded = false;
		int count = 0;

		for (int i = 0; i < rules_.size(); i++) {

			if (rules_[i].GetKey() == currentKey &&
				currentToken.tokenName == rules_[i].GetValue() ||
				(rules_[i].GetKey() == currentKey &&
				rules_[i].GetValue() == "ID" &&
				currentToken.tokenType == "Identifier") ||
				rules_[i].GetKey() == currentKey &&
				rules_[i].GetElements() == "lambda") {

				if (rules_[i].GetElements() == "lambda") {

					ruleStack_.pop();
					isRuleAdded = true;

					break;
				}
				else {

					ruleStack_.pop();
					AddRule(i);
					isRuleAdded = true;
					
					break;
				}
			}

			if (ruleStack_.top() == "$" && currentToken.tokenName == "$") {

				return true;
			}

			if (rules_[i].GetKey() == currentKey) {

				isARule = true;
			}

			++count;
		}

		if (count == rules_.size() && isARule) {

			return false;
		}

		cout << ruleStack_.top() << " " << tokenStack_.top().tokenName << endl;

		if (ruleStack_.top() == tokenStack_.top().tokenName) {

			cout << "Pop Rule - " << ruleStack_.top() << 
				" is Popped from Rule Stack" << endl;

			ruleStack_.pop();

			cout << "Pop Rule - " << tokenStack_.top().tokenName << 
				" is Popped from Token Stack"
				<< endl;

			tokenStack_.pop();
		}
		else if (ruleStack_.top() == "NUM" && 
			tokenStack_.top().tokenType == "Integer") {

			cout << "Pop Rule - " << ruleStack_.top() << 
				" is Popped from Rule Stack" << endl;

			ruleStack_.pop();
			cout << "Pop Rule - " << tokenStack_.top().tokenName << 
				" is Popped from Token Stack"
				<< endl;

			tokenStack_.pop();
		}
		else if (ruleStack_.top() == "ID" && 
			tokenStack_.top().tokenType == "Identifier") {

			cout << "Pop Rule - " << ruleStack_.top() << 
				" is Popped from Rule Stack" << endl;

			ruleStack_.pop();
			cout << "Pop Rule - " << tokenStack_.top().tokenName << 
				" is Popped from Token Stack"
				<< endl;
			tokenStack_.pop();
		}
		else if (isARule == false && 
			ruleStack_.top() 
			!= tokenStack_.top().tokenName && 
			isRuleAdded == false) {

			return false;
		}

		isRuleAdded = false;
	}

	return true;
}