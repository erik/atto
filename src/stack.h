
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

#ifndef _STACK_H_
#define _STACK_H_

#include "atto.h"

#define MAX_STACK_SIZE 250

typedef struct {
  TValue values[MAX_STACK_SIZE];
  int top;
} Stack;

Stack* StackNew();
void StackDestroy(Stack*);

Stack* Stack_from_array(int, TValue*);

void push(Stack*, TValue);
TValue pop(Stack*);
int filled(Stack*);
void print_stack(Stack*);

#endif /* _STACK_H_ */
