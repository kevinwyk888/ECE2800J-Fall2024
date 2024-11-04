### Introduction

This chapter aims to review the basic C++ grammars or other fundamental points.

This chapter aims to get insight into the const qualifier.

### lvalue and rvalue

- **lvalue**: An expression which may appear as either the left-hand or right-hand side of an assignment.

    **rvalue**: An expression which may appear on the right- but not left-hand side of an assignment.

### Array

Array can be passed as a reference.

```cpp
 int sum(int a[], unsigned int size);
 // Returns the sum of the first
 // size elements of array a[]
```

### Reference

Reference is an alternative name for a object.

```cpp
int ival = 1024;
int &refVal = iVal;


Wrong!
int &refVal; SHOUlD BE initialized!!!
int &refVal = 10; SHOULD BE Lvalue!

```

### Const qualifier

- Property
  - cannot be modified.
  - should be initialized.

```cpp
const int iVal = 10;
```

### Const Reference

```cpp
const int iVal = 10;
const int &rVal = iVal;

const int &rVal = 10; Could be rvalue.
```

**Benefits**

- `const`: pass large structure will expensive.
- `&` : avoid mistakenly change the content.

### Const Pointers

```cpp
const int *p; // pointer to const;
int *const p; //const pointer;
const int *const p;
```

**typedef**

```cpp
typedef const T constT_t;
typedef constT_t * ptr_constT_t; //pointer to const

typedef T* ptr_t;
typedef const ptr_t constT_ptr_t; // const to pointer
```

### Abstraction

- Provides only those details that matter. 
- Eliminates unnecessary details and reduces complexity.
- Target: Client and Author.
- Two Properties:
  - Local: Not depend on other Abstraction Implementation
  - Substituable: Can be replaced by another Abstraction Implementation.
- Abstraction and abstraction implementation are different.
  -  Abstraction: tells what.
  -  Implementation: tells how
  -  Some abstraction can have different implementation.

#### Procedural Abstraction

Three clauses to the specification

- REQUIRES
- MODIFIES
- EFFECTS