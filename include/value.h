#ifndef _VALUE_H_
#define _VALUE_H_

#include "atto.h"
#include "stack.h"
#include "opcodes.h"

TValue createError(char*);
TValue createNumber(AttoNumber);
TValue createNull();
TValue createString(char*, int, int);
TValue createVar(TValue*);
TValue createBool(char);
TValue createFunction(struct AttoBlock* b);

void valueDestroy(TValue*);
void valueDestroy2(TValue*, int);

TValue MathOp(int, TValue, TValue);
TValue BitwiseOp(int, TValue, TValue);
TValue ComparisonOp(int, TValue, TValue);

char   *TValue_to_string(TValue);
char   *TValue_type_to_string(TValue);

int boolValue(TValue);
#endif /* _VALUE_H_ */
