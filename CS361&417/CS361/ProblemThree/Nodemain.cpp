/**
*	Author: Braxton Marshall
*	Class: CS361 - Data Structures and Algorithms	
*	Problem # 3
*/
#include "Node.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <queue>
#include <list>
#include <set>
#include <cmath>

struct idcomp 
{
	bool operator() (const Node* left, const Node* right) const 
	{
		return left->getID() < right->getID();
	}
};

struct CompareNode
{
	bool operator() (const Node* left, const Node* right) const
	{
		return left->getType() > right->getType();
	}
};

int main()
{	
	srand (time(NULL));
	std::list<Node*> Nodelist;
	std::priority_queue<Node*, std::vector<Node*>, CompareNode> pqueue;
	int choice=0;
	int id=0;
	char ctype;
	Node* nptr = nullptr;
	Node* ncurr = nullptr;

	std::cout 	<< "*******************************************************" << '\n'
				<< " How many Nodes would you like to create? " << '\n';
	
	std::cin 	>> choice;

	std::cout	<< '\n';


	for (int i = 0; i < choice; i++)
	{	
		// New Node
		nptr = new Node();

		// Randomize
		id = rand() % 11;
		nptr->setID(id);

		ctype = rand() % 26 + 65;
		nptr->setType(ctype);

		// Add to List
		Nodelist.push_back(nptr);
	}

	// Sort List by ID
	Nodelist.sort(idcomp());

	std::cout	<< " Displaying Node List..." << '\n' << '\n';
	// Display List & add to Priority Queue
	for (std::list<Node*>::iterator nit = Nodelist.begin(); nit != Nodelist.end(); ++nit)
	{
		ncurr = *nit;
		ncurr->display(std::cout);
		pqueue.push(ncurr);
	}
	std::cout 	<< '\n';
	std::cout	<< " Displaying Priority Queue..." << '\n' << '\n';
	while (!pqueue.empty())
	{
		ncurr = pqueue.top();
		ncurr->display(std::cout);
		pqueue.pop();
		delete ncurr;
	}

	return 0;
}