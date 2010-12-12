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
