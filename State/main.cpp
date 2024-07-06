#pragma once

#include <iostream>
#include <string>

class State;
class StateContext;
class SolidState;
class LiquidState;
class GasState;

class State {
  std::string name;

 public:
  State(const std::string& name) : name(name) {}
  std::string GetName() { return name; }
  virtual void Freeze(StateContext*) = 0;
  virtual void Heat(StateContext*) = 0;
};

class StateContext {
 private:
  State* state;

 public:
  StateContext(State* state) : state(state) {}

  void Freeze() {
    std::cout << "Freezing " << state->GetName() << std::endl;
    state->Freeze(this);
  }
  void Heat() {
    std::cout << "Heating " << state->GetName() << std::endl;
    state->Heat(this);
  }

  void SetState(State* s) {
    std::cout << state->GetName() << " turns into "
              << s->GetName() << std::endl;
    delete state;
    state = s;
  }
  State* GetState() { return state; }

  ~StateContext() { delete state; }
};

class SolidState : public State {
 public:
  SolidState() : State("Ice") {}
  virtual void Freeze(StateContext* state);
  virtual void Heat(StateContext* state);
};
class LiquidState : public State {
 public:
  LiquidState() : State("Water") {}
  virtual void Freeze(StateContext* state);
  virtual void Heat(StateContext* state);
};
class GasState : public State {
 public:
  GasState() : State("Steam") {}
  virtual void Freeze(StateContext* state);
  virtual void Heat(StateContext* state);
};

void SolidState::Freeze(StateContext* state) {
  std::cout << "Nothing happens" << std::endl;
}
void SolidState::Heat(StateContext* state) {
  state->SetState(new LiquidState());
}

void LiquidState::Freeze(StateContext* state) {
  state->SetState(new SolidState());
}
void LiquidState::Heat(StateContext* state) {
  state->SetState(new GasState());
}

void GasState::Freeze(StateContext* state) {
  state->SetState(new LiquidState());
}
void GasState::Heat(StateContext* state) {
  std::cout << "Nothing happens" << std::endl;
}

void Test() {
  char state;
  std::cout << "Choose initial state of water:\n"
               "1 - Ice\n"
               "2 - Water\n"
               "3 - Steam\n";

  std::cin >> state;
  StateContext* sc = new StateContext(new SolidState());

  switch (state) {
    case 1:
      sc->SetState(new SolidState());
      break;

    case 2:
      sc->SetState(new LiquidState());
      break;

    case 3:
      sc->SetState(new GasState());
      break;

    default:
      break;
  }
  std::cout << "\nKeep setting operations." << std::endl;
  std::cout << "Available operations\n"
               "1 - Heating\n"
               "2 - Freezing\n"
               "3 - Exit\n\n";

  auto loop = true;

  while (loop) {
    int choise;
    std::cin >> choise;

    switch (choise) {
      case 1:
        sc->Heat();
        break;

      case 2:
        sc->Freeze();
        break;

      case 3:
        loop = false;
        break;

      default:
        break;
    }
  }

  delete sc;
}

int main() {
  Test();
  return 0;
}