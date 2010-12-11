CC=clang
CFLAGS=  -Wall -Wextra -std=c99 -g
LNFLAGS= -lm
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)
EXE=atto

all: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LNFLAGS) -o$(EXE)
clean:
	rm -f $(OBJ) $(EXE)

src/main.o: src/main.c src/opcodes.h src/atto.h src/config.h
src/stack.o: src/stack.c src/stack.h src/atto.h src/config.h
src/vm.o: src/vm.c src/opcodes.h src/atto.h src/config.h

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
