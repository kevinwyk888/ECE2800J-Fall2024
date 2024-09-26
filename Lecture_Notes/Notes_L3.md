## Introduction

This chapter aims to understand the compilation process, how to compile a single source file and how to compile multiple source files

**Basic Working Mechanism of Computer**

Code -> Compile+linkers(Programs) -> Machine Code ->  CPU(computer)

## Developing a Program on Linux

- Writing the source code
- Compile the program
  - `g++ -o program source.cpp`
    - `-o` option tells what the name of the output file is.
  - `g++ -c source.cpp` + `g++ -o program source.o`
    - It is equivalent to the first choice
    - `-c` means compilation only.
    - `**.o` means unlinked object code.
- Run the program
  - `./program`
  
 **Diagram** : ![](picture/5.jpg)
  
 **Useful options** : 
  - `-g` : Put debugging information in the executable file
  - `-Wall` : Turn on all warnings.
  
**E.g.**
![](picture/4.jpg)