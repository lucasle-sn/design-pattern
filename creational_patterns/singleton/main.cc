#include <iostream>
#include <mutex>
#include <thread>

/**
 * # Implemetation
 *
 * The Singleton class declares the static method getInstance that returns the
 * same instance of its own class.
 *
 * The Singleton’s constructor should be hidden from the client code. Calling
 * the getInstance method should be the only way of getting the Singleton
 * object.
 *
 */

class Singleton {
 private:
  explicit Singleton(int value) : value_(value) {}
  ~Singleton() {}

  static Singleton *instance_;  ///< Singleton instance
  static std::mutex mutex_;     ///< mutex for thread safe
  int value_;                   ///< temp var for testing

 public:
  Singleton() = delete;
  Singleton(const Singleton &) = delete;
  Singleton(Singleton &&) = delete;
  Singleton &operator=(const Singleton &) = delete;
  Singleton &operator=(Singleton &&) = delete;

  static Singleton *getInstance(int value) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!instance_) {
      return new Singleton(value);
    }
    return instance_;
  }

  int value() const { return value_; }
};

Singleton *Singleton::instance_{nullptr};
std::mutex Singleton::mutex_;

void func(int value) {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  auto singleton = Singleton::getInstance(value);
  std::cout << singleton->value() << std::endl;
}

int main() {
  std::thread t1(func, 1);
  std::thread t2(func, 2);
  t1.join();
  t2.join();

  return EXIT_SUCCESS;
}