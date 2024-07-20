#include <iostream>
#include <mutex>
#include <string>
#include <thread>

class Singleton {
 protected:
  Singleton(const std::string value) : value_(value) {}
  ~Singleton() {}
  std::string value_;
  static Singleton* singleton_;
  static std::mutex mutex_;

 public:
  Singleton(Singleton& other) = delete;
  void operator=(const Singleton&) = delete;

  static Singleton* GetInstance(const std::string& value);

  std::string value() const { return value_; }
};

Singleton* Singleton::singleton_{nullptr};
std::mutex Singleton::mutex_;

/**
 * The first time we call GetInstance we will lock the storage location
 *      and then we make sure again that the variable is null and then we
 *      set the value.
 */
Singleton* Singleton::GetInstance(const std::string& value) {
  std::lock_guard<std::mutex> lock(mutex_);
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
  // Safety variant of using singleton under multithreads
  // The values will be the same all the time - singleton was reused

  std::thread t1(Thread1);
  std::thread t2(Thread2);
  t1.join();
  t2.join();

  return 0;
}