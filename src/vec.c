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

TValue getIndex(Vector *vec, int idx) {
  if(idx >= vec->size) {
    puts("Error: getIndex: array index out of bounds");
    //TODO: return null
    return;
  }
  
  return vec->elements[idx];  
}

int append(Vector *vec, TValue val) {
  setIndex(vec, vec->size, val);
  return vec->size;
}
