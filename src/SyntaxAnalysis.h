#pragma once

#include "LexicalAnalysis.h"
#include "Token.h"
#include "IR.h"

#include <string>

class SyntaxAnalysis
{
public:

	/**
	* Constructor
	*/
	SyntaxAnalysis(LexicalAnalysis& lex);

	/**
	* Method which performs lexical analysis
	*/
	bool Do();

	Variables variables;
	Variables registerVariables;
	Instructions instructions;
	Labels labels;
	int registerCount = -1;

	bool checkName(string& current);
	void addVariable(Instruction* inst, bool src, bool reg);
	void addLabel(Instruction* inst);

	Variable* getVariable(Variable* var);

	void printInstructions(Instructions* instruc);
	void FillPredAndSucc();
	bool labelExists(Label* label);
	bool variableExists(Variable* variable);

private:
	/**
	* Prints the error message, and token that caused the syntax error
	*/
	void printSyntaxError(Token token);

	/**
	* Prints the token info
	*/
	void printTokenInfo(Token token);

	/**
	* Eats the current token if its type is "t"
	* otherwise reports syntax error
	*
	* param[in] - t - the expected token type
	*/
	void eat(TokenType t);

	/**
	* Returns the next token from the token list
	*/
	Token getNextToken();

	/**
	 * Nonterminal Q
	 */
	void Q();

	/**
	 * Nonterminal S
	 */
	void S();

	/**
	 * Nonterminal L
	 */
	void L();

	/**
	 * Nonterminal E
	 */
	void E();

	/**
	* Reference to lexical analysis module
	*/
	LexicalAnalysis& lexicalAnalysis;

	/**
	* Syntax error indicator
	*/
	bool errorFound;

	/**
	* Iterator to the token list which represents the output of the lexical analysis
	*/
	TokenList::iterator tokenIterator;

	/**
	* Current token that is being analyzed
	*/
	Token currentToken;

	int instructionPosition;

	
};