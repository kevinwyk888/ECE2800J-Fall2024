//Guard
#ifndef EX2

#define EX2
#include <string>
#include <cstdio>
//Definition
static const int MAX_BOOKS = 10;
typedef struct _Book{
    int ID;
    std::string title, author;
    bool isAvailable;
}Book;
typedef struct _Library{
    Book books[MAX_BOOKS];
    int numBooks;
}Library;
Library initLibrary();
void addBook(Library &lib, std::string title, std::string author);
void borrowBook(Library &lib, int ID);
void returnBook(Library &lib, int ID);
void printLibrary(const Library &lib);

#endif 
