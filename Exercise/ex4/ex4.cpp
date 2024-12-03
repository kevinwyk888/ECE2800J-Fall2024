#include<string.h>
#include<iostream>
#include "ex4.h"

bookInventory::bookInventory() : numBooks(0) {
  // Initialize all books to default values
  for (int i = 0; i < MAX_BOOKS; ++i) {
    books[i] = Book();
  }
}
void bookInventory::addBook(const Book &book) {
  if (numBooks >= (unsigned int)MAX_BOOKS) {
    throw Exception("The inventory is full.");
  }
  books[numBooks++] = book;
}
int bookInventory::searchBook(const std::string &title) const {
    for (unsigned int i = 0; i < numBooks; i++) 
        if (books[i].title == title) return i+1;
    throw Exception("Book "+title+" not found.");
}
void bookInventory::setBook(const Book &book, int ID) {
    if ( ID > MAX_BOOKS  || ID <= 0  ) 
        throw Exception("Invalid book ID.");
    if ((unsigned int) ID >  numBooks) books[numBooks++] = book; 
    else books[ID-1] = book;
}
Book bookInventory::viewBook(int ID) const {
    if ( (unsigned int)ID > numBooks || ID <= 0 ) 
        throw Exception("Invalid book ID.");
    return books[ID-1];
}
void bookInventory::removeBook(int ID) {
    if ( (unsigned int)ID > numBooks || ID <= 0  ) 
        throw Exception("Invalid book ID."); 
    for (unsigned int i = ID-1; i < numBooks-1 ; i++)
        books[i] = books[i+1];
    numBooks--;
}
void bookInventory::printInventory() const {
    if (numBooks == 0) throw  Exception("The inventory is empty.");
    for (unsigned int i = 0; i < numBooks ; i++) {
        std:: cout << "Book ID: " << i+1 << std::endl;
        std:: cout << "Title: " << books[i].title << std::endl;
        std:: cout << "Author: " << books[i].author << std::endl;
        std:: cout << "Status: " << ((books[i].isAvailable)?("available"):("not available")) << std::endl;
    }
}
library::library() {
  // Initialize all books to default values
  numBooks=0;
  for (int i = 0; i < MAX_BOOKS; i++) {
    books[i] = Book();
  }
}

void library:: borrowBook(int ID) {
    if ((unsigned int) ID > numBooks || ID <= 0 ) throw Exception("Invalid book ID.");
    if (!books[ID-1].isAvailable) throw Exception("Book "+books[ID-1].title+" is not available.");
    books[ID-1].isAvailable = false;
}

void library:: returnBook(int ID) {
    if ((unsigned int) ID > numBooks || ID <= 0 ) throw Exception("Invalid book ID.");
    if (books[ID-1].isAvailable) throw Exception("Book "+books[ID-1].title+" is already available.");
    books[ID-1].isAvailable = true;
}

void library:: listBorrowed() const {
    bool flag=true;
    for (unsigned int i = 0; i < numBooks ; i++) 
        flag = flag && books[i].isAvailable;
    if (flag) throw Exception("All books are available.");
    for (unsigned int i = 0; i< numBooks ; i++) 
        if (books[i].isAvailable == false) {
            std:: cout << "Book ID: " << i+1 << std::endl;
            std:: cout << "Title: " << books[i].title << std::endl;
            std:: cout << "Author: " << books[i].author << std::endl;
        }
}