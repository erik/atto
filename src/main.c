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

int main(void) {
  AttoVM* vm = AttoVMNew();
  
  AttoBlock* b = AttoBlockNew();
  push(b->stack,  createNumber(10));
  push(b->stack,  createNumber(2));
  Instruction inst = OP_SWAP;
  AttoBlock_push_inst(b, inst);

  vm_interpret(vm, b, 0, 0, NULL);
  print_stack(b->stack);
  return 0;
}
