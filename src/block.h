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

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "atto.h"
#include "vec.h"
#include "stack.h"
#include "value.h"

typedef struct {
  Vector* k;     /* constants */
  int sizev;
  TValue *vars;
  Vector* code;  /* opcodes */
  Stack* stack;
} AttoBlock;

AttoBlock  *AttoBlockNew();
void        AttoBlockDestroy(AttoBlock*);
int         AttoBlock_push_inst(AttoBlock*, Instruction);
Instruction AttoBlock_fetch_inst(AttoBlock*, unsigned);
int         AttoBlock_push_const(AttoBlock*, TValue);
TValue      AttoBlock_fetch_const(AttoBlock*, unsigned);

#endif /* _BLOCK_H_ */
