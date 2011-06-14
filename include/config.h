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
