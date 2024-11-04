### Introduction

7. Recursive

8. Enum

9. Program Arguement

10. I-O stream


### Recursion

Composition: 

- base case 
- recursive

### Function Pointers

```cpp
int min(int x,int y) {return x<y?x:y;}

int (*foo) (int, int);
foo=min;
```

### Enum

```cpp
#include<iostream>
using namespace std;
int main() {
    enum Suit_t {A,B,C,D};
    Suit_t suit = A;
    if (suit == A) cout << "1";
    cout << A << B << C << D; // const int 0/1/2/3
    return 0;
}
```

### Passing Arguement to Program

```cpp 
int main(int argc, char *argv[]) {
    for (int i=0;i< argc;i++) 
        cout << argv[i] <<endl;
    cout << argv[0] << endl;
    cout << atoi("1") << atoi("112") << atoi("afa") << atoi("12a121");
    return 0;
}
```

- ``argv[0]`` returns the root of directory.
- ``atoi`` "11" -> 11 "11a" -> 11 "abs" -> 0

### I-O stream

- Two kinds of stream data: characters and binary data.

#### OutStream: cout

`cout << "Hello"` 

`<<` is called the insertion operator, used for inserting things into output stream.

##### Print with Fixed Field Width

`#include <iomanip>`

`cout << foo << setw(4) << bar << endl;`

`setw()` sets the width of the following number to the specified number of positions and **right-aligns** the number within that field.

#### Output: Buffering

The output will be saved in the underlying operating system.

- The buffer will be written when:
  -  A newline is inserted. (e.g. endl / '\n')
  -  Buffer is flushed (e.g. `cout << "ok" << flush`)
  -  Buffer full
  -  `cin` begins
  -  Program exits.
-  `cerr` will not be buffered.

### Input Stream: Composition

`cin >> foo`

- `>>` is called the extraction operator, and is used to extract things from the input stream.

**tips:** `cin` will read the input until the space appear.

#### Other input Function

1. `getline`: it will get the whole line and not include `\n`

```cpp
 cin >> foo >> bar;
 getline(cin, baz);
```
2. `get`: it will read a single character.

```cpp
char ch;
cin.get(ch);
```
### Input: Buffering

Characters typed (which are to be gathered by cin) are stored in a buffer until the enter key is pressed.

### Failed Input 

- `cin` will return false when meeting invalid input.
- You should use `cin.clear()` to flush the error.
- If do not use `cin.ignore()`, the rest of input will remain;

### Using File Stream

Head file: `<fstream>`

- `ifstream iFile`: Declare an input file stream.
- `ofstream iFile`: Declare an output file stream.

```cpp
int bar;
string baz;
iFile.open("text.txt");
iFile >> bar;
getline(iFile, baz);

while (iFile) {
    cout << baz ;
    getline(iFile, baz);
}

OR

while(getline(iFile, line)) {
 cout << line << endl;
}

iFile.close();
```

### String Stream

```cpp

 #include <sstream>
 istringstream iStream;
 int foo;
 double bar;
 iStream.str(line);
 iStream >> foo >> bar;

// line = "1 3.14"
// foo = 1 bar = 3.14

 int foo = 512;
 int bar = 1024;
 string result;
 ostringstream oStream;
 oStream << foo << " " << bar;
 result = oStream.str();

// result = "1 3.14"

```