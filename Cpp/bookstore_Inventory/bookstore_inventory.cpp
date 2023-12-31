#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

using namespace std;

class Book {
private:
  double base_price = 20;

public:
  double get_base_price() { return base_price; }
  virtual double tax_free_price(int quantity) { return base_price * quantity; }
  virtual double calculate_tax(double price) = 0;
  double price(int quantity, bool member) {
    double price_before_tax = tax_free_price(quantity);
    price_before_tax += (quantity > 10) ? -0.05 * price_before_tax : 0;
    double final_price = price_before_tax + calculate_tax(price_before_tax);
    return (member) ? final_price * 0.9 : final_price;
  };
};

class Fiction : public Book {
public:
  double calculate_tax(double price) override { return price * 0.1; }
};

class Educational : public Book {
public:
  double calculate_tax(double price) override { return 0; }
};

class Non_Fiction : public Book {
public:
  double calculate_tax(double price) override { return price * 0.15; }
};

class Rare_Editions : public Book {
private:
  double rarity_surcharge = 10;

public:
  double tax_free_price(int quantity) {
    return quantity * (get_base_price() + rarity_surcharge);
  }
  double calculate_tax(double price) override { return price * 0.20; }
};

class InventorySys {
private:
  unique_ptr<Book> book = nullptr;
  istringstream iss;
  unique_ptr<Book> setBook(string booktype_str) {
    if (booktype_str == "Fiction")
      return make_unique<Fiction>();
    if (booktype_str == "Non-Fiction")
      return make_unique<Non_Fiction>();
    if (booktype_str == "Educational")
      return make_unique<Educational>();
    if (booktype_str == "Rare_Editions")
      return make_unique<Rare_Editions>();
    return nullptr;
  }

public:
  double order_price(string order) {
    string booktype_str;
    int quantity = 0;
    string member_status;
    iss.str(order);
    iss >> booktype_str >> quantity >> member_status;
    iss.clear();
    book = setBook(booktype_str);
    if (book == nullptr) {
      cout << "we don't have this book" << endl;
      return -1;
    }
    return book->price(quantity, (member_status == "Member"));
  }
};

int main(int argc, char *argv[]) {
  std::vector<std::string> testInput = {
      "Fiction 3 Member", "Non-Fiction 12 Non-Member", "Educational 5 Member",
      "Rare_Editions 2 Non-Member"};

  InventorySys inv_sys;
  for (auto &order : testInput) {
    cout << order << " cost : " << inv_sys.order_price(order) << endl;
  }
}
