//Autor: Petar Dimitrijevic
//Datum: 06.06.2024.

#include "ResourceAllocation.h"
#include "Constants.h"

bool doResourceAllocation(SimplificationStack* simplificationStack, InterferenceGraph* interferenceGraph)
{
	//Checking if the Simplification stack is created
	if (simplificationStack == NULL)
	{
		cout << "Simplification Stack is empty!" << endl;
		return false;
	}

	int size = simplificationStack->size();
	int v_size;


	vector<Variable> regVector;
	vector<Variable>::iterator vit;
	Variable* variable;

	int i;
	for (i = 0; i < size; i++)
	{

		variable = simplificationStack->top();
		simplificationStack->pop();
		int j = 0;
		variable->setAssignment(Regs(j));

		if (i != 0)
		{
			for (vit = regVector.begin(); vit != regVector.end(); vit++)
			{
				//Checking for interference between variables and assigning registers
				if (interferenceGraph->matrix[variable->getPosition()][vit->getPosition()] == __INTERFERENCE__) 
				{
					if (variable->getAssignment() == vit->getAssignment())
					{
						j++;
						variable->setAssignment(Regs(j));
					}
					else
					{
						variable->setAssignment(Regs(j));
					}
				}
				else if (interferenceGraph->matrix[variable->getPosition()][vit->getPosition()] == __EMPTY__)
				{
					variable->setAssignment(Regs(j));
				}
			}
		}
		//Pushing variables on stack
		regVector.push_back(*variable);
	}
	return true;
}