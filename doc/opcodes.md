#Opcodes
This document gives an overview of the opcodes of the Atto VM. It is
valid as of Atto version 1.0. Anything later version may have some
changes.

Atto is a stack based virtual machine.

Complete opcode listing:

          OP_NOP,
          OP_POP,  
          OP_DUP,
          OP_SWAP,
          OP_ADD,
          OP_SUB,
          OP_MUL,
          OP_DIV,
          OP_MOD,
          OP_POW,
          OP_OR,
          OP_AND,
          OP_XOR,
          OP_NOT,
          OP_EQ,
          OP_LT,
          OP_GT,
          OP_LTE,
          OP_GTE,
          OP_CMP,
          OP_IF,
          OP_JMP,       
          OP_PUSHCONST, 
          OP_PUSHVAR,   
          OP_SETVAR,    
          OP_VALUEVAR,  
          OP_BOOLVALUE, 
          OP_CONCAT,    
          OP_PRINT,
          OP_READLINE,  
          OP_DUMPSTACK, 
          OP_CLEARSTACK, 
          OP_CALL,
          OP_RETURN

##Opcode Listing

####NOP
Nada.

###Stack ops
####POP
Pop top value off of the stack
####DUP
Push a copy of whatever the top value on the stack is onto the stack
####SWAP
Swap the top and second from top values on the stack

###Math ops
For each of the math ops, let a = second value on stack, and b = first
value on stack.
####ADD
push a + b
####SUB
push a - b
####MUL
push a * b
####DIV
push a / b (where b != 0)
####MOD
push a % b (where b != 0)
####POW
push a raised to b

###Bitwise ops
For each of the bitwise ops, let a = second value on stack, and b = first
value on stack.
####OR
push a | b
####AND
push a & b
####XOR
push a ^ b
####NOT
push ~b

###Comparison ops
For each of the bitwise ops, let a = second value on stack, b = first
value on stack
####EQ
push a == b
####LT
push a < b
####GT
push a > b
####LTE
push a <= b
####GTE
push a >= b
####CMP
If a == b, push 0, else if a > b push 1, else -1

###Flow of Control ops
####IF
If first value on stack is true, execute the next instruction,
otherwise skip it
####JMP
Program counter += top of stack

###Constant ops
####PUSHCONST
Index of constant to load is program counter++. (index is stored as an
opcode, but not executed). Constant at index is pushed to stack

###Var ops
####PUSHVAR
Index of var to load is program counter++. Var at index is pushed to
stack.
####SETVAR
Expects a var to be on top of stack. Sets its value to second from top
of stack. Both the var and the value it is set to are popped of the 
stack.
####VALUEVAR
Expects a var on top of stack. Pushes the value the var contains onto
the stack.

###Bool ops
####BOOLVALUE
Determines whether the top value on the stack evaluates to true or
false, and pushes the corresponding bool value.

###String ops
####CONCAT
Expects two strings to be on top of stack. Pushes a new string onto
stack made of (second on stack) + (top of stack).

###IO ops
####PRINT
Prints top of stack to screen
####READLINE
Reads a line of input from console, and puts it in a string on top of
stack. Limited to BUFSIZ chars (which is like 1024, so it should be
fine)

###Stack Ops
####DUMPSTACK
Prints the values of each element of the stack
####CLEARSTACK
Empties out the stack

###Function Ops
####CALL
Calls the function located on top of the stack. Expects a number to be
second from top on stack, which is the number of arguments to pass to
the given function.
####RETURN
Returns the top of the stack from a function to its calling function.
