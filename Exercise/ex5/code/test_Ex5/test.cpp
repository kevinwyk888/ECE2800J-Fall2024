#include "../ex5.h"
#include <iostream>
#include <cassert>
#include <string>
#include <sstream>

int main() {
    /******************* Test For Default Constructor *******************/
    std::cout << "Test for Default Constructor" << std::endl;
    bookInventory bi;
    assert(bi.isEmpty() == true);
    assert(bi.getSize() == MAX_BOOKS);
    assert(bi.getNumBooks() == 0);
    std::cout << "Test Passed" << std::endl;

    /******************* Test For Default Constructor *******************/
    std::cout << "Test for Constructor with Parameter" << std::endl;
    bookInventory bi2(5);
    assert(bi2.isEmpty() == true);
    assert(bi2.getSize() == 5);
    assert(bi2.getNumBooks() == 0);
    std::cout << "Test Passed" << std::endl;

    /******************* Test For Add Book *******************/
    std::cout << "Test for Add Book" << std::endl;
    Book b1("Book1", "Author1");
    bi.addBook(b1);
    assert(bi.isEmpty() == false);
    assert(bi.getSize() == MAX_BOOKS);
    assert(bi.getNumBooks() == 1);
    assert(bi.books[0].title == "Book1");
    assert(bi.books[0].author == "Author1");
    // Test for Exception
    try {
        for (int i = 0; i < MAX_BOOKS; i++) {
            bi.addBook(b1);
        }
    } catch (Exception &e) {
        assert(e.what() == "The inventory is full.");
    }
    std::cout << "Test Passed" << std::endl;

    /******************* Test For Remove Book *******************/
    std::cout << "Test for Remove Book" << std::endl;
    bookInventory bi4(5);
    Book b2("Book2", "Author2");
    Book b3("Book3", "Author3");
    bi4.addBook(b1);
    bi4.addBook(b2);
    bi4.addBook(b3);
    bi4.removeBook(2);
    assert(bi4.isEmpty() == false);
    assert(bi4.getSize() == 5);
    assert(bi4.getNumBooks() == 2);
    assert(bi4.books[0].title == "Book1");
    assert(bi4.books[0].author == "Author1");
    bi4.removeBook(1);
    assert(bi4.isEmpty() == false);
    assert(bi4.getSize() == 5);
    assert(bi4.getNumBooks() == 1);
    assert(bi4.books[0].title == "Book3");
    assert(bi4.books[0].author == "Author3");
    bi4.removeBook(1);
    assert(bi4.isEmpty() == true);
    assert(bi4.getSize() == 5);
    assert(bi4.getNumBooks() == 0);
    // Test for Exception
    
    std::cout << "2222222" << std::endl; 
    try {
        bi4.removeBook(1);
        std::cout << "1111111" << std::endl; 
    } catch (Exception &e) {
        assert(e.what() == "Invalid book ID.");
    }
    std::cout << "3333333" << std::endl; 
    bi4.addBook(b1);
    bi4.addBook(b2);
    bi4.addBook(b3);
    try {
        bi4.removeBook(4);
    } catch (Exception &e) {
        assert(e.what() == "Invalid book ID.");
    }
    std::cout << "Test Passed" << std::endl;

    /******************* Test For Print Inventory *******************/
    

    std::cout << "Test for Print Inventory" << std::endl;
    bookInventory bi5(5);
    Book b4("Book4", "Author4");
    bi5.addBook(b1);
    // 检测print
    std::string output = "Book ID: 1\nTitle: Book1\nAuthor: Author1\n";
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());
    bi5.printInventory();
    std::cout.rdbuf(old);
    assert(buffer.str() == output);
    // Test for Exception
    bi5.removeBook(1);
    try {
        bi5.printInventory();
    } catch (Exception &e) {
        assert(e.what() == "The inventory is empty.");
    }
    /***************** Test For repOK *******************/
    std::cout << "Test for repOK" << std::endl;
    bookInventory bi6(5);
    assert(bi6.repOK() == true);
    bi6.numBooks = 6;
    assert(bi6.repOK() == false);
    bi6.numBooks = 0;
    bi6.empty = false;
    assert(bi6.repOK() == false);
    std::cout << "Test Passed" << std::endl;

    /******************* Test For Destructor *******************/
    std::cout << "Test for Destructor" << std::endl;
    bookInventory *bi3 = new bookInventory(5);
    delete bi3;
    std::cout << "Test Passed" << std::endl;

}