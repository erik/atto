#ifndef _LOAD_H_
#define _LOAD_H_

#include "atto.h"
#include "vec.h"
#include "block.h"
#include "vm.h"

struct LoadState;
/*
 * Parameters:
 * S - LoadState
 * b - where to read the bytes
 * size - number of bytes to be read
 * returns: bytes read
 */
typedef int (*Reader)(struct LoadState* S, unsigned char *b, size_t size);

typedef struct {
    char*    source;
    Vector*  k;
    int      sizev;
    Vector*  code;
} Proto;

typedef struct LoadState {
    AttoVM*      vm;
    Reader       reader;
    char*        name;
    FILE*        fp;
} LoadState;

Proto*     AttoLoad(AttoVM*, Reader, char*, FILE*);
void       ProtoDestroy(Proto* p);
AttoBlock* Proto_to_block(AttoVM*, Proto*);

#endif /* _LOAD_H_ */
