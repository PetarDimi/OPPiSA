//Autor: Petar Dimitrijevic
//Datum: 06.06.2024.

#include <iostream>
#include <exception>

#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"
#include "LivenessAnalysis.h"
#include "InterferenceGraph.h"
#include "SimplificationStack.h"
#include "ResourceAllocation.h"
#include "Output.h"

using namespace std;


int main()
{
	try
	{
		std::string fileName = ".\\..\\examples\\multiply.mavn";
		bool retVal = false;
		cout << "Projektni zadatak iz OPPiSA 2023/2024" << endl << "Petar Dimitrijevic RA207-2018" << endl << endl;


		//Lexical Analysis here
		LexicalAnalysis lex;

		if (!lex.readInputFile(fileName))
			throw runtime_error("\nException! Failed to open input file!\n");

		lex.initialize();
		retVal = lex.Do();

		if (retVal)
		{
			cout << "Lexical analysis finished successfully!" << endl << endl;
			lex.printTokens();
		}
		else
		{
			lex.printLexError();
			throw runtime_error("\nException! Lexical analysis failed!\n");
		}
		//Syntax Analysis here
		SyntaxAnalysis syn(lex);
		retVal = syn.Do();

		if (retVal)
		{
			cout << "Syntax analysis finished successfully!" << endl << endl;
		}
		else
		{
			throw runtime_error("\nException! Syntax analysis failed!\n");
		}
		syn.FillPredAndSucc();
		syn.printInstructions(&syn.instructions);

		//Liveness Analysis here
		LivenessAnalysis(&syn.instructions);
		cout << "Liveness Analysis finished successfully!" << endl << endl;
		syn.printInstructions(&syn.instructions);

		//Interference graph and Simplification stack here
		Variables* var = &syn.registerVariables;
		InterferenceGraph interGraph = doInterferenceGraph(&syn.instructions, var);
		SimplificationStack simpStack;
		SimplificationStack simplificationStack = doSimplificationStack(&interGraph, &simpStack);
		interGraph = doInterferenceGraph(&syn.instructions, var);
		
		printInterferenceGraph();

		//Resource allocation here
		if (doResourceAllocation(&simplificationStack, &interGraph)) {
			cout << "Resource Allocation finished successfully!" << endl;
			syn.printInstructions(&syn.instructions);
			cout << endl << "*** Program finished successfully! ***" << endl;
		}
		else
			cout << "Resource Allocation failed!" << endl;

		//Writing code in output file here
		string name = ".\\..\\examples\\multiply.out.s";
		writeOutput(syn.instructions, syn.labels, syn.variables, name);
		
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}
