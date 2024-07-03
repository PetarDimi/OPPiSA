//Autor: Petar Dimitrijevic
//Datum: 06.06.2024.

#include "SimplificationStack.h"
#include "Constants.h"

SimplificationStack& doSimplificationStack(InterferenceGraph* interferenceGraph, SimplificationStack* simplificationStack)
{
	vector<int> variables(interferenceGraph->variables->size());
	int position;
	int maxNeighbours;
	int i;
	int size = interferenceGraph->variables->size();

	while (size > 0)
	{
		maxNeighbours = 0;
		position = 0;

		//Checking which variable has the most neighbours
		for (i = 0; i < interferenceGraph->variables->size(); i++)
		{
			int counter = 0;
			int j;
			for (j = 0; j < interferenceGraph->variables->size(); j++)
			{
				if (interferenceGraph->matrix[i][j] == __INTERFERENCE__)
					counter++;
			}
			if (counter > maxNeighbours)
			{
				maxNeighbours = counter;
				position = i;
			}
		}

		if (maxNeighbours > __REG_NUMBER__)
		{
			throw runtime_error("Insufficient number of resources!");
		}
		//Removing all neighbours from Interference graph
		for (i = 0; i < interferenceGraph->matrix.size(); i++)
		{
			interferenceGraph->matrix[position][i] = 0;
			interferenceGraph->matrix[i][position] = 0;
		}

		Variables::iterator vit;

		if (maxNeighbours != 0)
		{
			for (vit = interferenceGraph->variables->begin(); vit != interferenceGraph->variables->end(); vit++)
			{
				if ((*vit)->getPosition() == position)
					simplificationStack->push(*vit);
			}
			variables.push_back(position);
		}
		else
		{
			//Pushing variables left with no neighbours on stack
			Variables::iterator vit1;
			bool alreadyOnStack;
			for (vit1 = interferenceGraph->variables->begin(); vit1 != interferenceGraph->variables->end(); vit1++)
			{
				alreadyOnStack = false;
				int i;
				for (i = 0; i < variables.size(); i++)
				{
					if ((*vit1)->getPosition() == variables[i])
						alreadyOnStack = true;
				}
				if (!alreadyOnStack)
					simplificationStack->push(*vit1);
			}
			return *simplificationStack;
		}
		size--;
	}
}