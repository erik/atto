CSRC := $(shell find src -name "*.c")
CHDR := $(shell find include -name "*.h")

COBJ := $(CSRC:.c=.o)

AR      := ar
ARFLAGS := cq
LIB     := libatto.a

CC := clang
CFLAGS := -Wall -Wextra -pedantic -std=c99 -Iinclude/ -Wno-unused-parameter -O2
LNFLAGS := -lm
EXE := atto

TESTSRC := $(shell find src/ \( -name "*.c" -and -not -name "main.c" \))
TESTOBJ := $(TESTSRC:.c=.o)
TESTEXE := tester

####

all: $(COBJ) $(EXE) lib

test: $(TESTOBJ)
	$(CC) $(CFLAGS) $(TESTOBJ) $(LNFLAGS) -g -O0 -DDEBUG -DUNIT_TEST src/tester.c -o $(TESTEXE)
	./tester

# creates the gmon.out files when ./atto or ./tester is run
gprof:
	gcc $(CFLAGS) $(CSRC) $(LNFLAGS) -pg -o $(EXE)
	gcc $(CFLAGS) $(TESTSRC) $(LNFLAGS) -pg -DUNIT_TEST -o $(TESTEXE)

$(EXE): $(COBJ)
	@ echo "  LINK" $(EXE)
	@ $(CC) $(COBJ) $(LNFLAGS) -o $(EXE)

cleanlib:
	rm -f $(LIB)	

lib: cleanlib $(LIB)

$(LIB):  $(LIBOBJ)
	@ echo "ar $@"
	@ $(AR) $(ARFLAGS) $@ $(COBJ)

%.o: %.c
	@ echo "  CC" $<
	@ $(CC) $(CFLAGS) -c $< -o $@

debug:
	@ $(MAKE) "CFLAGS=$(CFLAGS) -g -O0 -DDEBUG"

gcc:
	@ $(MAKE) "CC=gcc"

clang:
	@ $(MAKE) "CC=clang"

clean: cleanlib
	rm -f $(COBJ) $(EXE)

todo:
	@ find src -type f | xargs grep -n -i "TODO"
	@ find src -type f | xargs grep -n -i "FIXME"

loc: 
	@ wc -l src/*.[ch]

# requires sloccount
sloc:
	@ sloccount src lib | grep '(SLOC)'

.PHONY= loc sloc todo clean all debug gcc gprof
