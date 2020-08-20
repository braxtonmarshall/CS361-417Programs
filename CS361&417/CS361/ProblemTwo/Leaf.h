/**
*
*	Author: Braxton Marshall
*	Class: CS361 - Data Structures and Algorithms	
*	Problem # 2
*/


#ifndef LEAF_H_INCLUDED
#define LEAF_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <utility>
#include <string>

class Leaf
{
	private:

		int id;	// ID of Leaf Object

	public:

		/*
		*	Constructor
		*/
		Leaf();

		/*
		*	Deconsctructor
		*/
		~Leaf();
		/*
		*	Returns ID of Leaf Object
		*/
		int getID() const;

		/*
		*	Sets ID of Leaf Object
		*/
		void setID(int i);

		/*
		*	Print the Leaf Object
		*/
		void display(std::ostream &outs) const;
};

/**
*
*/
inline 
int Leaf::getID() const
{
	return this->id;
}

/**
*
*/
inline
void Leaf::setID(int i)
{
	this->id = i;
}

/**
*
*/
inline
std::ostream& operator<<( std::ostream& outs, const Leaf &prt )
{
	prt.display(outs);

	return outs;
}
#endif