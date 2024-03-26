# Brainfuck

I have divided my work on Brainfuck language processing into several parts : 
- Interpreter 
- Compiler to C 
- Syntax analysis

A Makefile is available, here are the commands :
- `make` : Compile all parts of this project
- `make compiler` : Compiles only the compiler part
- `make interpreter` : Compiles only the interpreter part
- `make syntax` : Work In Progress
- `make clean` : Cleans up everything created by the makefile

All the binaries are generated in a `Bin/` subfolder.

## Interpreter

In this section, I filter the Brainfuck program on the input side to give the same program on the output side, reduced to 8 useful characters. 

## Compiler 

In this section, I translate the Brainfuck program given as C input in a `Compiled/` subfolder.

## Syntax analysis

Work In Progress