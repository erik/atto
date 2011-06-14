#ifndef _DUMP_H_
#define _DUMP_H_

#include "atto.h"
#include "load.h"
#include "vm.h"

/*
 * Parameters:
 * vm - may be unused, various uses
 * p - what to write
 * s - how much to write
 * d - FILE* (or something else)
 */
typedef int (*Writer)(AttoVM *vm, const void *p, size_t s, void* d);

typedef struct {
  AttoVM* vm;
  Writer writer;
  void *data;
  int status;
} DumpState;

Proto *Proto_from_block(AttoVM*, AttoBlock*);
int    dump(AttoVM*, Proto*, Writer, void*);
void   createHeader(char*);

#endif /* _DUMP_H_ */
