/***********************************************************
* Author:					Chase Marcum
* Date Created:				2014-03-01
* Last Modification Date:	2015-03-22
* Lab Number:				CST 320 Lab 2
* Filename:					State.cpp
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
#include "State.h"

State::State(string name) {
	stateName = name;
}

/**************************************************************
*	  Purpose:  Default constructor for Rules no variable
*				members set
*
*     Entry:	n/a
*
*     Exit:		n/a
*
****************************************************************/
State::State() {}


/**************************************************************
*	  Purpose:  Destructor of State
*
*     Entry:	n/a
*
*     Exit:		n/a
*
****************************************************************/
State::~State() {}
