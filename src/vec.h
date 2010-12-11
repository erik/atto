#ifndef _VEC_H_
#define _VEC_H_

#include "atto.h"

#define INITIAL_VECTOR_SIZE 10
#define VECTOR_RESIZE_STEP  5

typedef struct {
  TValue *elements;
  int size;
  int alloc;
} Vector;


Vector *VectorNew();
void    VectorDestroy(Vector*);
void    resizeVector(Vector*, int);
void    setIndex(Vector*, int, TValue);
int     append(Vector*, TValue);

#endif /* _VEC_H_ */
