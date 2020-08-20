/**
*
*	Author: Braxton Marshall
*	Class: CS361 - Data Structures and Algorithms	
*	Problem # 2
*/

#include <iomanip>
#include "Leaf.h"

/**
*	Default Constructor
*/
Leaf::Leaf()
	:id(0)
{
}

/**
*	Deconstructor	
*/
Leaf::~Leaf()
{
}

/**
*	
*/
void Leaf::display( std::ostream& outs ) const
{
	outs	<< std::left
			<< std::setw(6)		<< " Leaf ID:"
			<< std::setw(16)	<<	getID()
			<< "\n";	
}