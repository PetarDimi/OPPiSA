//Autor: Petar Dimitrijevic
//Datum: 06.06.2024.

#include <sstream>

#include "FiniteStateMachine.h"

using namespace std;


const TokenType FiniteStateMachine::stateToTokenTable[NUM_STATES] = {
	/*state 00*/	T_NO_TYPE,
	/*state 01*/	T_NO_TYPE,
	/*state 02*/	T_NUM,
	/*state 03*/	T_COMMA,
	/*state 04*/	T_L_PARENT,
	/*state 05*/	T_R_PARENT,
	/*state 06*/	T_COL,
	/*state 07*/	T_SEMI_COL,
	/*state 08*/	T_WHITE_SPACE,
	/*state 09*/	T_NO_TYPE,
	/*state 10*/	T_ID,
	/*state 11*/	T_ID,
	/*state 12*/	T_ID,
	/*state 13*/	T_FUNC,
	/*state 14*/	T_ID,
	/*state 15*/	T_ID,
	/*state 16*/	T_MEM,
	/*state 17*/	T_ID,
	/*state 18*/	T_ID,
	/*state 19*/	T_REG,
	/*state 20*/	T_ID,
	/*state 21*/	T_M_ID,
	/*state 22*/	T_R_ID,
	/*state 23*/	T_ID,
	/*state 24*/	T_ID,
	/*state 25*/	T_ADD,
	/*state 26*/	T_ADDI,
	/*state 27*/	T_B,
	/*state 28*/	T_ID,
	/*state 29*/	T_ID,
	/*state 30*/	T_BLTZ,
	/*state 31*/	T_ID,
	/*state 32*/	T_LA,
	/*state 33*/	T_LW,
	/*state 34*/	T_ID,
	/*state 35*/	T_ID,
	/*state 36*/	T_NOP,
	/*state 37*/	T_ID,
	/*state 38*/	T_ID,
	/*state 39*/	T_SUB,
	/*state 40*/	T_SW,
	/*state 41*/	T_ERROR,
	/*state 42*/	T_LI,
	/*state 43*/	T_NO_TYPE,
	/*state 44*/	T_COMMENT,

	//Added instructions
	/*state 45*/	T_ID,
	/*state 46*/	T_ID,
	/*state 47*/	T_DIV,

	/*state 48*/	T_ID,
	/*state 49*/	T_ID,
	/*state 50*/	T_ORI,

	/*state 51*/	T_ID,
	/*state 52*/	T_ID,
	/*State 53*/	T_MULT,
};

const char FiniteStateMachine::supportedCharacters[NUM_OF_CHARACTERS] =
{
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
	'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
	'u', 'v', 'w', 'x', 'y', 'z',
	'_', ',', '(', ')', ':', ';', ' ', '\t', '\n', '\r', '/'
};

/*
	S - space,
	T - tab,
	E - enter,
	C - clear line
*/
const int FiniteStateMachine::stateMatrix[NUM_STATES][NUM_OF_CHARACTERS] =
{
				//	  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  _  ,  (  )  :  ;  S  T  E  C  /
	/* state 00 */	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// IDLE

	/* state 01 */	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,23,27,20,45,20,20,20,20,20,20,20,31,21,34,48,20,20,22,37,20,20,20,20,20,20,20, 9, 3, 4, 5, 6, 7, 8, 8, 8, 8,43},		// START_STATE
	
	/* state 02 */	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_NUM
	
	/* state 03 */	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_COMMA
	/* state 04 */	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_L_PARENT
	/* state 05 */	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_R_PARENT
	/* state 06 */	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_COL
	/* state 07 */	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_SEMI_COL
	/* state 08 */	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 0},		// T_WHITE_SPACE
	
	/* state 09 */	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,10,41,41,41,41,41,41,14,41,41,41,41,17,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41},		// _
	
	/* state 10 */	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,11,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41},		// F - T_ID
	/* state 11 */	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,12,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41},		// U - T_ID
	/* state 12 */	{41,41,41,41,41,41,41,41,41,41,41,41,13,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41},		// N - T_ID
	/* state 13 */	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41, 0, 0, 0, 0,41},		// T_FUNC

	/* state 14 */	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,15,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41},		// M - T_ID
	/* state 15 */	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,16,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41},		// E - T_ID
	/* state 16 */	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41, 0, 0, 0, 0,41},		// T_MEM

	/* state 17 */	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,18,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41},		// R - T_ID
	/* state 18 */	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,19,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41},		// E - T_ID
	/* state 19 */	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41, 0, 0, 0, 0,41},		// T_REG

	/* state 20 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_ID
	/* state 21 */	{21,21,21,21,21,21,21,21,21,21,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,51,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_M_ID
	/* state 22 */	{22,22,22,22,22,22,22,22,22,22,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_R_ID

	/* state 23 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,24,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// A - T_ID
	/* state 24 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,25,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// D - T_ID
	/* state 25 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,26,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_ADD
	/* state 26 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_ADDI

	/* state 27 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,28,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// B or T_B
	/* state 28 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,29,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// L - T_ID
	/* state 29 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,30,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T - T_ID
	/* state 30 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_BLTZ

	/* state 31 */	{20,20,20,20,20,20,20,20,20,20,32,20,20,20,20,20,20,20,42,20,20,20,20,20,20,20,20,20,20,20,20,20,33,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// L - T_ID
	/* state 32 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_LA
	/* state 33 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_LW

	/* state 34 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,35,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// N - T_ID
	/* state 35 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,36,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// O - T_ID
	/* state 36 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_NOP

	/* state 37 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,38,20,40,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// S - T_ID
	/* state 38 */	{20,20,20,20,20,20,20,20,20,20,20,39,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// U - T_ID
	/* state 39 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_SUB
	/* state 40 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_SW

	/* state 41 */	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_ERROR

	/* state 42 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_LI

				//	  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  _  ,  (  )  :  ;  S  T  E  C  /
	/* state 43 */	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,44},		// /
	/* state 44 */	{44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44, 0, 0,44},		// T_COMMENT

	//Added instructions
	/* state 45 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,46,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// D - T_ID
	/* state 46 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,47,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// I - T_ID
	/* state 47 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_DIV

	/* state 48 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,49,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// O - T_ID
	/* state 49 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,50,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// R - T_ID
	/* state 50 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_ORI

	/* state 51 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,52,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// U - T_ID
	/* state 52 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,53,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// L - T_ID
	/* state 53 */	{20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		// T_MULT

};


TokenType FiniteStateMachine::getTokenType(int stateNumber)
{
	return stateToTokenTable[stateNumber];
}


void FiniteStateMachine::initStateMachine()
{
	for (int i = 0; i < NUM_STATES; i++)
	{
		map<char, int> stateTransitions;
		for (int j = 0; j < NUM_OF_CHARACTERS; j++)
		{
			stateTransitions[supportedCharacters[j]] = stateMatrix[i][j];
		}
		stateMachine[i] = stateTransitions;
	}
}


int FiniteStateMachine::getNextState(int currentState, char transitionLetter)
{
	StateMachine::iterator it = stateMachine.find(currentState);
	
	if (it == stateMachine.end())
	{
		string strCurrentState;
		stringstream ss;
		ss << currentState;
		ss >> strCurrentState;
		string errMessage = "\nEXCEPTION: currentState = " + strCurrentState + " is not a valid state!";
		throw runtime_error(errMessage.c_str());
	}

	map<char, int>::iterator cit = it->second.find(transitionLetter);

	if (cit == it->second.end())
	{
		return INVALID_STATE;
	}
	else
	{
		return cit->second;
	}
}
