#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Vechicle {
private:
public:
  enum comfort_class { Standard, Enhanced, Luxury };
  double get_base_score(comfort_class type, int distance) {
    switch (type) {
    case Standard:
      return 50.0;
      break;
    case Enhanced:
      return 75.0;
      break;
    case Luxury:
      return 100.0 + distance;
      break;
    default:
      cout << "unknow comfort class " << endl;
      break;
    }
    return 0.0;
  }
  virtual double get_total_score(comfort_class type, int distance) = 0;
};

class Car : public Vechicle {
public:
  double get_total_score(comfort_class type, int distance) override {
    return get_base_score(type, distance) + 0.5 * distance;
  }
};

class Train : public Vechicle {
public:
  double get_total_score(comfort_class type, int distance) override {
    return get_base_score(type, distance) + 1.0 * distance;
  }
};

class Bus : public Vechicle {
public:
  double get_total_score(comfort_class type, int distance) override {
    return get_base_score(type, distance) + 0.3 * distance;
  }
};

class Hyperloop : public Vechicle {
public:
  double get_total_score(comfort_class type, int distance) override {
    return (get_base_score(type, distance) + 5 * distance) * 0.9;
  }
};

class Tool {
private:
  istringstream iss;
  unique_ptr<Vechicle> set_vechicle(string str) {
    if (str == "Car") {
      return make_unique<Car>();
    } else if (str == "Train") {
      return make_unique<Train>();
    } else if (str == "Bus") {
      return make_unique<Bus>();
    } else if (str == "Hyperloop") {
      return make_unique<Hyperloop>();
    }
    cout << "unknow vechicle" << endl;
    return nullptr;
  }
  Vechicle::comfort_class get_type(string str) {
    if (str == "Standard")
      return Vechicle::Standard;
    if (str == "Enhanced")
      return Vechicle::Enhanced;
    if (str == "Luxury")
      return Vechicle::Luxury;
    cout << "unnknow comfort class return standard" << endl;
    return Vechicle::Standard;
  }

public:
  Tool(){};
  double get_socre(string input) {
    string vechicle_str;
    double distance;
    string type_str;
    iss.str(input);
    iss >> vechicle_str >> distance >> type_str;
    iss.clear();
    unique_ptr<Vechicle> vechicle = set_vechicle(vechicle_str);
    if (vechicle == nullptr)
      return -1;
    Vechicle::comfort_class type = get_type(type_str);
    return vechicle->get_total_score(type, distance);
  }
};

int main(int argc, char *argv[]) {
  vector<string> testinput{"Car 200.0 Luxury",     "Car 200.0 Standard",
                           "Train 200.0 Enhanced", "Bus 200.0 Standard",
                           "Bus 200.0 Luxury",     "Hyperloop 200.0 Standard",
                           "supercar 200.0 Luxury"};

  Tool tool;
  for (auto &str : testinput) {
    cout << str << " : " << tool.get_socre(str) << endl;
  }
}