#include <cstring>
#include <iostream>
#include <memory>

class Product {
 public:
  virtual ~Product() = default;
  virtual void doStuff() = 0;
};

class ConcreteProductA final : public Product {
 public:
  void doStuff() override {
    std::cout << "Do stuff with Product A" << std::endl;
  }
};
class ConcreteProductB final : public Product {
 public:
  void doStuff() override {
    std::cout << "Do stuff with Product B" << std::endl;
  }
};

class Creator {
 public:
  virtual void someOperation(){};
  virtual std::unique_ptr<Product> createProduct() = 0;
};

class ConcreateCreatorA final : public Creator {
 public:
  std::unique_ptr<Product> createProduct() override {
    return std::make_unique<ConcreteProductA>();
  }

  void someOperation() override {
    std::cout << "Some operation in Creator of Product A" << std::endl;
  }
};
class ConcreateCreatorB final : public Creator {
 public:
  std::unique_ptr<Product> createProduct() override {
    return std::make_unique<ConcreteProductB>();
  }
};

void run(Creator &creator) {
  creator.someOperation();
  auto product = creator.createProduct();
  product->doStuff();
}

int main() {
  {
    std::cout << "Create with Creator A" << std::endl;
    ConcreateCreatorA creator;
    run(creator);
  }
  {
    std::cout << "Create with Creator B" << std::endl;
    ConcreateCreatorB creator;
    run(creator);
  }
}