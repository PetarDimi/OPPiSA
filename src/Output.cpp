//Autor: Petar Dimitrijevic
//Datum: 06.06.2024.

#include "Output.h"

using namespace std;

//Function used for printing new MIPS code to output file
void writeOutput(Instructions& instructions, Labels& labels, Variables& variables, string name)
{
	ofstream outputFile(name);

	if (outputFile)
	{
		outputFile << ".globl main" << endl;
		outputFile << endl << ".data" << endl;
		Variables::iterator vit;

		//Setting memory registers
		for (vit = variables.begin(); vit != variables.end(); vit++)
		{
			if ((*vit)->getType() == Variable::MEM_VAR)
				outputFile << (*vit)->getName() << ":				.word	" << (*vit)->getValue() << endl;
		}

		outputFile << endl << ".text" << endl;
		Instructions::iterator it;
		for (it = instructions.begin(); it != instructions.end(); it++)
		{
			Labels::iterator lit;
			bool isLabel = false;
			for (lit = labels.begin(); lit != labels.end(); lit++)
			{
				if ((*lit)->getPosition() == (*it)->getPosition())
				{
					outputFile << (*lit)->getName() << ":" << endl;
					isLabel = true;
				}
			}

			int position = 0;
			string output = (*it)->getOutput();

			outputFile << "\t";

			//Replacing `d, `n, `l, `s for actual values
			while (output.find("`d") != -1)
			{
				position = output.find("`d");
				output.replace(position, 2, Registers[(*it)->getDestination().front()->getAssignment()]);
			}

			while (output.find("`n") != -1)
			{
				position = output.find("`n");
				output.replace(position, 2, to_string((*it)->getNum()));
			}

			while (output.find("`l") != -1)
			{
				position = output.find("`l");
				output.replace(position, 2, (*it)->getLabel()->getName());
			}

			while (output.find("`s") != -1)
			{
				position = output.find("`s");
				if ((*it)->getSource().front()->getType() == Variable::VariableType::MEM_VAR)
				{
					output.replace(position, 2, (*it)->getSource().front()->getName());
				}
				else
				{
					output.replace(position, 2, Registers[(*it)->getSource().front()->getAssignment()]);
				}
				(*it)->getSource().remove((*it)->getSource().front());
			}

			outputFile << output << endl;
		}
	}
	else
	{
		throw runtime_error("Couldn't create output file!");
	}
	outputFile.close();
}