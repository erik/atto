/* simple dynamically resizing array */

#include "vec.h"

Vector *VectorNew() {
  Vector *v = malloc(sizeof(Vector));
  v->elements = malloc(sizeof(TValue) * INITIAL_VECTOR_SIZE);
  v->size = 0;
  v->alloc = INITIAL_VECTOR_SIZE;
  return v;
}

void VectorDestroy(Vector* v) {
  free(v->elements);
  free(v);
}

void VectorDestroy2(Vector* v, int delConsts) {
  unsigned i;
  for(i = 0; i < v->size; ++i) {
    valueDestroy2(&v->elements[i], 1);
  }
  VectorDestroy(v);
}

void resizeVector(Vector* v, unsigned size) {
  v->alloc = size + 1;
  v->elements = realloc(v->elements, (size + 1) * sizeof(TValue));
}

void setIndex(Vector *vec, unsigned idx, TValue val) {
  if(idx >= vec->alloc) {
    resizeVector(vec, vec->alloc + (idx - vec->alloc) + VECTOR_RESIZE_STEP);
  }
  vec->elements[vec->size++] = val;
}

TValue getIndex(Vector *vec, unsigned idx) {
  if(idx >= vec->size) {
    return createNull("getIndex: array index out of bounds");
  }
  
  return vec->elements[idx];  
}

unsigned append(Vector *vec, TValue val) {
  setIndex(vec, vec->size, val);
  return vec->size;
}
