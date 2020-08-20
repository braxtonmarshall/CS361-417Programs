/**
*
*	Author: Braxton Marshall
*	Class: CS361 - Data Structures and Algorithms	
*	Problem # 1
*/

#include <iomanip>
#include "Node.h"

/**
*	Default Constructor
*/
Node::Node()
	:freq(1)
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
			<< std::setw(6)		<< " Node value: "
			<< std::setw(10)	<<	getval()
			<< std::setw(2)		<< " | "
			<< std::setw(11)	<< " Dest: "
			<< std::setw(2)		<< getdest()
			<< std::setw(2)		<< " | "
			<< std::setw(11)	<< " Frequency: "
			<< std::setw(2)		<< getfreq()
			<< "\n";	
}