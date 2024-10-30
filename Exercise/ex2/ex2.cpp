#include "ex2.h"
#include <string>
#include <cstdio>

Library initLibrary() { //set an empty library
    Library library;
    library.numBooks=0;
    Book book_s[MAX_BOOKS];
    for (int i=0;i<MAX_BOOKS;i++) 
        library.books[i] = { i+1, "", "", false};
    return library;
}
void addBook(Library &lib, std::string title, std::string author){ //add the book
    if (lib.numBooks == MAX_BOOKS) { 
        printf("The library is full.\n"); 
        return;
    }
    lib.books[lib.numBooks].title = title;
    lib.books[lib.numBooks].author = author;
    lib.books[lib.numBooks++].isAvailable = true;
}
void borrowBook(Library &lib, int ID) { // judge the status of the book
    if (ID<1 || ID>MAX_BOOKS) {
        printf("Invalid book ID.\n");
        return;
    }
    if (lib.books[ID-1].isAvailable == false) 
        printf("Book %s is not available.\n", lib.books[ID-1].title.c_str());
    else {
        printf("Book %s is borrowed.\n", lib.books[ID-1].title.c_str());
        lib.books[ID-1].isAvailable = false;
    }

}
void returnBook(Library &lib, int ID) { // judge the status of the book
    if (ID<1 || ID>MAX_BOOKS) {
        printf("Invalid book ID.\n");
        return;
    }
    if (lib.books[ID-1].isAvailable == false) {
        printf("Book %s is returned.\n", lib.books[ID-1].title.c_str());
        lib.books[ID-1].isAvailable = true;
        }
    else 
        printf("Book %s is already available.\n", lib.books[ID-1].title.c_str());
}
void printLibrary(const Library &lib) { // use loop to print all books
    if (lib.numBooks == 0) {
        printf("The library is empty.\n");
        return;
    }
    for (int i=0;i<lib.numBooks;i++) {
        printf("Book ID: %d\n", i+1);
        printf("Title: %s\n",lib.books[i].title.c_str());
        printf("Author: %s\n",lib.books[i].author.c_str());
        printf("Status: %s\n", lib.books[i].isAvailable ? "available" : "not available");
    }
}