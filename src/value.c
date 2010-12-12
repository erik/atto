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

#include <math.h>

#include "value.h"

TValue createNumber(AttoNumber n) {
  TValue tv;
  tv.type = TYPE_NUMBER;
  Value v;
  v.number = n;
  tv.value = v;
  return tv;
}

TValue createNull() {
  TValue tv;
  tv.type = TYPE_NULL;
  return tv;
}

TValue MathOp(int opcode, Stack* stack) {
  TValue b = pop(stack); 
  TValue a = pop(stack); 
  
  AttoNumber arg0 = TV2NUM(a);
  AttoNumber arg1 = TV2NUM(b);

  AttoNumber result = 1337;

  switch(opcode) {
  case OP_ADD:
    result = arg0 + arg1;
    break;
  case OP_SUB:
    result = arg0 - arg1;
    break;
  case OP_MUL:
    result = arg0 * arg1;
    break;
  case OP_DIV:
    if(arg1 == 0) {
      puts("Error: divide by 0.");
      return createNull();
    }
    result = arg0 / arg1;
    break;
  case OP_MOD:
    if(arg1 == 0) {
      puts("Error: divide by 0.");
      return createNull();
    }
    result = (long)arg0 % (long)arg1;
    break;
  case OP_POW:
    result = pow(arg0, arg1);
    break;
  default:
    puts("Unrecognized opcode");
    return createNull();
  }
  a = createNumber(result);
  push(stack, a);
  return a;
}

TValue BitwiseOp(int opcode, Stack* stack) {
  TValue b = pop(stack); 
  TValue a = pop(stack); 
  
  long arg0 = (long)TV2NUM(a);
  long arg1 = (long)TV2NUM(b);

  AttoNumber result = 1337;

  switch(opcode) {
  case OP_OR:
    result = arg0 | arg1;
    break;
  case OP_AND:
    result = arg0 & arg1;
    break;
  case OP_XOR:
    result = arg0 ^ arg1;
    break;
  default:
    puts("Unrecognized opcode");
    return createNull();
  }
  a = createNumber(result);
  push(stack, a);
  return a;
}

TValue ComparisonOp(int opcode, Stack* stack) {
  TValue b = pop(stack); 
  TValue a = pop(stack); 
  
  AttoNumber arg0 = TV2NUM(a);
  AttoNumber arg1 = TV2NUM(b);

  AttoNumber result = 0;

  switch(opcode) {
  case OP_EQ:
    result = arg0 == arg1 ? 1 : 0;
    break;
  case OP_LT:
    result = arg0 < arg1 ? 1 : 0;
    break;
  case OP_GT:
    result = arg0 > arg1 ? 1 : 0;
    break;
  case OP_LTE:
    result = arg0 <= arg1 ? 1 : 0;
    break;
  case OP_GTE:
    result = arg0 >= arg1 ? 1 : 0;
    break;
  case OP_CMP:
    result = arg0 == arg1 ? 0 : arg0 >= arg1 ? 1 : -1;
    break;
  default:
    puts("Unrecognized opcode.");
    return createNull();
  }

  a = createNumber(result);
  push(stack, a);
  return a;
}

char* TValue_to_string(TValue v) {
  switch(v.type) {
  case TYPE_NUMBER: {
    char* ret = malloc(20);
    sprintf(ret, "%Lf", TV2NUM(v));
    return ret;
  }
  case TYPE_STRING:
    return TV2STR(v);
  case TYPE_NULL:
    return "NULL";
  }   
  return "Unknown type";  
}
