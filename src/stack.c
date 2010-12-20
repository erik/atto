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

#include "stack.h"
#include "value.h"

#include <stdio.h>

Stack *StackNew() {
  Stack* s = malloc(sizeof(Stack));
  s->top = 0;
  return s;
}

void StackDestroy(Stack* s) {
  free(s);
  // nothing to do as long as s->values is statically allocated
}

Stack *Stack_from_array(int argc, TValue* argv) {
  Stack* s = StackNew();
  int i;
  for(i = 0; i < argc; ++i) {
    push(s, argv[i]);
  }
  return s;
}

void push(Stack* s, TValue v) {
  if(s->top >= MAX_STACK_SIZE) {
    puts("Stack full.");
    return;
  }
  s->values[s->top++] = v;
}

TValue pop(Stack* s) {
  if(--s->top < 0) {
    puts("Stack empty.");
    return createNull();
  }
  return s->values[s->top];
}

int filled(Stack* s) {
  return s->top >= MAX_STACK_SIZE;
}

void print_stack(Stack* s) {
  if(s->top == 0) {
    puts("Stack is empty.");
    return;
  }

  printf("Stack at %p:\n", (void*)s);
  int i;
  for(i = 0; i < s->top; ++i) {
    TValue v = s->values[i];
    printf("[%d]\t=>\t", i);
    switch(v.type) {
    case TYPE_NULL:
      printf("NULL\n");
      break;
    case TYPE_NUMBER:
      printf("%Lf\n", TV2NUM(v));
      break;
    case TYPE_STRING:
      printf("\"%s\"\n", TV2STR(v));
      break;
    default:
      printf("Unknown type\n");
    }
  }
}
