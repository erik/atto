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

#ifndef _DUMP_H_
#define _DUMP_H_

#include "atto.h"
#include "load.h"
#include "vm.h"

/*
 * Parameters:
 * vm - may be unused, various uses
 * p - what to write
 * s - how much to write
 * d - FILE* (or something else)
 */
typedef int (*Writer)(AttoVM *vm, const void *p, size_t s, void* d);

typedef struct {
  AttoVM* vm;
  Writer writer;
  void *data;
  int status;
} DumpState;

Proto *Proto_from_block(AttoVM*, AttoBlock*);
int    dump(AttoVM*, Proto*, Writer, void*);
void   createHeader(char*);

#endif /* _DUMP_H_ */
