#ifndef _OPCODES_H_
#define _OPCODES_H_

/* atto opcodes */
typedef enum {
    OP_NOP,

    /* basic stack ops */
    OP_POP,
    OP_DUP,
    OP_SWAP,

    /* math ops */
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_POW,

    /* bitwise ops */
    OP_OR,
    OP_AND,
    OP_XOR,
    OP_NOT,

    /* comparison ops */
    OP_EQ,
    OP_LT,        // push true if top - 1 < top, false otherwise
    OP_GT,        // push true if top -1 > top, false otherwise
    OP_LTE,
    OP_GTE,
    OP_CMP,       // push -1 if top -1 < top, 0 if equal, 1 otherwise

    /* flow of control ops */
    OP_IF,        // if [stack], exec next inst, otherwise skip
    OP_JMP,       // pc += [stack]

    /* const ops */
    OP_PUSHCONST, // push const[++pc] on to stack

    /* var ops */
    OP_PUSHVAR,   // push var[++pc] on to stack
    OP_SETVAR,    // var at [stack] = [stack]
    OP_VALUEVAR,  // push value of var on top of stack onto stack

    /* bool ops */
    OP_BOOLVALUE, // if boolValue[stack], push true, else false

    /* string ops */
    OP_CONCAT,    //  push a new string made of (SECOND) + (TOP)

    /* IO */
    OP_PRINT,
    OP_READLINE,  // read from keyboard, push string to stack

    /* stack ops */
    OP_DUMPSTACK,
    OP_CLEARSTACK,

    /* function ops */
    OP_CALL,     // calls a function located on top of the stack, popping top - 1
    // values onto its argument stack
    OP_RETURN,   // return the top of the stack to the calling function.

    NUM_OPS        /* how many opcodes are there? */

} AttoOpCodes;

#define OPCODE_NAMES "nop",			\
    "pop", "dup", "swap",                       \
    "add", "sub", "mul", "div", "mod", "pow",	\
    "op", "and", "xor", "not",			\
    "eq", "lt", "gt", "lte", "gte", "cmp",	\
    "if", "jmp",				\
    "pushconst",				\
    "pushvar", "setvar", "valuevar",            \
    "boolvalue",                                \
    "concat",                                   \
    "print", "readline",                        \
    "dumpstack", "clearstack",                  \
    "call", "return"

#endif /* _OPCODES_H_ */
