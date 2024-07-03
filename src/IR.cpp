//Autor: Petar Dimitrijevic
//Datum: 06.06.2024.

#include <iostream>

#include "IR.h"

using namespace std;

//Label set and get functions
//***********************************
void Label::setName(string name)
{
	this->name = name;
}

void Label::setPosition(int pos)
{
	this->position = pos;
}

string Label::getName()
{
	return this->name;
}
 
int Label::getPosition()
{
	return this->position;
}
//***********************************


//Variable set and get functions
//***********************************
void Variable::setType(VariableType type)
{
	this->m_type = type;
}

void Variable::setName(string name)
{
	this->m_name = name;
}

void Variable::setValue(int val)
{
	this->m_value = val;
}

void Variable::setAssignment(Regs reg)
{
	this->m_assignment = reg;
}

void Variable::setPosition(int pos)
{
	this->m_position = pos;
}

int Variable::getPosition()
{
	return this->m_position;
}

Regs Variable::getAssignment()
{
	return this->m_assignment;
}

Variable::VariableType Variable::getType()
{
	return this->m_type;
}

std::string Variable::getName()
{
	return this->m_name;
}

int Variable::getValue()
{
	return this->m_value;
}
//***********************************


//Instruction set and get functions
//***********************************
void Instruction::setDestination(Variables& destination)
{
	this->m_dst = destination;
}

void Instruction::setSource(Variables& source)
{
	this->m_src = source;
}

void Instruction::setUse(Variables& use)
{
	this->m_use = use;
}

void Instruction::setDef(Variables& def)
{
	this->m_def = def;
}
void Instruction::setIn(Variables& in)
{
	this->m_in = in;
}
void Instruction::setOut(Variables& out)
{
	this->m_out = out;
}

void Instruction::setSucc(list<Instruction*>& succ)
{
	this->m_succ = succ;
}

void Instruction::setPred(list<Instruction*>& pred)
{
	this->m_pred = pred;
}

void Instruction::setPosition(int pos)
{
	this->m_position = pos;
}

void Instruction::setNum(int num)
{
	this->m_num = num;
}

void Instruction::setLabel(Label* label)
{
	this->m_label = label;
}

void Instruction::setOutput(string output)
{
	this->m_output = output;
}

Variables& Instruction::getDestination()
{
	return this->m_dst;
}

Variables& Instruction::getSource()
{
	return this->m_src;
}

Variables& Instruction::getUse()
{
	return this->m_use;
}

Variables& Instruction::getDef()
{
	return this->m_def;
}

Variables& Instruction::getIn()
{
	return this->m_in;
}

Variables& Instruction::getOut()
{
	return this->m_out;
}

list<Instruction*>& Instruction::getSucc()
{
	return this->m_succ;
}

list<Instruction*>& Instruction::getPred()
{
	return this->m_pred;
}

int Instruction::getNum()
{
	return this->m_num;
}

int Instruction::getPosition()
{
	return this->m_position;
}

Label* Instruction::getLabel()
{
	return this->m_label;
}

string Instruction::getOutput()
{
	return this->m_output;
}

InstructionType Instruction::getType()
{
	return this->m_type;
}
//***********************************