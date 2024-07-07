#include <iostream>
#include <string>

class Chair {
 public:
  virtual ~Chair(){};
  virtual std::string chairFunction() const = 0;
};

class VictorianChair : public Chair {
 public:
  std::string chairFunction() const override {
    return "An order for the manufacture of a Victorian chair has been accepted";
  }
};

class ModernChair : public Chair {
  std::string chairFunction() const override {
    return "An order for the manufacture of a Modern chair has been accepted";
  }
};

class Sofa {
 public:
  virtual ~Sofa(){};
  virtual std::string sofaFunction() const = 0;
};

class VictorianSofa : public Sofa {
 public:
  std::string sofaFunction() const override {
    return "An order for the manufacture of a Victorian sofa has been accepted";
  }
};

class ModernSofa : public Sofa {
 public:
  std::string sofaFunction() const override {
    return "An order for the manufacture of a Modern sofa has been accepted";
  }
};

class FurnitureFactory {
 public:
  virtual Chair* сreateChair() const = 0;
  virtual Sofa* createSofa() const = 0;
};

class VictorianFurnitureFactory : public FurnitureFactory {
 public:
  Chair* сreateChair() const override { return new VictorianChair(); }
  Sofa* createSofa() const override { return new VictorianSofa(); }
};

class ModernFurnitureFactory : public FurnitureFactory {
 public:
  Chair* сreateChair() const override { return new ModernChair(); }
  Sofa* createSofa() const override { return new ModernSofa(); }
};

void ClientCode(const FurnitureFactory& factory) {
  const Chair* product_chair = factory.сreateChair();
  const Sofa* product_sofa = factory.createSofa();
  std::cout << product_chair->chairFunction() << "\n";
  std::cout << product_sofa->sofaFunction() << "\n\n";

  delete product_chair;
  delete product_sofa;
}

int main() {
  bool loop = true;

  while (loop) {
    int choise;
    std::cout << "What style of furniture would you like to order?\n"
                 "1 - Victorian furniture\n"
                 "2 - Modern furniture\n"
                 "3 - exit\n\n";
    std::cin >> choise;

    switch (choise) {
      case 1:
      {
        VictorianFurnitureFactory* f1 = new VictorianFurnitureFactory();
        ClientCode(*f1);
        delete f1;
      }
        break;
      case 2:
      {
        ModernFurnitureFactory* f2 = new ModernFurnitureFactory();
        ClientCode(*f2);
        delete f2;
      }
        break;
      case 3:
        return loop = false;
      default:
        break;
    }
  }

  return 0;
}