#include <iostream>
#include <mutex>
#include <string>
#include <thread>

class Singleton {
 protected:
  Singleton(const std::string value) : value_(value) {}
  std::string value_;
  static Singleton* singleton_;

 public:
  Singleton(Singleton& other) = delete;
  void operator=(const Singleton&) = delete;

  static Singleton* GetInstance(const std::string& value);

  std::string value() const { return value_; }
};

Singleton* Singleton::singleton_ = nullptr;

Singleton* Singleton::GetInstance(const std::string& value) {
  if (singleton_ == nullptr) {
    singleton_ = new Singleton(value);
  }
  return singleton_;
}

void Thread1() {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  Singleton* singleton = Singleton::GetInstance("1");
  std::cout << singleton->value() << "\n";
}

void Thread2() {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  Singleton* singleton = Singleton::GetInstance("2");
  std::cout << singleton->value() << "\n";
}

int main() {
  // Unsafety variant of using singleton under multithreads
  // If you see the same values  - singleton was reused
  // If numbers are different - 2 singletons were created

  std::thread t1(Thread1);
  std::thread t2(Thread2);
  t1.join();
  t2.join();

  return 0;
}