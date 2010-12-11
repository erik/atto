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

void resizeVector(Vector* v, int size) {
  v->alloc = size;
  TValue *resized = realloc(v->elements, size * sizeof(TValue));
  
  int i;
  for(i = 0; i < size; ++i) {
    if (i < v->size) {
      resized[i] = v->elements[i];
    }
  }
  v->elements = resized;
}

void setIndex(Vector *vec, int idx, TValue val) {
  if(idx >= vec->alloc) {
    resizeVector(vec, vec->alloc + (idx - vec->alloc) + VECTOR_RESIZE_STEP);
  }
  vec->elements[vec->size++] = val;
}

int append(Vector *vec, TValue val) {
  setIndex(vec, vec->size, val);
  return vec->size;
}
