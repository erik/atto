#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "atto.h"
#include "vec.h"
#include "stack.h"
#include "value.h"

typedef struct AttoBlock {
    Vector* k;     /* constants */
    int sizev;
    TValue *vars;
    Vector* code;  /* opcodes */
    Stack stack;
} AttoBlock;

AttoBlock  *AttoBlockNew();
void        AttoBlockDestroy(AttoBlock*);
int         AttoBlock_push_inst(AttoBlock*, Instruction);
Instruction AttoBlock_fetch_inst(AttoBlock*, unsigned);
int         AttoBlock_push_const(AttoBlock*, TValue);
TValue      AttoBlock_fetch_const(AttoBlock*, unsigned);

#endif /* _BLOCK_H_ */
