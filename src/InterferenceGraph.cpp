//Autor: Petar Dimitrijevic
//Datum: 06.06.2024.

#include "InterferenceGraph.h"
#include "Constants.h"

#include <vector>
#include <iostream>

using namespace std;

static InterferenceGraph interferenceGraph;

InterferenceGraph& doInterferenceGraph(Instructions* instructions, Variables* variables)
{
	interferenceGraph.variables = variables;

	//Creating matrix
	InterferenceMatrix interferenceMatrix;
	interferenceMatrix.resize(interferenceGraph.variables->size());
	
	int i;
	for (i = 0; i < interferenceMatrix.size(); i++)
	{	
		interferenceMatrix[i].resize(interferenceMatrix.size());
	}


	interferenceGraph.matrix = interferenceMatrix;

	//Adding interference to matrix
	Instructions::iterator it;
	for (it = instructions->begin(); it != instructions->end(); it++)
	{
		if ((*it)->getType() != InstructionType::I_LI)
		{
			Variables::iterator vit;
			for (vit = (*it)->getDef().begin(); vit != (*it)->getDef().end(); vit++)
			{
				Variables::iterator vit1;
				for (vit1 = (*it)->getOut().begin(); vit1 != (*it)->getOut().end(); vit1++)
				{
					if (strcmp((*vit)->getName().c_str(), (*vit1)->getName().c_str()) && (*vit)->getType() == (*vit1)->getType())
					{
						interferenceGraph.matrix[(*vit)->getPosition()][(*vit1)->getPosition()] = __INTERFERENCE__;
						interferenceGraph.matrix[(*vit1)->getPosition()][(*vit)->getPosition()] = __INTERFERENCE__;
					}
				}
			}
		}
	}
	return interferenceGraph;
}


//Function for printing Interference matrix to command prompt
void printInterferenceGraph()
{
	cout << "--------------------------------------------------" << endl;
	cout << "		Interference Matrix:	   			   " << endl;
	cout << "--------------------------------------------------" << endl;

	Variables::iterator vit;
	InterferenceMatrix::iterator itm1;
	vector<int>::iterator itm2;
	for (vit = interferenceGraph.variables->begin(); vit != interferenceGraph.variables->end(); vit++)
	{
		cout << "\t " << (*vit)->getName();
	}
	cout << endl;

	vit = interferenceGraph.variables->begin();
	for (itm1 = interferenceGraph.matrix.begin(); itm1 != interferenceGraph.matrix.end(); itm1++)
	{
		cout << (*vit++)->getName();
		for (itm2 = (*itm1).begin(); itm2 != (*itm1).end(); itm2++)
		{
			cout << "\t " << *itm2;
		}
		cout << endl;
	}
	cout << "--------------------------------------------------" << endl;
}