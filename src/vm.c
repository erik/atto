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

AttoVM *AttoVMNew() {
  AttoVM* vm = malloc(sizeof(AttoVM));
  return vm;
}

void AttoVMDestroy(AttoVM* vm) {
  free(vm);
}

#define EXPECT_ON_STACK(num) if(stack->top < num) { \
  printf("Expected at least %d elements"				\
	 " on the stack, but only %d found!\n",				\
	 num, stack->top );						\
  return *max;								\
  }

#define NEXTINST { i = TV2INST(*++pc_val); }
#define DISPATCH NEXTINST; break

TValue vm_interpret(AttoVM* vm, AttoBlock* block, int start, int argc, const TValue argv[]) {

  TValue* max     = (TValue*)(block->code->elements + start + block->code->size);
  TValue *pc_val       = (TValue*)(block->code->elements + start);
  Instruction i        = TV2INST(*pc_val);
  TValue *k            = (TValue*)block->k->elements;
  Stack *stack         = (Stack*)block->stack;

  int x;
  for(x = 0; pc_val < max; ++x) {
    printf("[%d]\t%d\n", x,i);
    switch(i) {
    case OP_NOP:
      DISPATCH;
    case OP_PUSH:
      //TODO:
      DISPATCH;
    case OP_POP:
      EXPECT_ON_STACK(1);
      pop(stack);
      DISPATCH;
    case OP_DUP:
      EXPECT_ON_STACK(1);
      TValue v = pop(stack);
      push(stack, v);
      push(stack, v);
      DISPATCH;      
    case OP_SWAP:
      EXPECT_ON_STACK(2);
      TValue f = pop(stack);
      TValue s = pop(stack);
      push(stack, f);
      push(stack, s);
      DISPATCH;
    }
  }

  return *max;
}
