CC=clang
CFLAGS=  -Wall -Wextra -std=c99 -g -Wno-unused-parameter
LNFLAGS= -lm
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)
EXE=atto

all: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LNFLAGS) -o$(EXE)
clean:
	rm -f $(OBJ) $(EXE)

src/block.o: src/block.c src/block.h src/atto.h src/config.h src/vec.h \
 src/stack.h
src/main.o: src/main.c src/opcodes.h src/atto.h src/config.h src/vec.h \
 src/block.h src/stack.h src/vm.h src/value.h
src/stack.o: src/stack.c src/stack.h src/atto.h src/config.h
src/value.o: src/value.c src/value.h src/atto.h src/config.h
src/vec.o: src/vec.c src/vec.h src/atto.h src/config.h
src/vm.o: src/vm.c src/opcodes.h src/atto.h src/config.h src/vm.h src/block.h \
 src/vec.h src/stack.h

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
