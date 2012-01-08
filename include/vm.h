#ifndef _VM_H_
#define _VM_H_

#include "block.h"

typedef struct {
    unsigned just_putting_this_here_so_compiler_doesnt_complain_about_an_empty_struct_kthnx;
    // constants, functions, etc. go here
} AttoVM;

AttoVM *AttoVMNew();
void    AttoVMDestroy(AttoVM*);
TValue  vm_interpret(AttoVM*, AttoBlock*, int, int);
#endif /* _VM_H_ */
