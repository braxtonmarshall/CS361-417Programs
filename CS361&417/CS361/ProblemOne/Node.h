/**
*
*	Author: Braxton Marshall
*	Class: CS361 - Data Structures and Algorithms	
*	Problem # 1
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

		int val;	// Value of Node
		int freq;	// Frequency of Node
		int dest;	// Destination of Node
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
		*	Returns Val of Node
		*/
		int getval() const;

		/*
		*	Sets Val of Node
		*/
		void setval(int v);

		/*
		*	Returns frequency of Node
		*/
		int getfreq() const;

		/*
		*	Sets frequency of Node
		*/
		void setfreq(int f);

		/*
		*	Returns dest of Node
		*/
		int getdest() const;

		/*
		*	Sets dest of Node
		*/
		void setdest(int d);
		/*
		*	Print the Node
		*/
		void display(std::ostream &outs) const;
};

/**
*
*/
inline 
int Node::getval() const
{
	return this->val;
}

/**
*
*/
inline
void Node::setval(int v)
{
	this->val = v;
}

/**
*
*/
inline 
int Node::getfreq() const
{
	return this->freq;
}

/**
*
*/
inline
void Node::setfreq(int f)
{
	this->freq = f;
}

/**
*
*/
inline 
int Node::getdest() const
{
	return this->dest;
}

/**
*
*/
inline
void Node::setdest(int d)
{
	this->dest = d;
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