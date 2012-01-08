#ifndef _VEC_H_
#define _VEC_H_

#include "atto.h"
#include "value.h"

#define INITIAL_VECTOR_SIZE 10
#define VECTOR_RESIZE_STEP  5

typedef struct {
    TValue *elements;
    unsigned size;
    unsigned alloc;
} Vector;


Vector *VectorNew();
void    VectorDestroy(Vector*);
void    VectorDestroy2(Vector* v, int delConsts);
void    resizeVector(Vector*, unsigned);
void    setIndex(Vector*, unsigned, TValue);
TValue  getIndex(Vector*, unsigned);
unsigned     append(Vector*, TValue);

#endif /* _VEC_H_ */
