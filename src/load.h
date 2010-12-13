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

#ifndef _LOAD_H_
#define _LOAD_H_

#include "atto.h"
#include "vec.h"
#include "block.h"
#include "vm.h"

struct LoadState;
/*
 * Parameters:
 * S - LoadState
 * b - where to read the bytes
 * size - number of bytes to be read
 * returns: bytes read
 */
typedef int (*Reader)(struct LoadState* S, unsigned char *b, size_t size);

typedef struct {
  char*    source;
  Vector*  k;
  Vector*  code;  
} Proto;

typedef struct LoadState {
  AttoVM*      vm;
  AttoBlock*   block;
  Reader       reader;
  char*        name;
  FILE*        fp;
} LoadState;

Proto*     AttoLoad(AttoVM*, AttoBlock*, Reader, char*, FILE*);
void       ProtoDestroy(Proto* p);
AttoBlock* Proto_to_block(AttoVM*, Proto*);

#endif /* _LOAD_H_ */
