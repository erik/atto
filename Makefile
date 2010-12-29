CC=clang
#DEBUG= -g -DDEBUG
OPTIMIZE=  -O3 -funroll-loops
CFLAGS:=  -Wall -Wextra -std=c99 -Wno-unused-parameter $(OPTIMIZE) $(DEBUG)
LNFLAGS= -lm
SRC = src/block.c src/dump.c src/load.c src/stack.c src/value.c src/vec.c src/vm.c  src/main.c
OBJ =$(SRC:.c=.o)
EXE=atto

AR=ar
ARFLAGS=cq
LIB=libatto.a
LIBOBJ=$(OBJ)

all: $(EXE) 

$(EXE): $(OBJ)
	@echo "link $(EXE)"
	@$(CC) $(OBJ) $(CFLAGS) $(LNFLAGS) -o$(EXE)

cleanlib:
	rm -f $(LIB)	

lib: cleanlib $(LIB)

$(LIB):  $(LIBOBJ)
	@echo "ar $@"
	@$(AR) $(ARFLAGS) $@ $(LIBOBJ)

clean: cleanlib
	rm -f $(OBJ) $(EXE)

src/block.o: src/block.c src/block.h src/atto.h src/config.h src/vec.h \
 src/value.h src/stack.h src/opcodes.h
src/dump.o: src/dump.c src/dump.h src/atto.h src/config.h src/load.h \
 src/vec.h src/value.h src/stack.h src/opcodes.h src/block.h src/vm.h
src/load.o: src/load.c src/load.h src/atto.h src/config.h src/vec.h \
 src/value.h src/stack.h src/opcodes.h src/block.h src/vm.h src/dump.h
src/main.o: src/main.c src/opcodes.h src/atto.h src/config.h src/vec.h \
 src/value.h src/stack.h src/block.h src/vm.h src/load.h src/dump.h
src/stack.o: src/stack.c src/stack.h src/atto.h src/config.h src/value.h \
 src/opcodes.h
src/value.o: src/value.c src/value.h src/atto.h src/config.h src/stack.h \
 src/opcodes.h
src/vec.o: src/vec.c src/vec.h src/atto.h src/config.h src/value.h \
 src/stack.h src/opcodes.h
src/vm.o: src/vm.c src/opcodes.h src/atto.h src/config.h src/vm.h src/block.h \
 src/vec.h src/value.h src/stack.h

.c.o:
	@echo "   cc $<"
	@${CC} -c ${CFLAGS} $< -o $@
todo:
	@find src -type f | xargs grep -n -i "TODO"
	@find src -type f | xargs grep -n -i "FIXME"

loc: 
	@wc -l src/*.[ch]

# requires sloccount
sloc:
	@sloccount src lib | grep '(SLOC)'


.PHONY= loc sloc todo clean
