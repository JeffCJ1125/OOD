#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Book {
public:
  Book(string str) : title(str){};
  enum BookType { Fiction, Non_Fiction, Reference, Non };
  string title{""};
  virtual int due_days() = 0;
};

class Fiction : public Book {
public:
  Fiction(string str) : Book(str){};
  int due_days() override { return 15; }
};
class Non_Fiction : public Book {
public:
  Non_Fiction(string str) : Book(str){};
  int due_days() override { return 30; }
};
class Reference : public Book {
public:
  Reference(string str) : Book(str){};
  int due_days() override { return 0; }
};

class Management_System {
private:
  unique_ptr<Book> book{nullptr};
  Book::BookType prase_type(string str) {
    if (str == "Fiction")
      return Book::BookType::Fiction;
    if (str == "Non-Fiction")
      return Book::BookType::Non_Fiction;
    if (str == "Reference")
      return Book::BookType::Reference;
    return Book::BookType::Non;
  }
  unique_ptr<Book> get_book(pair<string, string> input) {
    string type_str = input.first;
    string title = input.second;
    switch (prase_type(type_str)) {
    case Book::BookType::Fiction:
      return make_unique<Fiction>(title);
    case Book::BookType::Non_Fiction:
      return make_unique<Non_Fiction>(title);
    case Book::BookType::Reference:
      return make_unique<Reference>(title);
    default:
      return nullptr;
      break;
    }
    return nullptr;
  }

public:
  void check_due_day(pair<string, string> input) {
    book = get_book(input);
    if (book == nullptr) {
      cout << "no this kind of book " << endl;
      return;
    }
    int due_days = book->due_days();
    if (due_days > 0) {
      cout << "\"" << book->title << "\" due in " << due_days << " days."
           << endl;
    } else {
      cout << "\"" << book->title << "\" cannot be borrowed." << endl;
    }

    return;
  }
};

int main(int argc, char *argv[]) {
  std::vector<std::pair<std::string, std::string>> test_input = {
      {"Fiction", "The Great Gatsby"},
      {"Non-Fiction", "A Brief History of Time"},
      {"Reference", "Encyclopedia Britannica"},
      {"Fiction", "1984"}};
  Management_System book_sys;
  for (auto &pairs : test_input) {
    book_sys.check_due_day(pairs);
  }
  return 0;
}