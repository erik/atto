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

#include "dump.h"

#include <string.h>

#define DumpMem(b, n, size, D)   DumpBlock(b, (n) * (size), D)
#define DumpVar(v, D)            DumpMem(&v, 1, sizeof(v), D)

void DumpBlock(const void *blk, size_t size, DumpState *D) {
  D->status = (*D->writer)(D->vm, blk, size, D->data);
}

void DumpChar(char x, DumpState *d) {
  DumpVar(x, d);
}

void DumpInt(int x, DumpState *d) {
  DumpVar(x, d);
}

void DumpString(AttoString s, DumpState *d) {
  char* str = s.ptr;
  int i;
  int len = strlen(str);
  DumpInt(len, d);
  for(i = 0; i <= len; ++i) {
    DumpChar(str[i], d);
  }
}

void createHeader(char* h) {
  int x = 1;
  memcpy(h, BYTECODE_SIGNATURE, sizeof(BYTECODE_SIGNATURE));
  h    += sizeof(BYTECODE_SIGNATURE);
  *h++ = (char)VERSION;
  *h++ = (char)*(char*)&x; // endianness
}

void DumpHeader(DumpState *d) {
  char h[HEADER_SIZE];
  createHeader(h);
  DumpBlock(h, HEADER_SIZE, d);
}

void DumpVector(Vector *vec, size_t s, DumpState *d) {
  DumpInt(vec->size, d);
  int i;
  for(i = 0; i < vec->size; ++i) {
    TValue v = getIndex(vec, i);
    switch(v.type) {
    case TYPE_NUMBER: {
      AttoNumber n = TV2NUM(v);
      DumpMem((void*)&n, 1, s, d);
      break;
    }
    case TYPE_STRING: {
      AttoString str = v.value.string;
      DumpString(str, d);
      break;
    }
    default:
      puts("Unrecognized type!");
      return;
    }
  }
}

void DumpConstants(Proto *p, DumpState *d) {
  int sizek = p->k->size;
  DumpInt(sizek, d);

  int i;
  for(i = 0; i < sizek; ++i) {
    TValue v = getIndex(p->k, i);
    
    DumpChar(v.type, d);

    switch(v.type) {
    case TYPE_NULL:
      break;
    case TYPE_NUMBER:
      DumpVar(TV2NUM(v), d);
      break;
    case TYPE_STRING:
      DumpString(v.value.string, d);
      break;
    default:
      fprintf(stderr, "Unknown type: %d\n", v.type);
      break;
    }    
  }
}

void DumpVars(Proto *p, DumpState *d) {
  int sizev = p->sizev;
  DumpInt(sizev, d);
}

void DumpCode(Proto* p, DumpState *d) {
  int sizecode = p->code->size;
  DumpInt(sizecode, d);
  
  int i;
  for(i = 0; i < sizecode; ++i) {
    AttoNumber inst = TV2NUM(getIndex(p->code, i));
    DumpVar(inst, d);
  }
}


Proto* Proto_from_block(AttoVM* vm, AttoBlock *b) {
  UNUSED(vm);
  Proto* p = malloc(sizeof(Proto));
  p->source = "lOl";
  p->k = b->k;
  p->code = b->code;
  p->sizev = b->sizev;
  return p;
}

int dump(AttoVM* vm, Proto* p, Writer writer, void *data) {
  DumpState d;
  d.vm = vm;
  d.writer = writer;
  d.data = data;
  d.status = 0;
  DumpHeader(&d);
  DumpConstants(p, &d);
  DumpVars(p, &d);
  DumpCode(p, &d);
  return d.status;
}
