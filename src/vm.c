#include "opcodes.h"
#include "atto.h"
#include "vm.h"

AttoVM *AttoVMNew() {
  AttoVM* vm = malloc(sizeof(AttoVM));
  return vm;
}

void AttoVMDestroy(AttoVM* vm) {
  free(vm);
}

TValue atto_interpret(AttoVM* vm) {
}
