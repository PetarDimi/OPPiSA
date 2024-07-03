#ifndef __IR__
#define __IR__

#include "Types.h"
#include <list>
#include <vector>
#include <string>

using namespace std;
/**
 * This class represents one variable from program code.
 */
class Variable
{
public:
	enum VariableType
	{
		MEM_VAR,
		REG_VAR,
		NO_TYPE
	};

	Variable() : m_type(NO_TYPE), m_name(""), m_position(-1), m_assignment(no_assign) {}
	Variable(string name, int pos) : m_type(NO_TYPE), m_name(name), m_position(pos), m_assignment(no_assign) {}
	Variable(string name, VariableType v_type) : m_type(v_type), m_name(name), m_position(-1), m_assignment(no_assign){}

	void setType(VariableType type);
	void setName(string name);
	void setValue(int val);
	void setAssignment(Regs regs);
	void setPosition(int pos);

	int getPosition();
	string getName();
	Regs getAssignment();
	VariableType getType();
	int getValue();

private:
	VariableType m_type;
	string m_name;
	int m_position;
	int m_value;
	Regs m_assignment;
};

//***********************************

class Label
{
	string name;
	int position;

public:
	Label() {};
	Label(string n, int p) : name(n), position(p) {};
	
	void setName(string name);
	void setPosition(int Position);
	int getPosition();
	string getName();
	bool operator == (Label& lab) { return !strcmp(lab.name.c_str(), this->name.c_str()); }
};

/*
*This type represents list of labels
*/
typedef list<Label*> Labels;
static vector<string> Registers = { "$t0", "$t1", "$t2", "$t3", "$t4" };
static vector<string> Types = { "NO_TYPE", "ADD", "ADDI", "SUB", "LA", "LI", "LW", "SW", "BLTZ", "B", "NOP", "DIV", "ORI", "MULT" };

/**
 * This type represents list of variables from program code.
 */
typedef std::list<Variable*> Variables;


/**
 * This class represents one instruction in program code.
 */
class Instruction
{
public:
	Instruction () : m_position(0), m_type(I_NO_TYPE) {}
	Instruction (int pos, InstructionType type, Variables& dst, Variables& src) :
		m_position(pos), m_type(type), m_dst(dst), m_src(src) {}
	Instruction(InstructionType instruction) : m_position(0), m_type(instruction) {}

	void setDestination(Variables& destination);
	void setSource(Variables& source);
	void setUse(Variables& use);
	void setDef(Variables& def);
	void setIn(Variables& in);
	void setOut(Variables& out);
	void setSucc(list<Instruction*>& succ);
	void setPred(list<Instruction*>& pred);
	void setPosition(int pos);
	void setNum(int num);
	void setLabel(Label* label);
	void setOutput(string output);

	Variables &getDestination();
	Variables &getSource();
	Variables &getUse();
	Variables &getDef();
	Variables &getIn();
	Variables &getOut();
	list<Instruction*> &getSucc();
	list<Instruction*> &getPred();
	int getNum();
	int getPosition();
	Label* getLabel();
	string getOutput();
	InstructionType getType();


private:
	int m_position;
	InstructionType m_type;
	int m_num;
	Label* m_label;
	string m_output;
	
	Variables m_dst;
	Variables m_src;

	Variables m_use;
	Variables m_def;
	Variables m_in;
	Variables m_out;
	std::list<Instruction*> m_succ;
	std::list<Instruction*> m_pred;
};


//Vector and stack used in creating Simplification stack and Interference matrix
typedef std::vector<std::vector<int>> InterferenceMatrix;
typedef std::stack<Variable*> SimplificationStack;

typedef struct InterferenceGraphStructure
{
	Variables* variables;
	InterferenceMatrix matrix;
	char** values;

	InterferenceGraphStructure() {};
}InterferenceGraph;


/**
 * This type represents list of instructions from program code.
 */
typedef std::list<Instruction*> Instructions;


#endif
