/**
*	Author: Braxton Marshall
*	Class: CS361 - Data Structures and Algorithms	
*	Problem # 2
*/
#include "Leaf.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <queue>
#include <list>
#include <set>
#include <cmath>

/**
*
*/
int minIndex(std::queue<Leaf*> &q, int sortedIndex) 
{ 
    int min_index = -1; 
    int min_val = INT8_MAX; 
    int n = q.size(); 
    for (int i=0; i<n; i++) 
    { 	
    	Leaf* lcurr = q.front();
        int curr = lcurr->getID();
        q.pop();  
        if (curr <= min_val && i <= sortedIndex) 
        { 
            min_index = i; 
            min_val = curr; 
        } 
        q.push(lcurr);
    } 
    return min_index; 
}
/**
*	Move Minimum element to rear of queue
*/
void insertMinToRear(std::queue<Leaf*> &q, int min_index) 
{ 	
	Leaf* rearcurr = nullptr;
    int n = q.size(); 
    for (int i = 0; i < n; i++) 
    { 	
    	Leaf* lcurr = q.front();
        q.pop(); 
        if (i != min_index) 
            q.push(lcurr); 
        else
            rearcurr = lcurr; 
    } 
    q.push(rearcurr); 
}
/**
*
*/
void sortQueue(std::queue<Leaf*> &q) 
{ 
    for (int i = 1; i <= q.size(); i++) 
    { 
        int min_index = minIndex(q, q.size() - i); 
        insertMinToRear(q, min_index); 
    } 
} 


int main()
{	
	/**
	*	Seed Rand()
	*/
	srand (time(NULL));
	/**
	* 	Initiliaze Random Engine Generator
	*/
	std::random_device rd;
	std::default_random_engine generator(rd());

	/**
	*	Variable Declartions
	*/

	std::list<std::queue<Leaf*>> QueueList;
	std::set<int> UniqueSet;
	std::queue<Leaf*> Q_one;
	std::queue<Leaf*> Q_two;
	std::queue<Leaf*> Q_three;
	std::queue<Leaf*> Q_four;
	std::queue<Leaf*> Q_five;
	std::queue<Leaf*> Q_six;
	std::queue<Leaf*> Q_seven;
	std::queue<Leaf*> Q_eight;
	std::queue<Leaf*> Q_nine;
	Leaf* lptr = nullptr;
	int choice=0;
	int count=0;

	std::cout 	<< "*******************************************************" << '\n'
				<< " How many Leafs would you like to create? " << '\n';
	
	std::cin 	>> choice;

	std::cout	<< '\n';


	// Create Leaf Objects
	for (int i = 0; i < choice; i++)
	{	
		// Create new Leaf
		lptr = new Leaf();

		// Randomize ID with normal distribution
		std::normal_distribution<double> ndist(50.0, 10.0);
		double n = ndist(generator);

		// Round normal variable to int and add to leaf object
		int leafid = std::round(n);
		lptr->setID(leafid);

		// Add to Appropriate Queue if Leaf ID is Unique
		if (UniqueSet.find(leafid) == UniqueSet.end())
		{	
			UniqueSet.insert(leafid);
			if (leafid < 10)
			{	
				Q_one.push(lptr);
			}

			if (leafid >= 10 && leafid < 20)
			{
				Q_two.push(lptr);				
			}
			
			if (leafid >= 20 && leafid < 30)
			{
				Q_three.push(lptr);
			}

			if (leafid >= 30 && leafid < 40)
			{
				Q_four.push(lptr);
			}

			if (leafid >= 40 && leafid < 50)
			{
				Q_five.push(lptr);
			}

			if (leafid >= 50 && leafid < 60)
			{
				Q_six.push(lptr);
			}

			if (leafid >= 60 && leafid < 70)
			{
				Q_seven.push(lptr);
			}

			if (leafid >= 70 && leafid < 80)
			{
				Q_eight.push(lptr);
			}

			if (leafid >= 80)
			{
				Q_nine.push(lptr);
			}
		}
		else 
		{	
			std::cout << " Value: " << leafid << " wasn't unique. Deleting Leaf Object..." << '\n';
			std::cout << '\n';
			delete lptr;
		}
	}

	// Add Queues to List
	QueueList.push_back(Q_one);
	QueueList.push_back(Q_two);
	QueueList.push_back(Q_three);
	QueueList.push_back(Q_four);
	QueueList.push_back(Q_five);
	QueueList.push_back(Q_six);
	QueueList.push_back(Q_seven);
	QueueList.push_back(Q_eight);
	QueueList.push_back(Q_nine);

	// Sort Queues in List

	for (std::list<std::queue<Leaf*>>::iterator qit = QueueList.begin(); qit != QueueList.end(); ++qit)
	{
		sortQueue(*qit);
	}

	// Display Queues in List
	
	for (std::list<std::queue<Leaf*>>::iterator qit = QueueList.begin(); qit != QueueList.end(); ++qit)
	{	
		std::cout << " Queue Number: " << count << '\n';
		std::queue<Leaf*> qcurr = *qit;

		while(qcurr.empty() == false)
		{
			lptr = qcurr.front();
			qcurr.pop();
			lptr->display(std::cout);
			delete lptr;
		}
		count++;
	}

	return 0;
}