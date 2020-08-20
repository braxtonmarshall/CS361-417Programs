/**
*
*	Author: Braxton Marshall
*	Class: CS361 - Data Structures and Algorithms	
*	Problem # 3
*/

#include <iomanip>
#include "Node.h"

/**
*	Default Constructor
*/
Node::Node()
	:id(0)
{
}

/**
*	Deconstructor	
*/
Node::~Node()
{
}

/**
*	Display
*/
void Node::display( std::ostream& outs ) const
{
	outs	<< std::left
			<< std::setw(6)		<< " Node ID: "
			<< std::setw(16)	<<	getID()
			<< std::setw(2)		<< " | "
			<< std::setw(11)	<< " Ctype: "
			<< std::setw(2)		<< (char)getType()
			<< "\n";	
}