#include <string.h>

#include "load.h"
#include "dump.h"

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

static TValue LoadString(LoadState* S) {
  int i;
  int length = LoadInt(S);
  char* ptr = malloc(length + 1);
  for(i = 0; i <= length; ++i) {
    ptr[i] = LoadChar(S);
  }

  return createString(ptr, length, 1);
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
    AttoNumber inst = LoadNumber(S);
    append(f->code, createNumber(inst));
  }
}

static TValue LoadFunction(LoadState* S) {
  int size = LoadInt(S);
  AttoBlock* b = AttoBlockNew();
  int i;
  for(i = 0; i < size; ++i) {
    AttoNumber inst = LoadNumber(S);
    AttoBlock_push_inst(b, inst);
  }

  return createFunction(b);
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
      obj = LoadString(S);
      break;
    case TYPE_BOOL:
      obj = createBool(LoadChar(S));
      break;
    case TYPE_FUNCTION:
      obj = LoadFunction(S);
      break;
    default:
      printf("Unknown type: %d\n", type);
      error(S, "Unknown type");
      break;
    }
    append(f->k, obj);
  }
}

static void LoadVars(LoadState *S, Proto *p) {
  p->sizev = LoadInt(S);
}

static void LoadHeader(LoadState* S) {
  char *h_ = malloc(HEADER_SIZE);
  char *s_ = malloc(HEADER_SIZE);
  char *h = h_;
  char *s = s_;
  createHeader(h);
  LoadBlock(S, s, HEADER_SIZE);

  int diff = memcmp(h, s, HEADER_SIZE);

  if(diff) {
    fprintf(stderr, "ERROR: Bad header: ");
    IF(memcmp(h, s, sizeof(BYTECODE_SIGNATURE)), "wrong file signature (not Atto file?)");
    h += sizeof(BYTECODE_SIGNATURE);
    s += sizeof(BYTECODE_SIGNATURE);
    
    if(*h != *s) {
      fprintf(stderr, "wrong version, got %X, expected %X\n", *s, *h);
      error(S, "error");
    }

    s += 1;
    h += 1;

    if(*h != *s) {
      fprintf(stderr, "wrong endianness, got %d, expected %d\n", *s, *h);
      error(S, "error");
    }

    error(S, "bad header. different achitecture, or version mismatch");
  }

  free(s_);
  free(h_);

}

static Proto* LoadProto(LoadState* S) {
  Proto* p = malloc(sizeof(Proto));
  p->source = S->name;
  LoadConstants(S, p);
  LoadVars(S, p);
  LoadCode(S, p);
  return p;
}

Proto* AttoLoad(AttoVM* vm, Reader r, char* name, FILE* fp) {
  DEBUGF("Loading file: %s\n", name);
  LoadState s;
  s.vm = vm;
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
  AttoBlock* b = AttoBlockNew();
  unsigned i;
  for(i = 0; i < p->k->size; ++i) {
    append(b->k, getIndex(p->k, i));
  }
  for(i = 0; i < p->code->size; ++i) {
    append(b->code, getIndex(p->code, i));
  }
  b->sizev = p->sizev;
  
  DEBUGF("Vars: %d\n", p->sizev);

  if(p->sizev > 0 ) {
    TValue null = createNull();
    b->vars = malloc(sizeof(TValue) * p->sizev);
    
    int i;
    for( i = 0; i < p->sizev; ++i) {
      b->vars[i] = createVar(&null);
    }
  } else {
    b->vars = NULL;
  }

  return b;
}
