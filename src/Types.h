#ifndef __TYPES__
#define __TYPES__

#include "Constants.h"

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <stack>

/**
* Supported token types.
*/
enum TokenType
{
	T_NO_TYPE,

	T_ID,			// abcd...
	T_M_ID,			// m123...
	T_R_ID,			// r123...
	T_NUM,			// 123...
	T_WHITE_SPACE,

	// reserved words
	T_MEM,			// _mem
	T_REG,			// _reg
	T_FUNC,			// _func
	T_ADD,			// add
	T_ADDI,			// addi
	T_SUB,			// sub
	T_LA,			// la
	T_LI,			// li
	T_LW,			// lw
	T_SW,			// sw
	T_BLTZ,			// bltz
	T_B,			// b
	T_NOP,			// nop
	T_DIV,			// div
	T_ORI,			// ori
	T_MULT,			//mult

	// operators
	T_COMMA,		//,
	T_L_PARENT,		//(
	T_R_PARENT,		//)
	T_COL,			//:
	T_SEMI_COL,		//;

	// utility
	T_COMMENT,
	T_END_OF_FILE,
	T_ERROR,
};


/**
 * Instruction type.
 */
enum InstructionType
{
	I_NO_TYPE = 0,
	I_ADD,
	I_ADDI,
	I_SUB,
	I_LA,
	I_LI,
	I_LW,
	I_SW,
	I_BLTZ,
	I_B,
	I_NOP,
	I_DIV,
	I_ORI,
	I_MULT
};

/**
 * Reg names.
 */
enum Regs
{
	no_assign = 0,
	t0,
	t1,
	t2,
	t3
};

#endif
