CSRC := $(shell find src -name "*.c")
CHDR := $(shell find src -name "*.h")

COBJ := $(CSRC:.c=.o)

AR      := ar
ARFLAGS := cq
LIB     := libatto.a

CC := clang
CFLAGS := -Wall -Wextra -pedantic -std=c99 -Iinclude/ -Wno-unused-parameter -O2
LNFLAGS := -lm
EXE := atto

####

all: $(COBJ) $(EXE)

$(EXE): $(COBJ)
	@ echo "  LINK" $(EXE)
	@ $(CC) $(COBJ) $(LNFLAGS) -o $(EXE)

cleanlib:
	rm -f $(LIB)	

lib: cleanlib $(LIB)

$(LIB):  $(LIBOBJ)
	@echo "ar $@"
	@$(AR) $(ARFLAGS) $@ $(COBJ)

%.o: %.c
	@ echo "  CC" $<
	@ $(CC) $(CFLAGS) -c $< -o $@

debug:
	@$(MAKE) "CFLAGS=$(CFLAGS) -g -O0"

gcc:
	@$(MAKE) "CC=gcc"

clang:
	@$(MAKE) "CC=clang"

clean: cleanlib
	rm -f $(COBJ) $(EXE)

todo:
	@find src -type f | xargs grep -n -i "TODO"
	@find src -type f | xargs grep -n -i "FIXME"

loc: 
	@wc -l src/*.[ch]

# requires sloccount
sloc:
	@sloccount src lib | grep '(SLOC)'

.PHONY= loc sloc todo clean all debug gcc
