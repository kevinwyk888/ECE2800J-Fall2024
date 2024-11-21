#ifndef EX4_H
#define EX4_H

#include <string>

const int MAX_BOOKS = 10;

class Exception {

  std::string message = "";

public:
  Exception(const std::string &message) : message(message) {}
  std::string what() const { return message; }
};

struct Book {
  std::string title;
  std::string author;
  bool isAvailable;

  // Default constructor
  Book() : title(""), author(""), isAvailable(true) {}
  // Constructor with parameters
  Book(const std::string &title, const std::string &author) : title(title), author(author), isAvailable(true) {}
};

class bookInventory {

protected:
  // Array of books
  Book books[MAX_BOOKS];
  // Number of books in the inventory
  unsigned int numBooks;

public:
  /**
   * @brief Default constructor. Initializes the number of books to 0.
   * and sets the books with default values.
   */
  bookInventory();

  /**
   * @brief Returns the number of books in the inventory.
   *
   * @return The number of books.
   */
  int getNumBooks() const { return numBooks; }

  /**
   * @brief Adds a book to the inventory.
   *
   * @param book The book to be added.
   * @throw Exception if the inventory is full.
   */
  virtual void addBook(const Book &book);

  /**
   * @brief Searches for a book in the inventory.
   *
   * @param title The title of the book to be searched.
   * @return The ID of the book in the inventory. The ID is the index of the book in the books array + 1.
   * @throw Exception if the book is not found.
   */
  virtual int searchBook(const std::string &title) const;

  /**
   * @brief Updates a book in the inventory. If the book is not found, it is added to the inventory and the number of books is incremented.
   *
   * @param book The book to be set.
   * @param ID The ID of the book to be set. The ID is the index of the book in the books array + 1.
   * @throw Exception if the ID is invalid.
   */
  virtual void setBook(const Book &book, int ID);

  /**
   * @brief Returns a book from the inventory.
   *
   * @param ID The ID of the book to be returned. The ID is the index of the book in the books array + 1.
   * @return The book.
   * @throw Exception if the ID is invalid.
   */
  virtual Book viewBook(int ID) const;

  /**
   * @brief Removes a book from the inventory.
   *
   * @param ID The ID of the book to be removed. The ID is the index of the book in the books array + 1.
   * @throw Exception if the ID is invalid.
   */
  virtual void removeBook(int ID);

  /**
   * @brief Prints the inventory of books.
   *
   * @throw Exception if the inventory is empty.
   */
  virtual void printInventory() const;

  // Default destructor, does nothing
  ~bookInventory() = default;
};

class library : public bookInventory {

public:
  /**
   * @brief Default constructor. Initializes the number of books to 0.
   * and sets the books with default values.
   */
  library();

  /**
   * @brief Borrow a book from the library.
   *
   * @param ID The ID of the book to be borrowed. The ID is the index of the book in the books array + 1.
   * @throw Exception if the ID is invalid.
   * @throw Exception if the book is not available.
   */
  void borrowBook(int ID);

  /**
   * @brief Return a book to the library.
   *
   * @param ID The ID of the book to be returned.
   * @throw Exception if the ID is invalid.
   * @throw Exception if the book is already available.
   */
  void returnBook(int ID);

  /**
   * @brief Print the books that are currently borrowed.
   *
   * @throw Exception if there are no borrowed books.
   */
  void listBorrowed() const;

  ~library() = default;
};

#endif