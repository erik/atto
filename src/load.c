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

#include "load.h"

/* stolen from Bijou */
#define IF(c, s)     if (c) error(S, s);
#define UNLESS(c, s) IF(!(c), s)

static void error(LoadState* S, const char * msg)
{
  fprintf(stderr, "%s: %s in bytecode\n", S->name, msg);
  exit(EXIT_FAILURE);
}

#define LoadMem(S, b, n, size)     LoadBlock(S, b, (n) * (size))
#define LoadByte(S)                (unsigned char)LoadChar(S)
#define LoadVar(S, x)              LoadMem(S, &x, 1, sizeof(x))
#define LoadVector(S, b, n, size)  LoadMem(S, b, n, size)

static void LoadBlock(LoadState* S, void* b, size_t size)
{
  int s = (*S->reader)(S, b, size);
  IF(s == EOF, "Unexpected end of file");
}

static int LoadChar(LoadState* S) {
  char x;
  LoadVar(S, x);
  return x;
}

static int LoadInt(LoadState* S) {
  int x;
  LoadVar(S, x);
  return x;
}

static AttoNumber LoadNumber(LoadState* S) {
  AttoNumber x;
  LoadVar(S, x);
  return x;
}

static void LoadCode(LoadState* S, Proto* f) {
  int sizecode = LoadInt(S);
  DEBUGF("sizecode => %d\n", sizecode);
  f->code = VectorNew();
  int i;
  for(i = 0; i < sizecode; ++i) {
    Instruction x;
    x = LoadChar(S);
    append(f->code, createNumber(x));
  }
}

static void LoadConstants(LoadState* S, Proto* f) {
  int sizek = LoadInt(S);
  DEBUGF("sizek => %d\n", sizek);
  f->k = VectorNew();
  
  int i;
  for(i = 0; i < sizek; ++i) {
    TValue obj;
    int type = LoadChar(S);
    switch(type) {
    case TYPE_NULL:
      obj = createNull();
      break;
    case TYPE_NUMBER: {
      AttoNumber x = LoadNumber(S);
      obj = createNumber(x);
      break;
    }
    case TYPE_STRING:
      puts("TODO: String!");
      break;
    default:
      printf("Unknown type: %d\n", type);
      error(S, "Unknown type");
      break;
    }
    append(f->k, obj);
  }
}

static void LoadHeader(LoadState* S) {
  int bytecodeMin = LoadChar(S);
  int bytecodeMaj = LoadChar(S);
  IF(bytecodeMaj + bytecodeMin != VERSION, "Version mismatch");
}

static Proto* LoadProto(LoadState* S) {
  Proto* p = malloc(sizeof(Proto));
  p->source = S->name;
  LoadConstants(S, p);
  LoadCode(S, p);
  return p;
}

Proto* AttoLoad(AttoVM* vm, AttoBlock* b, Reader r, char* name, FILE* fp) {
  DEBUGF("Loading file: %s\n", name);
  LoadState s;
  s.vm = vm;
  s.block = b;
  s.reader = r;
  s.name = name;
  s.fp = fp;
  LoadHeader(&s);
  return LoadProto(&s);
}

void ProtoDestroy(Proto* p) {
  VectorDestroy(p->k);
  VectorDestroy(p->code);
  free(p);
}

AttoBlock* Proto_to_block(AttoVM* vm, Proto* p) {
  AttoBlock* b = AttoBlockNew(b);
  b->k = p->k;
  b->code = p->code;
  b->stack = StackNew();
  return b;
}
