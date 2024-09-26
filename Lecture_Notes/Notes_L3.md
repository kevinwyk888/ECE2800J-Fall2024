## Introduction

This chapter aims to understand the compilation process, how to compile a single source file and how to compile multiple source files

**Basic Working Mechanism of Computer**

Code -> Compile+linkers(Programs) -> Machine Code ->  CPU(computer)

## Developing a Program on Linux

- Writing the source code
- Compile the program
  - `g++ -o program source.cpp`
  - `-o` option tells what the name of the output file is.
- Run the program
  - `./program`

  
 **Useful options** : 
  - `-g` : Put debugging information in the executable file
  - `-Wall` : Turn on all warnings.