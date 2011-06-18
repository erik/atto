// a test program that runs a unit test of the virtual machine

#if UNIT_TEST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "vm.h"
#include "block.h"
#include "opcodes.h"
#include "atto.h"
#include "value.h"

#define INIT_TEST_OBJ                           \
  AttoVM* vm = AttoVMNew();                     \
  AttoBlock* b = AttoBlockNew()

#define DEINIT_TEST_OBJ                         \
  AttoVMDestroy(vm);                            \
  AttoBlockDestroy(b)

#define RESET_TEST_OBJ                          \
  DEINIT_TEST_OBJ;                              \
  vm = AttoVMNew();                             \
  b = AttoBlockNew()                           

#define PASS                                    \
  DEINIT_TEST_OBJ;                              \
  return 0

#define FAIL                                    \
  DEINIT_TEST_OBJ;                              \
  return 1

#define ADD_OP(op)                              \
  AttoBlock_push_inst(b, OP_##op)

#define INTERP {                                \
    TValue res = vm_interpret(vm, b, 0, 0); \
    if(res.type == TYPE_ERROR) {                \
      printf("\tError: %s", res.value.error);   \
      FAIL;                                     \
    }                                           \
  }

#define ASSERT(expr) if(!(expr)) {              \
    puts("ASSERT failed: '" #expr "'");         \
    FAIL;                                       \
}

#define TEST(name, desc) {                           \
    puts("Testing: " desc);                          \
    if(test_##name()) {                              \
      puts("\tfailed!");                             \
    } else {                                         \
      puts("\tpassed!");                             \
    }                                                \
  }

// ...
int test_nop() {
  INIT_TEST_OBJ;

  ADD_OP(NOP);

  INTERP;

  PASS;
}

int test_stack() {
  INIT_TEST_OBJ;

  push(&b->stack, createBool(0));
  push(&b->stack, createNumber(1));
  push(&b->stack, createNull());

  ADD_OP(POP);
  ADD_OP(SWAP);
  ADD_OP(DUP);

  INTERP;

  ASSERT(b->stack.top == 3);
  ASSERT(b->stack.values[b->stack.top - 1].type == TYPE_BOOL);
  ASSERT(b->stack.values[b->stack.top - 2].type == TYPE_BOOL);
  ASSERT(b->stack.values[b->stack.top - 3].type == TYPE_NUMBER);

  PASS;
}

int test_math() {
  INIT_TEST_OBJ;

  /** Set 1 **/
  // 16 4 11 4 5 + - * /
  // 16 / (4 * (11 - (4 + 5))) => 8
  push(&b->stack, createNumber(16));
  push(&b->stack, createNumber(4));
  push(&b->stack, createNumber(11));
  push(&b->stack, createNumber(4));
  push(&b->stack, createNumber(5));

  ADD_OP(ADD);
  ADD_OP(SUB);
  ADD_OP(MUL);
  ADD_OP(DIV);

  INTERP;

  ASSERT(b->stack.top == 1);
  ASSERT(TV2NUM(b->stack.values[0]) == 2.0);

  RESET_TEST_OBJ;

  /** Set 2 **/
  // 14 3 2 ^ %
  // 14 % (3^2) => 5
  push(&b->stack, createNumber(14));
  push(&b->stack, createNumber(3));
  push(&b->stack, createNumber(2));

  ADD_OP(POW);
  ADD_OP(MOD);

  INTERP;
  
  ASSERT(b->stack.top == 1);
  ASSERT(TV2NUM(b->stack.values[0]) == 5.0);

  PASS;
}

int test_bitwise() {
  INIT_TEST_OBJ;

  // 0x0F0 0xF00 0x8F 0xF & | ^
  // ~(((0x8F & 0xF) | 0xF00) ^ 0x0F0) => ~0xFFF (-0x1000)
  push(&b->stack, createNumber(0x0F0));
  push(&b->stack, createNumber(0xF00));
  push(&b->stack, createNumber(0x8F));
  push(&b->stack, createNumber(0xF));

  ADD_OP(AND);
  ADD_OP(OR);
  ADD_OP(XOR);
  ADD_OP(NOT);

  INTERP;

  ASSERT(b->stack.top == 1);
  ASSERT(TV2NUM(b->stack.values[0]) == ~0xFFF);

  PASS;
}

int test_comparison() {
  INIT_TEST_OBJ;

  push(&b->stack, createNumber(0));
  push(&b->stack, createNumber(1));
  ADD_OP(EQ);
  INTERP;
  ASSERT(b->stack.top == 1);
  ASSERT(b->stack.values[0].value.bool == 0);

  RESET_TEST_OBJ;

  push(&b->stack, createNumber(1456));
  push(&b->stack, createNumber(1456));
  ADD_OP(EQ);
  INTERP;
  ASSERT(b->stack.top == 1);
  ASSERT(b->stack.values[0].value.bool == 1);

  RESET_TEST_OBJ;

  // 0 10 < => true
  push(&b->stack, createNumber(0));
  push(&b->stack, createNumber(10));

  ADD_OP(LT);
  
  INTERP;

  ASSERT(b->stack.top == 1);
  ASSERT(b->stack.values[0].value.bool == 1);

  RESET_TEST_OBJ;

  // 0 10 > => false
  push(&b->stack, createNumber(0));
  push(&b->stack, createNumber(10));

  ADD_OP(GT);
  
  INTERP;

  ASSERT(b->stack.top == 1);
  ASSERT(b->stack.values[0].value.bool == 0);

  RESET_TEST_OBJ;

  push(&b->stack, createNumber(0));
  push(&b->stack, createNumber(1));

  ADD_OP(CMP);

  INTERP;

  ASSERT(b->stack.top == 1);
  ASSERT(TV2NUM(b->stack.values[0]) == -1.0);

  PASS;
}

int test_constants() {
  INIT_TEST_OBJ;

  AttoBlock_push_const(b, createString("0123", 4, 1));

  ADD_OP(PUSHCONST);
  AttoBlock_push_inst(b,0); // const index

  INTERP;

  ASSERT(b->stack.top == 1);
  ASSERT(b->stack.values[0].type == TYPE_STRING &&
         strcmp(b->stack.values[0].value.string.ptr, "0123") == 0);


  PASS;
}

int test_stack2() {
  INIT_TEST_OBJ;

  int i;
  for(i = 0; i < 100; ++i) {
    push(&b->stack, createNumber(i));
  }
  
  ASSERT(b->stack.top == 100);

  ADD_OP(CLEARSTACK);

  INTERP;
  
  ASSERT(b->stack.top == 0);
  
  PASS;    
}

int test_functions() {
  INIT_TEST_OBJ;

  AttoBlock* add = AttoBlockNew();
  AttoBlock_push_inst(add, OP_ADD);
  AttoBlock_push_inst(add, OP_RETURN);

  TValue tf = createFunction(add);

  push(&b->stack, createNumber(3));
  push(&b->stack, createNumber(2));

  push(&b->stack, createNumber(2));
  push(&b->stack, tf);

  ADD_OP(CALL);

  INTERP;
  
  ASSERT(b->stack.top == 1);
  ASSERT(TV2NUM(b->stack.values[0]) == 5);

  AttoBlockDestroy(add);

  PASS;
}


int main(int argc, char** argv) {

  TEST(nop,        "the ability of NOP to do nothing");
  TEST(stack,      "basic stack operations");
  TEST(math,       "mathematical operations");
  TEST(bitwise,    "bitwise operations");
  TEST(comparison, "comparison operations");
  TEST(constants,  "constants");
  TEST(stack2,     "other stack operations");
  TEST(functions,  "functions");

}

#endif /* UNIT_TEST */
