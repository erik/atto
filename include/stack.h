#ifndef _STACK_H_
#define _STACK_H_

#include "atto.h"

#define MAX_STACK_SIZE 250

typedef struct {
  TValue values[MAX_STACK_SIZE];
  int top;
} Stack;

Stack StackNew();
void StackDestroy(Stack*);

Stack Stack_from_array(int, TValue*);

void push(Stack*, TValue);
TValue pop(Stack*);
int filled(Stack*);
void print_stack(Stack);

#endif /* _STACK_H_ */
