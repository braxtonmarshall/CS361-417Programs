/**
*	Author: Braxton Marshall
*	Class: CS361 - Data Structures and Algorithms	
*	Problem # 1
*/
#include "Node.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <queue>
#include <list>
#include <set>
#include <cmath>
#include <map>

struct nodecompare
{
	bool operator() (const Node* left, const Node* right) const 
	{	
		if (left->getval() == right->getval())
		{
			return left->getdest() < right->getdest();
		}

		return left->getval() < right->getval();
	}
};
int main()
{	

	srand(time(NULL));
	std::map<Node*, int, nodecompare> Nodemap;
	std::map<Node*, int>::iterator nit;
	Node* nptr = nullptr;
	int N = 0;

	std::cout 	<< "*******************************************************" << '\n'
				<< " How many Nodes would you like to create? " << '\n';
	
	std::cin 	>> N;

	std::cout	<< '\n';


	// Generate Random Nodes and Add to Map
	for (int i = 0; i < N; i++)
	{	
		// New Node
		nptr = new Node();

		// Randomize
		nptr->setval(rand() % 20 + 1);
		nptr->setdest(rand() % 20 + 1);

		// Add to Map
		nit = Nodemap.find(nptr);
		if (nit != Nodemap.end())
		{	
			int j = nit->first->getfreq();
			Nodemap[nptr] = j + 1;
			nit->first->setfreq(j + 1);
		}
		else
		{
			Nodemap.insert (std::pair<Node*, int>(nptr, nptr->getfreq()) );
		}
	}


	// Display Map
	for (nit = Nodemap.begin(); nit != Nodemap.end(); ++nit)
	{
		nit->first->display(std::cout);
	}


	return 0;
}