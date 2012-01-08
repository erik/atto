#include "stack.h"
#include "value.h"

#include <string.h>
#include <stdio.h>

Stack StackNew()
{
    Stack s;
    memset(s.values, sizeof(TValue), MAX_STACK_SIZE);
    s.top = 0;
    return s;
}

void StackDestroy(Stack* s)
{
    s->top = 0;
    memset(s->values, sizeof(TValue), MAX_STACK_SIZE);
}

Stack Stack_from_array(int argc, TValue* argv)
{
    Stack s = StackNew();
    int i;
    for(i = 0; i < argc; ++i) {
        push(&s, argv[i]);
    }
    return s;
}

void push(Stack* s, TValue v)
{
    if(s->top >= MAX_STACK_SIZE) {
        puts("Stack full.");
        return;
    }
    s->values[s->top] = v;
    ++s->top;
}

TValue pop(Stack* s)
{
    if(--s->top < 0) {
        puts("Stack empty.");
        return createNull();
    }
    return s->values[s->top];
}

int filled(Stack* s)
{
    return s->top >= MAX_STACK_SIZE;
}

void print_stack(Stack s)
{
    if(s.top == 0) {
        puts("Stack is empty.");
        return;
    }

    printf("Stack at %p:\n", (void*)&s);
    int i;
    for(i = 0; i < s.top; ++i) {
        TValue v = s.values[i];
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
