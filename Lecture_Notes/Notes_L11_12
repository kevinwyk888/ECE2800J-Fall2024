## Introduction

11. Testing
12. Exception

### Testing

- Debugging: Fixed something we have known broken
- Testing: Discover bugs.

#### Incremental Testing

Testing as small units.

Simple inputs/ Boundary conditions/ Noesense

Regression Testing: Every time change the smallest part of the code.

### General Debugging Technique

1. `cout`
2. Debugger, such as `GDB`
3. `assert` Function
   - `#include<cassert>`;
   - If false, stop program and printing error by `cerr` 

#### Disable Assert

1.`#define NDEBUG`, `#ifndef` and `#endif`
2.`g++ -DNDEBUG`

### Exception

**Concept:**
When an exception occurs, the block of the normal-case code is exited, and control is passed to another block of code (the error handling code).

**In C++**

- Throwing an exception: try block.
- Catching an exception: catch block

```cpp
#include<iostream>
#include<cassert>
#include<string>
using namespace std;
int f(int n) {
    if (n<0) throw "123";
    if (n>1) throw 12;
    if (n==0) throw 1.00;
    if (n==1) throw false;
    return 0;
}
int main(int argc, char *argv[]) {
try {
    f(1);
} catch (int v) {
    cout << "int" ;
} catch (double v) {
    cout << "double";
} catch (const char* v) {
    cout << "string";
} catch (...) {
    cout << "None of above";
}

return 0;
}
```