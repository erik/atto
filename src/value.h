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

#ifndef _VALUE_H_
#define _VALUE_H_

#include "atto.h"
#include "stack.h"
#include "opcodes.h"

TValue createError(char*);
TValue createNumber(AttoNumber);
TValue createNull();
TValue createString(char*, int);
TValue createVar(TValue*);
TValue createBool(char);

void valueDestroy(TValue*);

TValue MathOp(int, Stack*);
TValue BitwiseOp(int, Stack*);
TValue ComparisonOp(int, Stack*);

char   *TValue_to_string(TValue);
char   *TValue_type_to_string(TValue);

int boolValue(TValue);
#endif /* _VALUE_H_ */
