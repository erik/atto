#include <math.h>
#include <string.h>

#include "value.h"

TValue createError(char* msg) {
  TValue tv;
  Value v;
  v.error = msg;
  tv.value = v;
  return tv;
}

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
  Value v;
  v.error = "NULL";
  tv.value = v;
  return tv;
}

TValue createVar(TValue *tvalue) {
  TValue tv;
  Value v;
  tv.type = TYPE_VAR;
  v.var.value = &tvalue->value;
  v.var.type  = tvalue->type;
  tv.value = v;
  return tv;
}

TValue createString(char* ptr, int len, int con) {
  TValue tv;
  tv.type = TYPE_STRING;
  AttoString as;
  as.ptr = calloc(len + 1, sizeof(char));
  memcpy(as.ptr, ptr, len);
  as.len = len;
  as.constant = con;
  Value v;
  v.string = as;
  tv.value = v;
  return tv;
}

TValue createBool(char val) {
  TValue tv;
  tv.type = TYPE_BOOL;
  Value v;
  v.bool = val;
  tv.value = v;
  return tv;
}

void valueDestroy(TValue* v) {
  valueDestroy2(v, 0);
}

void valueDestroy2(TValue* v, int delConst) {
  if(v->type == TYPE_STRING && (!v->value.string.constant || delConst)) {
    free(v->value.string.ptr);
    v->value.string.ptr = NULL;
  }
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

  // TODO: push Bools instead of Numbers
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
  case TYPE_VAR: {
    char* ret = malloc(20);
    sprintf(ret, "Var@%p", (void*)&v.value.var);
    return ret;
  }
  case TYPE_STRING:
    return TV2STR(v);
  case TYPE_NULL:
    return "NULL";
  case TYPE_ERROR:
    return v.value.error;
  case TYPE_BOOL:
    return v.value.bool ? "TRUE" : "FALSE";
  }   
  return "Unknown type";  
}

char* TValue_type_to_string(TValue v) {
  char *ret;
  switch(v.type) {
  case TYPE_ERROR:
    ret = "error";
    break;
  case TYPE_NULL:
    ret = "null";
    break;
  case TYPE_NUMBER:
    ret = "number";
    break;
  case TYPE_STRING:
    ret = "string";
    break;
  case TYPE_VAR:
    ret = "var";
    break;
  case TYPE_BOOL:
    ret = "bool";
    break;
  default:
    ret = "(UNKNOWN)";
    break;
  }
  return ret;
}


int boolValue(TValue t) {
  switch(t.type) {
  case TYPE_ERROR:
  case TYPE_NULL:
    return 0;
  case TYPE_VAR:
  case TYPE_STRING:
  case TYPE_NUMBER:
    return 1;
  case TYPE_BOOL:
    return t.value.bool;
  }
  return 0;
}
