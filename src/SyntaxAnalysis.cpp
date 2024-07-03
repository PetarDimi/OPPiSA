//Autor: Petar Dimitrijevic
//Datum: 06.06.2024.

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <regex>
#include <algorithm>
#include <string>

#include "SyntaxAnalysis.h"

using namespace std;

SyntaxAnalysis::SyntaxAnalysis(LexicalAnalysis& lex) : lexicalAnalysis(lex), errorFound(false), instructionPosition(1)
{
	tokenIterator = lexicalAnalysis.getTokenList().begin();
}

bool SyntaxAnalysis::Do() 
{
	currentToken = getNextToken();

	Q();
	if (--tokenIterator == lexicalAnalysis.getTokenList().begin()) 
	{
		return false;
	}
	else
	{
		return !errorFound;
	}
}

void SyntaxAnalysis::printSyntaxError(Token token)
{
	cout << "Syntax error! Token: " << token.getValue() << " unexpected" << endl;
}

void SyntaxAnalysis::eat(TokenType t)
{
	if (errorFound == false)
	{
		if (currentToken.getType() == t)
		{
			cout << currentToken.getValue() << endl;
			if (t != T_END_OF_FILE)
			{
				currentToken = getNextToken();
			}
		}

		else
		{
			printSyntaxError(currentToken);
			errorFound = true;
		}
	}
}

Token SyntaxAnalysis::getNextToken()
{
	if (tokenIterator == lexicalAnalysis.getTokenList().end())
		throw runtime_error("End of input file reached");
	return *tokenIterator++;
}

void SyntaxAnalysis::Q()
{
	if (!errorFound == true)
	{
		S();
		eat(T_SEMI_COL);
		L();
	}
	else {
		printSyntaxError(currentToken);
		errorFound = true;
	}
}

void SyntaxAnalysis::S()
{
	if (!errorFound == true)
	{
		if (currentToken.getType() == T_MEM)
		{
			eat(T_MEM);
			Variable* var = new Variable(currentToken.getValue(), Variable::VariableType::MEM_VAR);
			eat(T_M_ID);
			var->setValue(atoi(currentToken.getValue().c_str()));

			if (!checkName(currentToken.getValue()))
			{
				errorFound = true;
				throw runtime_error("Memory incorrectly allocated!");
			}

			if (variableExists(var))
			{
				errorFound = true;
				throw runtime_error("Variable already exists!");
			}

			variables.push_back(var);
			eat(T_NUM);
		}
		else if (currentToken.getType() == T_REG)
		{
			eat(T_REG);
			Variable* var = new Variable(currentToken.getValue(), Variable::VariableType::REG_VAR);

			if (!checkName(currentToken.getValue().substr(1, 2)))
			{
				errorFound = true;
				throw runtime_error("Memory incorrectly allocated!");
			}

			if (variableExists(var))
			{
				errorFound = true;
				throw runtime_error("Variable already exists!");
			}

			variables.push_back(var);
			registerCount++;
			var->setPosition(registerCount);
			registerVariables.push_back(var);

			eat(T_R_ID);
		}
		else if (currentToken.getType() == T_FUNC)
		{
			eat(T_FUNC);
			
			if (!isalpha(currentToken.getValue()[0]))
			{
				errorFound = true;
				throw runtime_error("Function name should start with capital letter!");
			}

			Label* label = new Label("main", instructionPosition);
			labels.push_back(label);
			eat(T_ID);
		}
		else if (currentToken.getType() == T_ID)
		{
			Label* label = new Label(currentToken.getValue(), instructionPosition);

			if (labelExists(label))
			{
				errorFound = true;
				throw runtime_error("Label already exists!");
			}

			labels.push_back(label);
			eat(T_ID);
			eat(T_COL);
			E();
		}
		else
			E();
	}
	else
	{
		errorFound = true;
		printSyntaxError(currentToken);
	}
}

void SyntaxAnalysis::L()
{
	if (!errorFound == true)
	{
		if (currentToken.getType() == T_END_OF_FILE)
		{
			eat(T_END_OF_FILE);
		}
		else
		{
			Q();
		}
	}
	else
	{
		errorFound = true;
		printSyntaxError(currentToken);
	}
}


void SyntaxAnalysis::E()
{
	if (!errorFound == true)
	{
		if (currentToken.getType() == T_ADD)
		{
			eat(T_ADD);
			Instruction* inst = new Instruction(I_ADD);
			inst->setOutput("add			`d, `s, `s");
			addVariable(inst, true, false);
			eat(T_R_ID);
			eat(T_COMMA);
			addVariable(inst, true, true);
			eat(T_R_ID);
			eat(T_COMMA);
			addVariable(inst, true, true);
			eat(T_R_ID);

			inst->setPosition(instructionPosition++);
			instructions.push_back(inst);

		}
		else if (currentToken.getType() == T_ADDI)
		{
			eat(T_ADDI);
			Instruction* inst = new Instruction(I_ADDI);
			inst->setOutput("addi		`d, `s, `n");
			addVariable(inst, true, false);
			eat(T_R_ID);
			eat(T_COMMA);
			addVariable(inst, true, true);
			eat(T_R_ID);
			eat(T_COMMA);
			inst->setNum(atoi(currentToken.getValue().c_str()));
			eat(T_NUM);

			inst->setPosition(instructionPosition++);
			instructions.push_back(inst);
		}
		else if (currentToken.getType() == T_SUB)
		{
			eat(T_SUB);
			Instruction* inst = new Instruction(I_SUB);
			inst->setOutput("sub			`d, `s, `s");
			addVariable(inst, true, false);
			eat(T_R_ID);
			eat(T_COMMA);
			addVariable(inst, true, true);
			eat(T_R_ID);
			eat(T_COMMA);
			addVariable(inst, true, true);
			eat(T_R_ID);

			inst->setPosition(instructionPosition++);
			instructions.push_back(inst);
		}
		else if (currentToken.getType() == T_LA)
		{
			eat(T_LA);
			Instruction* inst = new Instruction(I_LA);
			inst->setOutput("la			`d, `s");
			addVariable(inst, true, false);
			eat(T_R_ID);
			eat(T_COMMA);
			addVariable(inst, false, true);
			eat(T_M_ID);

			inst->setPosition(instructionPosition++);
			instructions.push_back(inst);
		}
		else if (currentToken.getType() == T_LW)
		{
			eat(T_LW);
			Instruction* inst = new Instruction(I_LW);
			inst->setOutput("lw			`d, `n(`s)");
			addVariable(inst, true, false);
			eat(T_R_ID);
			eat(T_COMMA);
			inst->setNum(atoi(currentToken.getValue().c_str()));
			eat(T_NUM);
			eat(T_L_PARENT);
			addVariable(inst, true, true);
			eat(T_R_ID);
			eat(T_R_PARENT);

			inst->setPosition(instructionPosition++);
			instructions.push_back(inst);
		}
		else if (currentToken.getType() == T_LI)
		{
			eat(T_LI);
			Instruction* inst = new Instruction(I_LI);
			inst->setOutput("li			`d, `n");
			addVariable(inst, true, false);
			eat(T_R_ID);
			eat(T_COMMA);
			inst->setNum(atoi(currentToken.getValue().c_str()));
			eat(T_NUM);

			inst->setPosition(instructionPosition++);
			instructions.push_back(inst);
		}
		else if (currentToken.getType() == T_SW)
		{
			eat(T_SW);
			Instruction* inst = new Instruction(I_SW);
			inst->setOutput("sw			`s, `n(`s)");
			addVariable(inst, true, true);
			eat(T_R_ID);
			eat(T_COMMA);
			inst->setNum(atoi(currentToken.getValue().c_str()));
			eat(T_NUM);
			eat(T_L_PARENT);
			addVariable(inst, true, true);
			eat(T_R_ID);
			eat(T_R_PARENT);

			inst->setPosition(instructionPosition++);
			instructions.push_back(inst);
		}
		else if (currentToken.getType() == T_B)
		{
			eat(T_B);
			Instruction* inst = new Instruction(I_B);
			inst->setOutput("b			`l");
			addLabel(inst);
			eat(T_ID);


			inst->setPosition(instructionPosition++);
			instructions.push_back(inst);
		}
		else if (currentToken.getType() == T_BLTZ)
		{
			eat(T_BLTZ);
			Instruction* inst = new Instruction(I_BLTZ);
			inst->setOutput("bltz		`s, `l");
			addVariable(inst, true, true);
			eat(T_R_ID);
			eat(T_COMMA);
			addLabel(inst);
			eat(T_ID);

			inst->setPosition(instructionPosition++);
			instructions.push_back(inst);
		}
		//Added instruction number 1
		else if (currentToken.getType() == T_DIV)
		{
			eat(T_DIV);
			Instruction* inst = new Instruction(I_DIV);
			inst->setOutput("div			`d, `s");
			addVariable(inst, true, false);
			eat(T_R_ID);
			eat(T_COMMA);
			addVariable(inst, true, true);
			eat(T_R_ID);

			inst->setPosition(instructionPosition++);
			instructions.push_back(inst);
		}
		//Added instruction number 2
		else if (currentToken.getType() == T_ORI)
		{
			eat(T_ORI);
			Instruction* inst = new Instruction(I_ORI);
			inst->setOutput("ori			`d, `s, `n");
			addVariable(inst, true, false);
			eat(T_R_ID);
			eat(T_COMMA);
			addVariable(inst, true, true);
			eat(T_R_ID);
			eat(T_COMMA);
			inst->setNum(atoi(currentToken.getValue().c_str()));
			eat(T_NUM);

			inst->setPosition(instructionPosition++);
			instructions.push_back(inst);
		}
		//Added instruction number 3
		else if (currentToken.getType() == T_MULT)
		{
			eat(T_MULT);
			Instruction* inst = new Instruction(I_MULT);
			inst->setOutput("mult		`d, `s");
			addVariable(inst, true, false);
			eat(T_R_ID);
			eat(T_COMMA);
			addVariable(inst, true, true);
			eat(T_R_ID);

			inst->setPosition(instructionPosition++);
			instructions.push_back(inst);
		}
		else
		{
			eat(T_NOP);
			Instruction* inst = new Instruction(I_NOP);
			inst->setOutput("nop");

			inst->setPosition(instructionPosition++);
			instructions.push_back(inst);
		}
	}
	else
	{
		errorFound = true;
		printSyntaxError(currentToken);
	}
}
//Used for checking name for error notifications
bool SyntaxAnalysis::checkName(string& current)
{
	return std::all_of(current.begin(), current.end(), ::isdigit);
}
//Used for checking existing labels for error notifications
bool SyntaxAnalysis::labelExists(Label* label)
{
	list<Label*>::iterator it;
	for (it = labels.begin(); it != labels.end(); it++)
	{
		if (*label == **it)
			return true;
	}
}
//Used for checking existing variables for error notifications
bool SyntaxAnalysis::variableExists(Variable* variable)
{
	list<Variable*>::iterator it;
	for (it = variables.begin(); it != variables.end(); it++)
	{
		if (!strcmp(variable->getName().c_str(), (*it)->getName().c_str()) && variable->getType() == (*it)->getType())
			return true;
	}
}
//Function used for pushin variable on stack(Source,Destination,Def,Use etc)
Variable* SyntaxAnalysis::getVariable(Variable* var)
{
	list<Variable*>::iterator it;

	for (it = variables.begin(); it != variables.end(); it++)
	{
		if (var->getName() == (*it)->getName())
			return *it;
	}
}

void SyntaxAnalysis::addVariable(Instruction* inst, bool reg, bool src)
{
	Variable* var = new Variable;
	var->setName(currentToken.getValue());

	if (reg)
	{
		var->setType(Variable::VariableType::REG_VAR);
	}
	else
	{
		var->setType(Variable::VariableType::MEM_VAR);
	}
	
	if (!variableExists(var))
		throw runtime_error("Variable is not defined!");

	if (src)
	{
		inst->getSource().push_back(getVariable(var));
		inst->getUse().push_back(getVariable(var));
	}
	else
	{
		inst->getDef().push_back(getVariable(var));
		inst->getDestination().push_back(getVariable(var));
	}
}

void SyntaxAnalysis::addLabel(Instruction* inst)
{
	list<Label*>::iterator it;
	for (it = labels.begin(); it != labels.end(); it++)
	{
		if (!strcmp(currentToken.getValue().c_str(), (*it)->getName().c_str()))
		{
			(*inst).setLabel(*it);
		}
	}
}

void SyntaxAnalysis::FillPredAndSucc()
{
	Instructions::iterator it1;
	Instructions::iterator it2;
	for (it1 = instructions.begin(); it1 != instructions.end(); it1++)
	{
		if ((*it1)->getType() == InstructionType::I_B)
		{
			for (it2 = instructions.begin(); it2 != instructions.end(); it2++)
			{
				if ((*it2)->getPosition() == (*it1)->getLabel()->getPosition())
				{
					(*it1)->getSucc().push_back(*it2);
					(*it2)->getPred().push_back(*it1);
				}
			}
		}
		else
		{
			Instructions::iterator it3;
			for (it3 = instructions.begin(); it3 != instructions.end(); it3++)
			{
				if ((*it1)->getPosition() + 1 == (*it3)->getPosition())
				{
					(*it1)->getSucc().push_back(*it3);
					(*it3)->getPred().push_back(*it1);

					if ((*it1)->getType() == InstructionType::I_BLTZ)
					{
						Instructions::iterator it4;
						for (it4 = instructions.begin(); it4 != instructions.end(); it4++)
						{
							if ((*it4)->getPosition() == (*it1)->getLabel()->getPosition())
							{
								(*it1)->getSucc().push_back(*it4);
								(*it4)->getPred().push_back(*it1);
							}
						}
					}
				}
			}
		}
	}
}

//Printing instructions to command prompt
void SyntaxAnalysis::printInstructions(Instructions* instruc)
{
	Instructions::iterator it;
	for (it = instructions.begin(); it != instructions.end(); it++)
	{
		int counter1 = 1;
		int counter2 = 1;

		Variables::iterator vit;
		Instructions::iterator it1;

		cout << "Type: " << Types[(*it)->getType()] << " Position: " << (*it)->getPosition() << endl;
		cout << "--------------------------------------------------" << endl;

		for (vit = (*it)->getDestination().begin(); vit != (*it)->getDestination().end(); vit++)
		{
			cout << "Destination:" << counter1++ << "	Name:" << (*vit)->getName() << "  Position:" << (*it)->getPosition() << "  Assignment:" << (*vit)->getAssignment() << endl;
		}

		for (vit = (*it)->getSource().begin(); vit != (*it)->getSource().end(); vit++)
		{
			cout << "Source:" << counter2++ << "	Name:" << (*vit)->getName() << "  Position:" << (*vit)->getPosition() << "  Assignment:" << (*vit)->getAssignment() << endl;
		}
		cout << "--------------------------------------------------" << endl;

		cout << "Pred: ";
		for (it1 = (*it)->getPred().begin(); it1 != (*it)->getPred().end(); it1++)
			cout << (*it1)->getPosition() << " ";
		cout << endl;

		cout << "Succ: ";
		for (it1 = (*it)->getSucc().begin(); it1 != (*it)->getSucc().end(); it1++)
			cout << (*it1)->getPosition() << " ";
		cout << endl;

		cout << "Use: ";
		for (vit = (*it)->getUse().begin(); vit != (*it)->getUse().end(); vit++)
			if ((*vit)->getType() != Variable::VariableType::MEM_VAR)
				cout << (*vit)->getName() << " ";
		cout << endl;

		cout << "Def: ";
		for (vit = (*it)->getDef().begin(); vit != (*it)->getDef().end(); vit++)
			if ((*vit)->getType() != Variable::VariableType::MEM_VAR)
				cout << (*vit)->getName() << " ";
		cout << endl;

		cout << "In: ";
		for (vit = (*it)->getIn().begin(); vit != (*it)->getIn().end(); vit++)
			if ((*vit)->getType() != Variable::VariableType::MEM_VAR)
				cout << (*vit)->getName() << " ";
		cout << endl;

		cout << "Out: ";
		for (vit = (*it)->getOut().begin(); vit != (*it)->getOut().end(); vit++)
			if ((*vit)->getType() != Variable::VariableType::MEM_VAR)
				cout << (*vit)->getName() << " ";
		cout << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "--------------------------------------------------" << endl << endl;

	}
}