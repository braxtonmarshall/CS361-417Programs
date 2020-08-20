/**
*
*	Author: Braxton Marshall
*	Class: CS361 - Data Structures and Algorithms	
*	Problem # 3
*/

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <utility>
#include <string>

class Node
{
	private:

		int id;		// ID of Node
		char ctype;	// Character Type of Node

	public:

		/*
		*	Constructor
		*/
		Node();

		/*
		*	Deconsctructor
		*/
		~Node();
		/*
		*	Returns ID of Node
		*/
		int getID() const;

		/*
		*	Sets ID of Node
		*/
		void setID(int i);

		/*
		*	Returns ctype of Node
		*/
		int getType() const;

		/*
		*	Sets ctype of Node
		*/
		void setType(char C);
		/*
		*	Print the Node
		*/
		void display(std::ostream &outs) const;
};

/**
*
*/
inline 
int Node::getID() const
{
	return this->id;
}

/**
*
*/
inline
void Node::setID(int i)
{
	this->id = i;
}

/**
*
*/
inline 
int Node::getType() const
{
	return this->ctype;
}

/**
*
*/
inline
void Node::setType(char C)
{
	this->ctype = C;
}

/**
*
*/
inline
std::ostream& operator<<( std::ostream& outs, const Node &prt )
{
	prt.display(outs);

	return outs;
}
#endif