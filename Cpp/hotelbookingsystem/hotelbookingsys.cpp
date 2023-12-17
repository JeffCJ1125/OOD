#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

using namespace std;

class Hotel {
public:
  virtual ~Hotel() = default;
  enum Roomtype { Standard, Deluxe, Suite };
  Roomtype get_room_type(string str) {
    if (str == "Standard")
      return Standard;
    if (str == "Deluxe")
      return Deluxe;
    if (str == "Suite")
      return Suite;
    return Standard;
  }
  int operatingcost(Roomtype type, int days) {
    switch (type) {
    case Standard:
      return 0;
      break;
    case Deluxe:
      return 40 * days;
      break;
    case Suite:
      return 80 * days + 10 * (days / 5);
    default:
      return 0;
      break;
    }
  }
  virtual int get_cost(Roomtype type, int days) = 0;
};

class Marriott : public Hotel {
public:
  int get_cost(Roomtype type, int days) override {
    return 100 * days + operatingcost(type, days);
  }
};

class Hilton : public Hotel {
public:
  int get_cost(Roomtype type, int days) override {
    int cost = 120 * days + operatingcost(type, days);
    if (type == Deluxe)
      cost += 20 * days;
    return cost;
  }
};

class HolidayInn : public Hotel {
public:
  int get_cost(Roomtype type, int days) override { return 90 * days; }
};

class ExcelsiorInn : public Hotel {
public:
  int get_cost(Roomtype type, int days) override {
    int op_cost_per_day = 3 * operatingcost(type, 1);
    return (150 > op_cost_per_day) ? 150 * days : op_cost_per_day * days;
  }
};

class BookingSystem {
private:
  istringstream iss;
  unique_ptr<Hotel> get_hotel_object(string hotel_name) {
    if (hotel_name == "Marriott") {
      return make_unique<Marriott>();
    }
    if (hotel_name == "Hilton") {
      return make_unique<Hilton>();
    }
    if (hotel_name == "HolidayInn") {
      return make_unique<HolidayInn>();
    }
    if (hotel_name == "ExcelsiorInn") {
      return make_unique<ExcelsiorInn>();
    }
    return nullptr;
  }

public:
  int getting_cost(string str) {
    string hotel_name;
    int days;
    string type_str;
    iss.str(str);
    iss >> hotel_name >> days >> type_str;
    iss.clear();
    cout << "Cost at " << hotel_name << " with " << type_str << "type for "
         << days << " days is ";
    unique_ptr<Hotel> hotel = get_hotel_object(hotel_name);
    if (hotel != nullptr) {
      Hotel::Roomtype type = hotel->get_room_type(type_str);
      int cost = hotel->get_cost(type, days);
      return cost;
    }
    cout << "wrong hotel " << endl;
    return 0;
  }
};

int main(int argc, char *argv[]) {
  std::vector<std::string> test_input = {"Marriott 3 Deluxe", "Hilton 2 Suite",
                                         "HolidayInn 5 Standard",
                                         "ExcelsiorInn 1 Suite"};

  BookingSystem booksys;
  for (auto str : test_input) {
    cout << booksys.getting_cost(str) << endl;
  }

  return 0;
}