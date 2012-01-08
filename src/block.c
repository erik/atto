#include "block.h"

AttoBlock *AttoBlockNew()
{
    AttoBlock* b = malloc(sizeof(AttoBlock));
    b->k    = VectorNew();
    b->code = VectorNew();
    b->stack = StackNew();
    b->sizev = 0;
    b->vars = NULL;
    return b;
}

void AttoBlockDestroy(AttoBlock* b)
{
    VectorDestroy2(b->k, 1);
    VectorDestroy(b->code);
    StackDestroy(&b->stack);
    if(b->vars) {
        int i;
        for(i = 0; i < b->sizev; ++i) {
            valueDestroy2(&b->vars[i], 1);
        }
        free(b->vars);
    }
    free(b);
}

int AttoBlock_push_inst(AttoBlock* b, Instruction inst)
{
    Value v;
    v.number = inst;
    TValue tv;
    tv.type = TYPE_NUMBER;
    tv.value = v;
    append(b->code, tv);

    return b->code->size - 1;
}

Instruction AttoBlock_fetch_inst(AttoBlock* b, unsigned idx)
{
    if(idx >= b->code->size) {
        puts("Error: trying to access instruction out of bounds");
        return -1;
    }

    return TV2INST(getIndex(b->code, idx));
}

int AttoBlock_push_const(AttoBlock* b, TValue v)
{
    append(b->k, v);
    return b->k->size - 1;
}

TValue AttoBlock_fetch_const(AttoBlock* b, unsigned idx)
{
    if(idx >= b->k->size) {
        puts("Error: trying to access constant out of bounds");
        return createNull();
    }
    return getIndex(b->k, idx);
}
