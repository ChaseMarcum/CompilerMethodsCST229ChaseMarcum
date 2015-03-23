/***********************************************************
* Author:					Chase Marcum
* Date Created:				2014-03-01
* Last Modification Date:	2015-03-22
* Lab Number:				CST 320 Lab 2
* Filename:					State.h
*
* Overview:
*	Sets up the outline of the State.
*
* Input:
*	String of State name.
*
* Output:
*	n/a
*
************************************************************/

#ifndef STATE_H
#define STATE_H
#include <string>

using namespace std;

class State {
public:
	string stateName;

	State(string name);
	State();
	~State();
};

#endif