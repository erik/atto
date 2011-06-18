#ifndef _ATTO_H_
#define _ATTO_H_

#include "config.h"

typedef enum {
  TYPE_ERROR,
  TYPE_NULL,
  TYPE_NUMBER,
  TYPE_STRING,
  TYPE_VAR,
  TYPE_BOOL,
  TYPE_FUNCTION
} AttoType;

typedef struct {
  int constant; // if a constant, don't free it
  char *ptr;
  int len;
} AttoString;

#define STRPTR(as) (as).ptr
#define STRLEN(as) (as).len

struct AttoBlock;

typedef struct AttoFunction {
  // TODO: library funtions
  struct AttoBlock* b;  
} AttoFunction;

typedef ATTO_NUMBER AttoNumber;

union Value_t;

typedef struct Var {
  union Value_t* value;
  AttoType type;
  int index;
} Var;

typedef union Value_t {
  char *error;
  char bool;
  AttoNumber number;
  AttoString string;
  AttoFunction function;
  Var var;
} Value;

/* Tagged value*/
typedef struct {
  Value value;
  AttoType type;
} TValue;

#define TV2NUM(tv)   ((tv).value.number)
#define TV2INST(tv)  (Instruction)((tv).value.number)

#define TV2STR(tv)  STRPTR((tv).value.string)

#if defined DEBUG
#if !defined DEBUGF
#define DEBUGF(format, ...) fprintf(stderr, "DEBUG: " format, __VA_ARGS__)
#define DEBUGLN(msg) fprintf(stderr, "DEBUG: %s\n", msg)
#endif
#else
#define DEBUGF(...)
#define DEBUGLN(msg)
#endif


#endif /* _ATTO_H_ */
