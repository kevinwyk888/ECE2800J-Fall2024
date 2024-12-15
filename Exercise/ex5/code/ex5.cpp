#include<string>
#include<iostream>
#include "ex5.h"

bookInventory :: bookInventory(): numBooks(0), empty(true), size(MAX_BOOKS){
    books = new Book[MAX_BOOKS];
}

bookInventory :: bookInventory(int maxbook): numBooks(0), empty(true), size(maxbook){
    if (maxbook < 1 || maxbook > MAX_BOOKS) throw Exception("Invalid size");
    books = new Book[maxbook];
}

bookInventory :: ~bookInventory() {
    empty = true;
    numBooks = 0;
    size = 0;
    delete[] books;
}

void bookInventory :: addBook(const Book &book) {
    if (numBooks >= size) throw Exception("The inventory is full.");
    empty = false;
    books[numBooks++] = book;
}

void bookInventory :: removeBook(int ID) {
    if (ID <= 0 || (unsigned int)ID > numBooks ) throw Exception("Invalid book ID.");
    for (unsigned int i = ID-1; i < numBooks-1 ; i++)
        books[i] = books[i+1];
    numBooks--;
    empty = (numBooks == 0);
    books[numBooks].author = "";
    books[numBooks].title = "";
}

void bookInventory :: printInventory() const {
    if (numBooks == 0) throw  Exception("The inventory is empty.");
    for (unsigned int i = 0; i < numBooks ; i++) {
        std:: cout << "Book ID: " << i+1 << std::endl;
        std:: cout << "Title: " << books[i].title << std::endl;
        std:: cout << "Author: " << books[i].author << std::endl;
    }
}


bool bookInventory :: repOK() {
    if (books == NULL) return false;
    if (empty) {
        if (numBooks != 0) return false;
        for (unsigned int i = 0; i < size; i++)
            if (!(books[i].author == "" && books[i].title == "")) return false;
    } else {
        if (numBooks == 0) return false;
        bool flag=true;
        for (unsigned int i = 0; i < size; i++)
            if (!(books[i].author == "" && books[i].title == "")) flag=false;
        if (flag) return false;
    }
    if (numBooks > size) return false;
    for (unsigned int i = 0; i < numBooks; i++)
        if ((books[i].author == "" && books[i].title == "")) return false;
    for (unsigned int i = numBooks; i < size ; i++)
        if (!(books[i].author == "" && books[i].title == "")) return false;
    return true;
}