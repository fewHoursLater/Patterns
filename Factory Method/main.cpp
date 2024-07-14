#include <iostream>
#include <string>

class Vehicle {
 public:
  virtual ~Vehicle() {}
  virtual std::string getType() const = 0;
};

class Bicylce : public Vehicle {
 public:
  std::string getType() const override { return "Bicycle"; }
};

class Jet : public Vehicle {
 public:
  std::string getType() const override { return "Jet"; }
};

class Car : public Vehicle {
 public:
  std::string getType() const override { return "Car"; }
};

class Manufacturer {
 public:
  virtual ~Manufacturer(){};
  virtual Vehicle* FactoryMethod() const = 0;
};

class BicycleManufacturer : public Manufacturer {
 public:
  Vehicle* FactoryMethod() const override { return new Bicylce(); }
};

class JetManufacturer : public Manufacturer {
 public:
  Vehicle* FactoryMethod() const override { return new Jet(); }
};

class CarManufacturer : public Manufacturer {
 public:
  Vehicle* FactoryMethod() const override { return new Car(); }
};

int main() {
  Manufacturer* creator = new BicycleManufacturer();
  Vehicle* vehicle = creator->FactoryMethod();
  std::cout << vehicle->getType() << std::endl;

  creator = new JetManufacturer();
  vehicle = creator->FactoryMethod();
  std::cout << vehicle->getType() << std::endl;

  creator = new CarManufacturer();
  vehicle = creator->FactoryMethod();
  std::cout << vehicle->getType() << std::endl;

  delete creator;
  return 0;
}