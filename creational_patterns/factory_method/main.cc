#include <cstring>
#include <iostream>
#include <memory>

/**
 * # Implementation
 *
 * Step 1: The Product declares the interface, which is common to all objects
 * that can be produced by the creator and its subclasses.
 *
 * Step 2: Concrete Products are different implementations of the product
 * interface.
 *
 * Step 3: The Creator class declares the factory method that returns new
 * product objects. It’s important that the return type of this method matches
 * the product interface.
 *
 * You can declare the factory method as abstract to force all subclasses to
 * implement their own versions of the method. As an alternative, the base
 * factory method can return some default product type.
 *
 * Note, despite its name, product creation is not the primary responsibility of
 * the creator. Usually, the creator class already has some core business logic
 * related to products. The factory method helps to decouple this logic from the
 * concrete product classes. Here is an analogy: a large software development
 * company can have a training department for programmers. However, the primary
 * function of the company as a whole is still writing code, not producing
 * programmers.
 *
 * Step 4: Concrete Creators override the base factory method so it returns a
 * different type of product.
 *
 * Note that the factory method doesn’t have to create new instances all the
 * time. It can also return existing objects from a cache, an object pool, or
 * another source.
 *
 */

/**
 * @brief This example reflects the design in "factory_method.png"
 */

//////////////////////////////////////////////////////////////////////

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