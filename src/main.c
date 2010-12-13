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

#include <stdio.h>
#include <stdlib.h>

#include "opcodes.h"
#include "atto.h"
#include "vec.h"
#include "block.h"
#include "vm.h"
#include "value.h"
#include "load.h"

static int reader(LoadState* S, unsigned char* b, size_t size)
{
    size_t i;
    for (i = 0; i < size; ++i) {
        int c = fgetc(S->fp);
        b[i] = c;
    }
    return i;
}

static int usage(void)  {
  fprintf(stderr, "Usage:\natto [options] file\n"
	  "-v\tDisplay version and exit\n"
	  "-h\tDisplay this help text\n");
  return 1;
}

int main(int argc, char **argv) {
  
  int i;
  char* file = NULL;
  for(i = 1; i < argc; ++i) {
    char *arg = argv[i];
    if(arg[0] == '-') {
      switch(arg[1]) {
      case 'v':
	printf("atto v%d.%d\n", VERSION_MAJOR, VERSION_MINOR);
	return 0;
      case 'h':
	usage();
	return 0;
      default:
	fprintf(stderr, "Unrecognized switch -%c\n", arg[1]);
	return usage();
      }
    } else {
      if(file != NULL) {
	return usage();
      }
      file = arg;
    }
  }

  if(file == NULL) {
    fprintf(stderr, "no file given\n");
    return usage();
  }

  FILE* in = fopen(file, "rb");
  if(in == NULL) {
    fprintf(stderr, "%s: no such file\n", file);
    return 1;
  }

  // TODO: place argv values on stack
  Stack* argStack = StackNew();
  
  AttoVM* vm = AttoVMNew();
  AttoBlock* b = AttoBlockNew();
 
  Proto* p = AttoLoad(vm, b, reader, file, in );
  b = Proto_to_block(vm, p);
  
  vm_interpret(vm, b, 0, 0, argStack);
  AttoVMDestroy(vm);
  AttoBlockDestroy(b);
  StackDestroy(argStack);
  return 0;
}
