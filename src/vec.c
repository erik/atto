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
    puts("Error: getIndex: array index out of bounds");
    return createNull();
  }
  
  return vec->elements[idx];  
}

unsigned append(Vector *vec, TValue val) {
  setIndex(vec, vec->size, val);
  return vec->size;
}
