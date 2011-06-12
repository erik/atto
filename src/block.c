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

#include "block.h"

AttoBlock *AttoBlockNew() {
  AttoBlock* b = malloc(sizeof(AttoBlock));
  b->k    = VectorNew();
  b->code = VectorNew();
  b->stack = StackNew();
  b->sizev = 0;
  b->vars = NULL;
  return b;
}

void AttoBlockDestroy(AttoBlock* b) {
  VectorDestroy(b->k);
  VectorDestroy(b->code);
  StackDestroy(b->stack);
  if(b->vars) {
    free(b->vars);
  }
  free(b);
}

int AttoBlock_push_inst(AttoBlock* b, Instruction inst) {
  Value v;
  v.number = inst;
  TValue tv;
  tv.type = TYPE_NUMBER;
  tv.value = v;
  append(b->code, tv);

  return b->code->size - 1;
}

Instruction AttoBlock_fetch_inst(AttoBlock* b, unsigned idx) {
  if(idx >= b->code->size) {
    puts("Error: trying to access instruction out of bounds");
    return -1;
  }
  
  return TV2INST(getIndex(b->code, idx));
}

int AttoBlock_push_const(AttoBlock* b, TValue v) {
  append(b->k, v);
  return b->k->size - 1;
}

TValue AttoBlock_fetch_const(AttoBlock* b, unsigned idx) {
  if(idx >= b->k->size) {
    puts("Error: trying to access constant out of bounds");
    return createNull();
  }
  return getIndex(b->k, idx);
}
