#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

using namespace std;
// base case: addition_service
class Addition_Service {
public:
  virtual double calculate_addition_fee(int day) = 0;
};
// addition_fee(int day)

class Insurance : public Addition_Service {
public:
  double calculate_addition_fee(int day) override { return 15.0 * day; }
};
// GPS : addtion_service
class GPS : public Addition_Service {
public:
  double calculate_addition_fee(int day) override { return 10.0 * day; }
};
// None : addtion_service
class None : public Addition_Service {
public:
  double calculate_addition_fee(int day) override { return 0; }
};

// base case: vehicle
class Vehicle {
private:
protected:
  virtual double get_basic_cost() = 0;

public:
  virtual double total_vehicle_cost(int day) { return get_basic_cost() * day; }
};

class Car : public Vehicle {
private:
  double basic_cost{60};

protected:
public:
  double get_basic_cost() override { return basic_cost; }
};

// Truck : vehicle
class Truck : public Vehicle {
private:
  double basic_cost{70};

protected:
public:
  double get_basic_cost() override { return basic_cost; }
};

// SUV : vehicle
class SUV : public Vehicle {
private:
  double basic_cost{50};

protected:
public:
  double get_basic_cost() override { return basic_cost; }
};
// Van : vehicle
class Van : public Vehicle {
private:
  double basic_cost{60};

protected:
public:
  virtual double get_basic_cost() override { return basic_cost; }
};

class Addition_ServiceType {
public:
  static unique_ptr<Addition_Service> parse_type(string str) {
    if (str == "Insurance") {
      return make_unique<Insurance>();
    } else if (str == "GPS") {
      return make_unique<GPS>();
    }
    return make_unique<None>();
  }
};

class VehicleType {
public:
  static unique_ptr<Vehicle> parse_type(string str) {
    if (str == "Car") {
      return make_unique<Car>();
    } else if (str == "SUV") {
      return make_unique<SUV>();
    } else if (str == "Truck") {
      return make_unique<Truck>();
    } else if (str == "Van") {
      return make_unique<Van>();
    }
    return nullptr;
  }
};

class Rental_Calculator {

public:
  double get_rental_cost(string str) {
    parse_input(str);
    if (vehicle == nullptr || add_service == nullptr)
      return -1.0;
    // cout << "total_vehicle_cost " << vehicle->total_vehicle_cost(day) << endl;
    // cout << "add_service cost " << add_service->calculate_addition_fee(day)
    //      << endl;
    return vehicle->total_vehicle_cost(day) +
           add_service->calculate_addition_fee(day);
  }

private:
  unique_ptr<Vehicle> vehicle;
  unique_ptr<Addition_Service> add_service;
  int day{0};
  void parse_input(string str) {
    istringstream iss(str);
    string vehicle_str;
    string add_str;
    iss >> vehicle_str >> day >> add_str;
    vehicle = VehicleType::parse_type(vehicle_str);
    add_service = Addition_ServiceType::parse_type(add_str);
  }
};

int main(int argc, char *argv[]) {
  std::vector<std::string> testInput = {
      "Car 3 Insurance", "SUV 5 GPS Navigation",
      "Truck 1 Insurance GPS Navigation", "Van 2"};
  Rental_Calculator cal;
  vector<double> cost;
  for (auto &str : testInput) {
    cost.push_back(cal.get_rental_cost(str));
  }

  for (auto c : cost) {
    cout << c << endl;
  }
}