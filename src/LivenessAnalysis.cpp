//Autor: Petar Dimitrijevic
//Datum: 06.06.2024.

#include "LivenessAnalysis.h"
#include <iostream>
#include <list>

using namespace std;

void LivenessAnalysis(Instructions* instructions)
{
	Instructions::iterator it;
	for (it = instructions->begin(); it != instructions->end(); it++)
	{
		(*it)->getIn().clear();
		(*it)->getOut().clear();
	}

	bool repeat = true;
	int number_of_instructions = instructions->size();
	int counter = 0;

	while(repeat)
	{
		list<Instruction*>::reverse_iterator revIt;
		for (revIt = instructions->rbegin(); revIt != instructions->rend(); revIt++)
		{
			Variables tempIn = (*revIt)->getIn();
			Variables tempOut = (*revIt)->getOut();
			list<Instruction*>::iterator itOut;

			for (itOut = (*revIt)->getSucc().begin(); itOut != (*revIt)->getSucc().end(); itOut++)
			{
				list<Variable*>::iterator viOut;
				for (viOut = (*itOut)->getIn().begin(); viOut != (*itOut)->getIn().end(); viOut++) {
					(*revIt)->getOut().push_back(*viOut);
				}
			}
			(*revIt)->getOut().sort();
			(*revIt)->getOut().unique();

			(*revIt)->getIn() = (*revIt)->getUse();

			list<Variable*>::iterator viIn;
			list<Variable*>::iterator exists;
			for (viIn = (*revIt)->getOut().begin(); viIn != (*revIt)->getOut().end(); viIn++)
			{
				exists = find((*revIt)->getDef().begin(), (*revIt)->getDef().end(), *viIn);
				if (exists != (*revIt)->getDef().end())
				{
					continue;
				}
				else
				{
					(*revIt)->getIn().push_back(*viIn);
				}
			}

			(*revIt)->getIn().sort();
			(*revIt)->getIn().unique();

			if (tempOut == (*revIt)->getOut() && tempIn == (*revIt)->getIn())
			{
				counter++;
				if (counter == number_of_instructions) {
					repeat = false;
				}
			}
		}

	}
}