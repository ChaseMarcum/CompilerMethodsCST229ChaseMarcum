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
		cout << "Error: Filename not found. Closing program.";
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
		myRules.push_back(tempRule);
	}

	vector<Token>::iterator tokenIterator = tokens.tokenTableVector.end();
	vector<Token>::iterator stop = tokens.tokenTableVector.begin();
	--tokenIterator;
	tokenStack.push(Token("$", "end"));

	while (tokenIterator != stop)
	{
		tokenStack.push(*tokenIterator);
		cout << tokenIterator->tokenName << endl;
		--tokenIterator;
	}

	tokenStack.push(*tokenIterator);
	cout << tokenIterator->tokenName << endl;

	bool awesome = Run();

	if (awesome)
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

void LL1Parser::AddRules(int ruleNumber)
{
	string ruleString = myRules[ruleNumber].elements;
	stack<string> tempStack;

	while (ruleString.find(" ") != string::npos)
	{
		string tempString;

		unsigned end = ruleString.find(" ");

		tempString = ruleString.substr(0, end);
		ruleString = ruleString.substr(end + 1, ruleString.length());
		cout << tempString << endl;

		tempStack.push(tempString);
	}

	tempStack.push(ruleString.substr(0, ruleString.length()));

	while (!tempStack.empty())
	{
		ruleStack.push(tempStack.top());
		cout << "pushing rule " << tempStack.top() << " onto the ruleStack" << endl;
		tempStack.pop();
	}
}

bool LL1Parser::Run()
{
	ruleStack.push("$");
	ruleStack.push("S");

	while (!ruleStack.empty() && !tokenStack.empty())
	{
		string currentKey = ruleStack.top();
		Token currentToken = tokenStack.top();
		int ruleNumber;

		for (int a = 0; a < myRules.size(); a++)
		{
		}
		int a;
		bool isARule = false;
		bool isRuleAdded = false;
		int count = 0;
		for (a = 0; a < myRules.size(); a++)
		{
			if (myRules[a].GetKey() == currentKey &&
				currentToken.tokenName == myRules[a].GetValue() ||
				(myRules[a].GetKey() == currentKey &&
				myRules[a].GetValue() == "ID" &&
				currentToken.tokenType == "Identifier") ||
				myRules[a].GetKey() == currentKey &&
				myRules[a].GetElements() == "lambda")
			{
				if (myRules[a].GetElements() == "lambda")
				{
					ruleStack.pop();
					isRuleAdded = true;
					break;
				}
				else
				{
					ruleNumber = a;
					ruleStack.pop();
					AddRules(a);
					isRuleAdded = true;
					break;
				}
			}

			if (ruleStack.top() == "$" && currentToken.tokenName == "$")
			{
				return true;
			}

			if (myRules[a].GetKey() == currentKey)
			{
				isARule = true;
			}

			++count;
		}

		if (count == myRules.size() && isARule)
		{
			return false;
		}

		cout << ruleStack.top() << " " << tokenStack.top().tokenName << endl;

		if (ruleStack.top() == tokenStack.top().tokenName)
		{
			cout << "popping " << ruleStack.top() << " from the ruleStack" << endl;

			ruleStack.pop();

			cout << "popping " << tokenStack.top().tokenName << " from the tokenStack"
				<< endl;

			tokenStack.pop();
		}
		else if (ruleStack.top() == "NUM" && tokenStack.top().tokenType == "Integer")
		{
			cout << "popping " << ruleStack.top() << " from the ruleStack" << endl;

			ruleStack.pop();
			cout << "popping " << tokenStack.top().tokenName << " from the tokenStack"
				<< endl;

			tokenStack.pop();
		}
		else if (ruleStack.top() == "ID" && tokenStack.top().tokenType == "Identifier")
		{
			cout << "popping " << ruleStack.top() << " from the ruleStack" << endl;

			ruleStack.pop();
			cout << "popping " << tokenStack.top().tokenName << " from the tokenStack"
				<< endl;
			tokenStack.pop();
		}
		else if (isARule == false && ruleStack.top() != tokenStack.top().tokenName
			&& isRuleAdded == false)
		{
			return false;
		}

		isRuleAdded = false;
	}

	return true;
}