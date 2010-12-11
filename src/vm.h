#ifndef _VM_H_
#define _VM_H_

typedef struct {
  // constants, functions, etc. go here
} AttoVM;

AttoVM *AttoVMNew();
void    AttoVMDestroy(AttoVM*);

#endif /* _VM_H_ */
