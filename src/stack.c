#include "stack.h"

#include <stdio.h>

Stack *StackNew() {
  Stack* s = malloc(sizeof(Stack));
  s->top = 0;
  return s;
}

void StackDestroy(Stack* s) {
  UNUSED(s);
  // nothing to do as long as s->values is statically allocated
}

void push(Stack* s, TValue v) {
  if(s->top >= MAX_STACK_SIZE) {
    puts("Stack full.");
    return;
  }
  s->values[s->top++] = v;
}

TValue pop(Stack* s) {
  return s->values[--s->top];
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
    // TODO: string print
    printf("[%d]\t=>\t%Lf\n", i, NVALUE(s->values[i]));
  }
}
