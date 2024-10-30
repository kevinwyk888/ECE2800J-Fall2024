#include "ex2.h"
#include <cstdio>
int main() {
    Library lib = initLibrary();
    addBook(lib, "The Catcher in the Rye", "J.D. Salinger");
    addBook(lib, "To Kill a Mockingbird", "Harper Lee");
    printLibrary(lib);
    borrowBook(lib, 1);
    borrowBook(lib, 2);
    returnBook(lib, 1);
    returnBook(lib, 1);
    printLibrary(lib);
    return 0;
}