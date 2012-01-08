#include <stdio.h>
#include <stdlib.h>

#include "opcodes.h"
#include "atto.h"
#include "vec.h"
#include "block.h"
#include "vm.h"
#include "value.h"
#include "load.h"
#include "dump.h"

static int reader(LoadState* S, unsigned char* b, size_t size)
{
    size_t i;
    for (i = 0; i < size; ++i) {
        int c = fgetc(S->fp);
        b[i] = c;
    }
    return i;
}

static int usage(void)
{
    fprintf(stderr, "Usage:\natto [options] file\n"
            "-v\tDisplay version and exit\n"
            "-h\tDisplay this help text\n");
    return 1;
}

int main(int argc, char **argv)
{

    int i;
    char* file = NULL;
    for(i = 1; i < argc; ++i) {
        char *arg = argv[i];
        if(arg[0] == '-') {
            switch(arg[1]) {
            case 'v':
                printf("atto v%d.%d\n", VERSION_MAJOR, VERSION_MINOR);
                return 0;
            case 'h':
                usage();
                return 0;
            default:
                fprintf(stderr, "Unrecognized switch -%c\n", arg[1]);
                return usage();
            }
        } else {
            if(file != NULL) {
                return usage();
            }
            file = arg;
        }
    }

    if(file == NULL) {
        fprintf(stderr, "no file given\n");
        return usage();
    }

    FILE* in = fopen(file, "rb");
    if(in == NULL) {
        fprintf(stderr, "%s: no such file\n", file);
        return 1;
    }

    AttoVM* vm = AttoVMNew();

    Proto* p = AttoLoad(vm, reader, file, in );
    AttoBlock* b = Proto_to_block(vm, p);

    ProtoDestroy(p);

    TValue ret = vm_interpret(vm, b, 0, 0);

    int status;

    if(ret.type == TYPE_ERROR) {
        status = EXIT_FAILURE;
    } else {
        status = EXIT_SUCCESS;
    }

    AttoVMDestroy(vm);
    AttoBlockDestroy(b);

    fclose(in);

    return status;
}


/*
 * For creating test files without painfully messing with
 * a hex editor
 *
static int writer(AttoVM* vm, const void *p, size_t s, void *d) {
  UNUSED(vm);
  return (fwrite(p, s, 1, (FILE*)d) != 1) && (s != 0);
}


// in main
  AttoVM* vm = AttoVMNew();
  AttoBlock* b = AttoBlockNew();

  AttoBlock_push_const(b, createNumber(2));
  AttoBlock_push_const(b, createNumber(3));

  AttoBlock_push_inst(b, OP_PUSHCONST);
  AttoBlock_push_inst(b, 0);

  AttoBlock_push_inst(b, OP_PUSHCONST);
  AttoBlock_push_inst(b, 1);

  AttoBlock_push_inst(b, OP_ADD);

  AttoBlock_push_inst(b, OP_PRINT);

  Proto* p = Proto_from_block(vm, b);
  FILE* fp = fopen("test.ato", "wb");
  dump(vm, p, writer, fp);
*/
