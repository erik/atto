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

#ifndef _VEC_H_
#define _VEC_H_

#include "atto.h"
#include "value.h"

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
TValue  getIndex(Vector*, int);
int     append(Vector*, TValue);

#endif /* _VEC_H_ */
