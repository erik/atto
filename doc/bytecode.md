#Bytecode Format
This file describes the Atto bytecode format as of v1.0. Anything later
may no longer be accurate.

##Structure
- Header
- Constants
- Vars
- Code

###Header
- An Atto bytecode file starts off with a signature to identify the
format, which is `\016ato`.
- Following this is the version of the Atto virtual machine, which is
encoded as a single byte. If, for example, the version was 5.1, the
the byte following the signature would be `0x51`. This must be the
same as the version of the VM the bytecode is running on.
- The next byte contains the endianess of the machine on which the
bytecode was compiled, either 0 or 1. Little endian machines would
have a value of 1, big endians would have 0. Must be the same for the
bytecode to be able to be run.

###Constants
Following the header section is a section defining all of the
constants for the program to be run. The general format for constants
is:

        Number of Constants (int)
        [
          Constant Type (byte)
            Constant (various representations)
          ...
        ]

First in the constant section is the number of constants to be
read. This value is an int.

For each constant, the type of the constant is dumped first as a byte,
followed by the representation of constant. The types constants can
have are:

- TYPE_NULL   : 1
- TYPE_NUMBER : 2
- TYPE_STRING : 3 
- TYPE_BOOL   : 5

Following this are the actual encodings of the constants. 
####Null
Nothing is dumped to the file after the type.
####Number
A number the size of AttoNumber (long double) in bytes is dumped to
the bytecode.
####String
First, the length of the string is dumped as an int. Next, each
individual char of the string is dumped as a byte. This includes the
trailing '\0'
####Bool
A single byte is dumped to the file, technically can be any value that
can fit into a char, but should ideally be 0 or 1 to represent false
and true.

###Vars
Since vars are set and accessed from the code itself, the only thing
in this section of the bytecoded is the number of vars there are,
dumped as an int.

###Code
This is where the actual opcodes are stored. First, an int is dumped,
with the number of opcodes to follow. Next, each opcode is dumped to
the file, each as a type AttoNumber (long double). 
To see a description of the opcodes and what they do, see
doc/opcodes.md


If you want to browse the code for the writing and loading of
bytecode, see src/dump.c (write to file), and src/load.c (load
bytecode into usuable format).
