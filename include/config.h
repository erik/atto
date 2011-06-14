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

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define UNUSED(x) ((void)(x))

#define ATTO_NUMBER long double

typedef uint32_t Instruction;

#define VERSION        0x10
#define VERSION_MAJOR  0x01
#define VERSION_MINOR  0x00
#define BYTECODE_SIGNATURE "\016ato"

#define HEADER_SIZE   7 /* VERSION + BYTECODE_SIGNATURE + endianness */

#endif /* _CONFIG_H_ */
