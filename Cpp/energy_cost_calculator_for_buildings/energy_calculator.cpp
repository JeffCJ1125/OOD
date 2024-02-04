#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

using namespace std;

// Energy_type
//   Enum{types}
//   virtual get_base_cost()
class EnergyType {
public:
  virtual double get_base_cost() = 0;
  virtual double get_flat_cost() { return 0; }

private:
};

// Energy :: Energy_type
//    variable:
//      base_cost
//    function:
//      get_base_cost() override
class Electricity : public EnergyType {
private:
  double base_cost{0.12};

public:
  Electricity() : EnergyType(){};
  double get_base_cost() override { return base_cost; }
};

class Gas : public EnergyType {
private:
  double base_cost{0.05};

public:
  Gas() : EnergyType(){};
  double get_base_cost() override { return base_cost; }
};

class Solar : public EnergyType {
private:
  double base_cost{0.02};

public:
  Solar() : EnergyType(){};
  double get_base_cost() override { return base_cost; }
  double get_flat_cost() override { return 100; }
};

class UsageType {
public:
  virtual double get_multiplier() = 0;

private:
};

class Residential : public UsageType {
private:
  double multiplier{1.0};

public:
  double get_multiplier() override { return multiplier; }
};

class Commercial : public UsageType {
private:
  double multiplier{1.5};

public:
  double get_multiplier() override { return multiplier; }
};

class Industrial : public UsageType {
private:
  double multiplier{2.0};

public:
  double get_multiplier() override { return multiplier; }
};

// building
//  variables:
//  square_foot_size - double
//  source - Energy_type
//  functions:
//    calculate_cost() - double
class Buildings {
private:
  double square_foot_size;
  unique_ptr<EnergyType> e_type;
  unique_ptr<UsageType> u_type;

public:
  Buildings(double size, string e_str, string u_str)
      : square_foot_size(size), e_type(get_energy(e_str)),
        u_type(get_usage(u_str)){};

  unique_ptr<EnergyType> get_energy(string str) {
    if (str == "Electricity") {
      return make_unique<Electricity>();
    }
    if (str == "Gas") {
      return make_unique<Gas>();
    }
    if (str == "Solar") {
      return make_unique<Solar>();
    }
    return nullptr;
  }
  unique_ptr<UsageType> get_usage(string str) {
    if (str == "Residential") {
      return make_unique<Residential>();
    }
    if (str == "Commercial") {
      return make_unique<Commercial>();
    }
    if (str == "Industrial") {
      return make_unique<Industrial>();
    }
    return nullptr;
  }
  double calculate_cost() {
    double cost = 0;
    cost =
        e_type->get_base_cost() * u_type->get_multiplier() * square_foot_size +
        e_type->get_flat_cost();
    return cost;
  }
};

// calculator
//   variables:
//     buildings
//   function:
//      parse_input(str) - private
//      calculate_cost(str) - public
class EnergyCalculator {
private:
  unique_ptr<Buildings> buildings{nullptr};
  bool parse_input(string str) {
    istringstream iss(str);
    string usage_str;
    double size;
    string energy_str;
    iss >> usage_str >> size >> energy_str;
    buildings = make_unique<Buildings>(size, energy_str, usage_str);
    return (buildings != nullptr);
  }

public:
  void calculate_cost(string input_str) {
    if (parse_input(input_str)) {
      cout << input_str << " cost : " << buildings->calculate_cost() << endl;
    } else {
      cout << "Error input " << endl;
    }
  }
};

int main(int argc, char *argv[]) {
  vector<string> test{"Residential 1000 Electricity", "Commercial 2000 Gas",
                      "Industrial 500 Solar"};
  EnergyCalculator calculator;
  for (auto s : test) {
    calculator.calculate_cost(s);
  }
  return 0;
}
