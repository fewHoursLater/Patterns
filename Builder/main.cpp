#include <iostream>
#include <memory>
#include <string>

// Abstract Product
class Pizza {
 private:
  std::string dough;
  std::string sauce;
  std::string topping;

 public:
  Pizza() {}
  ~Pizza() {}

  void SetDough(const std::string& d) { dough = d; }
  void SetSauce(const std::string& s) { sauce = s; }
  void SetTopping(const std::string& t) { topping = t; }

  void ShowPizza() {
    std::cout << "Pizza with Dough as " << dough << ", Sauce as " << sauce
              << " and Topping as " << topping << std::endl;
  }
};

// Abstract Builder
class PizzaBuilder {
 protected:
  std::shared_ptr<Pizza> pizza;

 public:
  PizzaBuilder() {}
  virtual ~PizzaBuilder() {}
  std::shared_ptr<Pizza> GetPizza() { return pizza; }
  void createNewPizzaProduct() { pizza.reset(new Pizza); }

  virtual void buildDough() = 0;
  virtual void buildSauce() = 0;
  virtual void buildTopping() = 0;
};

// Concrete Builder
class HawaiianPizzaBuilder : public PizzaBuilder {
 public:
  HawaiianPizzaBuilder() : PizzaBuilder() {}
  ~HawaiianPizzaBuilder() {}

  void buildDough() { pizza->SetDough("corn dough"); }
  void buildSauce() { pizza->SetSauce("1000 islands"); }
  void buildTopping() { pizza->SetTopping("pineapple and chicken"); }
};

// Concrete Builder
class SpicyPizzaBuilder : public PizzaBuilder {
 public:
  SpicyPizzaBuilder() : PizzaBuilder() {}
  ~SpicyPizzaBuilder() {}

  void buildDough() { pizza->SetDough("yeast dough"); }
  void buildSauce() { pizza->SetSauce("pepper bomb"); }
  void buildTopping() { pizza->SetTopping("Caroline Reaper"); }
};


// Director
class Waiter {
 private:
  PizzaBuilder* pizzaBuilder;

 public:
  Waiter() : pizzaBuilder(nullptr) {}
  ~Waiter() {}

  void SetPizzaBuilder(PizzaBuilder* b) { pizzaBuilder = b; }
  std::shared_ptr<Pizza> GetPizza() { return pizzaBuilder->GetPizza(); }
  void ConstructPizza() {
    pizzaBuilder->createNewPizzaProduct();
    pizzaBuilder->buildDough();
    pizzaBuilder->buildSauce();
    pizzaBuilder->buildTopping();
  }
};

int main() {
  Waiter waiter;

  HawaiianPizzaBuilder hawaiianPizzaBuilder;
  waiter.SetPizzaBuilder(&hawaiianPizzaBuilder);
  waiter.ConstructPizza();
  std::shared_ptr<Pizza> pizza = waiter.GetPizza();
  pizza->ShowPizza();

  SpicyPizzaBuilder spicyPizzaBuilder;
  waiter.SetPizzaBuilder(&spicyPizzaBuilder);
  waiter.ConstructPizza();
  pizza = waiter.GetPizza();
  pizza->ShowPizza();

  return 0;
}