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

#include "opcodes.h"
#include "atto.h"
#include "vm.h"
#include "block.h"
#include "value.h"

AttoVM *AttoVMNew() {
  AttoVM* vm = malloc(sizeof(AttoVM));
  return vm;
}

void AttoVMDestroy(AttoVM* vm) {
  free(vm);
}

#define ERROR(msg, args...) {                                           \
  char err[1024];                                                       \
  sprintf(err, "ERROR: [%d] %s: " msg, x, op_name, ## args);            \
  fprintf(stderr, "%s\n", err);                                         \
  return createError(msg);                                              \
  }


#define EXPECT_ON_STACK(num) if(stack->top < num) {                     \
    ERROR("Expected at least %d elements"				\
          " on the stack, but only %d found!\n",                        \
          num, stack->top );						\
  }

#define NEXTINST { i = TV2INST(*++pc_val); }
#define DISPATCH NEXTINST; break

TValue vm_interpret(AttoVM* vm, AttoBlock* block, int start, int argc, Stack* argv) {
  DEBUGLN("Interpret block");
  int error            = 0;
  TValue* max          = (TValue*)(block->code->elements + start + block->code->size);
  TValue *pc_val       = (TValue*)(block->code->elements + start);
  Instruction i        = TV2INST(*pc_val);
  Stack *stack         = (Stack*)block->stack;
  const char* opcode_names[] = { OPCODE_NAMES };
  const char* op_name = NULL;

  int x;
  for(x = 0; pc_val < max && !error; ++x) {

    op_name = i >= NUM_OPS ? "unknown" : opcode_names[i];

    if(i >= NUM_OPS) {
      ERROR("bad opcode: %d", i);
    }

    DEBUGF("[%d]\t%s (%d)\n", x, op_name, i);
    switch(i) {
    case OP_NOP:
      DISPATCH;
    case OP_PUSH:
      // FIXME: This opcode should probably be removed
      DISPATCH;
    case OP_POP:
      EXPECT_ON_STACK(1);
      pop(stack);
      DISPATCH;
    case OP_DUP: {
      EXPECT_ON_STACK(1);
      TValue v = pop(stack);
      push(stack, v);
      push(stack, v);
      DISPATCH;   
    }   
    case OP_SWAP: {
      EXPECT_ON_STACK(2);
      TValue f = pop(stack);
      TValue s = pop(stack);
      push(stack, f);
      push(stack, s);
      DISPATCH;
    }
    case OP_ADD: case OP_SUB: case OP_MUL:
    case OP_DIV: case OP_MOD: case OP_POW:
      EXPECT_ON_STACK(2);
      MathOp(i, stack);
      DISPATCH;
    case OP_OR: case OP_AND: case OP_XOR:
      EXPECT_ON_STACK(2);
      BitwiseOp(i, stack);
      DISPATCH;
    case OP_NOT:
      EXPECT_ON_STACK(1);
      TValue a = pop(stack);
      push(stack, createNumber(~(long)TV2NUM(a)));
      DISPATCH;
    case OP_EQ: case OP_LT: case OP_GT:
    case OP_LTE: case OP_GTE: case OP_CMP:
      EXPECT_ON_STACK(2);
      ComparisonOp(i, stack);
      DISPATCH;
    case OP_IF: {
      EXPECT_ON_STACK(1);
      TValue t = pop(stack);
      if(!TV2NUM(t)) {
	NEXTINST;
      }
      DISPATCH;
    }
    case OP_JMP: {
      EXPECT_ON_STACK(1);
      long jmp = (long)TV2NUM(pop(stack));
      if(jmp + pc_val >= max || jmp + pc_val < 0) {
	ERROR("Invalid jump: %ld", jmp);
      }
      pc_val += jmp;
      DISPATCH;
    }
    case OP_PUSHCONST: {
      int index = TV2INST(*++pc_val);
      if(index >= block->k->size) {
	ERROR("Constant index out of bounds: %d", index);
      }
      TValue k = getIndex(block->k, index);
      push(stack, k);
      DISPATCH;
    }
    case OP_PUSHVAR: {
      int index = TV2INST(*++pc_val);
      
      if(index < 0 || index >= block->sizev) {
        ERROR("Variable index out of bounds: %d", index);
      }

      push(stack, block->vars[i]);
      DISPATCH;
    }
    case OP_SETVAR: {
      EXPECT_ON_STACK(1);
      int index = TV2INST(*++pc_val);
      
      if(index < 0 || index >= block->sizev) {
        ERROR("Variable index out of bounds: %d", index);
        return createNull();
      }

      TValue tos = pop(stack);

      block->vars[index] = tos;
      DISPATCH;
    }
    case OP_PRINT: {
      EXPECT_ON_STACK(1);
      TValue v = pop(stack);
      char *str = TValue_to_string(v);

      printf("%s", str);

      if(v.type == TYPE_NUMBER) free(str);
      DISPATCH;
    }
    case OP_DUMPSTACK:
      print_stack(stack);
      DISPATCH;
    default:
      ERROR("Unrecognized opcode.");
    }
  }

  DEBUGLN("Finished block");
  return createNull();
}
