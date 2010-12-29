/*   This file is part of Atto.
 *
 *   Atto is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Atto is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Atto.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _OPCODES_H_
#define _OPCODES_H_

/* atto opcodes */
typedef enum {
  OP_NOP,
  
  /* basic stack ops */
  OP_POP,  
  OP_DUP,
  OP_SWAP,

  /* math ops */
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_MOD,
  OP_POW,

  /* bitwise ops */
  OP_OR,
  OP_AND,
  OP_XOR,
  OP_NOT,

  /* comparison ops */
  OP_EQ,
  OP_LT,
  OP_GT,
  OP_LTE,
  OP_GTE,
  OP_CMP,

  /* flow of control ops */
  OP_IF,        // if [stack], exec next inst, otherwise skip
  OP_JMP,       // pc += [stack]

  /* const ops */
  OP_PUSHCONST, // push const[++pc] on to stack
  
  /* var ops */
  OP_PUSHVAR,   // push var[++pc] on to stack
  OP_SETVAR,    // var[++pc] = [stack]
  OP_VALUEVAR,  // push value of var on top of stack onto stack

  /* IO */
  OP_PRINT,
  OP_DUMPSTACK, 
  
  NUM_OPS        /* how many opcodes are there? */

} AttoOpCodes;

#define OPCODE_NAMES "nop",			\
    "pop", "dup", "swap",                       \
    "add", "sub", "mul", "div", "mod", "pow",	\
    "op", "and", "xor", "not",			\
    "eq", "lt", "gt", "lte", "gte", "cmp",	\
    "if", "jmp",				\
    "pushconst",				\
    "pushvar", "setvar", "valuevar",            \
    "print", "dumpstack"


#endif /* _OPCODES_H_ */
