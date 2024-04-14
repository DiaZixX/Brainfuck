# Brainfuck

I have divided my work on Brainfuck language processing into several parts : 
- Interpreter 
- Compiler to C 
- Syntax analysis

A Makefile is available, here are the commands :
- `make` : Compile all parts of this project
- `make compiler` : Compiles only the compiler part
- `make interpreter` : Compiles only the interpreter part
- `make syntax` : Compiles only the syntax part
- `make test` : Runs tests on everything
- `make clean` : Cleans up everything created by the makefile

All the binaries are generated in a `Bin/` subfolder.

## Interpreter

In this section, I filter the Brainfuck program on the input side to give the same program on the output side, reduced to 8 useful characters. 

## Compiler 

In this section, I translate the Brainfuck program given as C or Python input in a `Compiled/` subfolder.
The command is : `./compiler c <name_of_file>` or `./compiler python <name_of_file>`.

## Syntax analysis

In this section, I check if the code is syntactically correct.