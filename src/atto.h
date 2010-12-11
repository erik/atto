#ifndef _ATTO_H_
#define _ATTO_H_

#include "config.h"

typedef enum {
  TYPE_NUMBER,
  TYPE_STRING,
  // TODO: maybe?
  TYPE_FUNCTION,
} AttoType;

typedef struct {
  char *ptr;
  int len;
} AttoString;

#define STRPTR(as) (as)->ptr
#define STRLEN(as) (as)->len

typedef ATTO_NUMBER AttoNumber;

typedef union {
  AttoNumber number;
  AttoString string;
  // TODO: function
} Value;

/* Tagged value*/
typedef struct {
  Value value;
  AttoType type;
} TValue;

#define NVALUE(tv)  (tv).value.number

#endif /* _ATTO_H_ */
