#include <cstring>
#include <iostream>

/**
 * @brief Abstract Factory is a creational design pattern that lets you produce
 * families of related objects without specifying their concrete classes.
 *
 * # Problem: A furiture shop has
 *  (1) a family of products <Chair>, <Sofa>, <Table>, and
 *  (2) variants of these families <Modern>, <Victorian>, and <ArtDeco>.
 * Also, furniture vendors update their catalogs very often, and you wouldn’t
 * want to change the core code each time it happen.
 * The expectation is to pick seperate products of the same style.
 *
 * # Structure: refers to "abstract_factory_structure.png"
 *
 * # Applicability:
 *  + When works with various families (e.g. chair, table) but not depends on
 * concrete classes (for future extensibility)
 *  + When you have a class with a set of Factory Method that blur its primary
 * responsibility.
 *
 * # Pros & cons:
 * + Pros:  - be sure that products getting from a factory are compatible
 *          - avoid tight coupling between concrete products and client code
 *          - align with "Single Respondsibility principle"
 *          - align with "Open/Closed principle"
 * + Cons:  - becomes complicated because alot of new interfaces and classes
 *
 * # Note:
 * "Abstract Factory" is often based on set of "Factory Method".
 */

/**
 * # Implementation:
 *
 * Step 1: Abstract Products declare interfaces for a set of distinct but
 * related products which make up a product family (chair/sofa).
 *
 * Step 2: Concrete Products are various implementations of abstract products,
 * grouped by variants. Each abstract product (chair/sofa) must be implemented
 * in all given variants (Victorian/Modern).
 *
 * Step 3: The Abstract Factory interface declares a set of methods for creating
 * each of the abstract products.
 *
 * Step 4: Concrete Factories implement creation methods of the abstract
 * factory. Each concrete factory corresponds to a specific variant of products
 * and creates only those product variants.
 *
 * Step 5: Although concrete factories instantiate concrete products, signatures
 * of their creation methods must return corresponding abstract products. This
 * way the client code that uses a factory doesn’t get coupled to the specific
 * variant of the product it gets from a factory. The Client can work with any
 * concrete factory/product variant, as long as it communicates with their
 * objects via abstract interfaces.
 */

/**
 * @brief This example reflects the design in "abstract_factory_structure.png"
 */

/**
 * @brief Abstract class defining a family <ProductA>
 */
class AbstractProductA {
 public:
  /**
   * @brief Destructor
   */
  virtual ~AbstractProductA(){};

  /**
   * @brief method_a()
   *
   * @return std::string
   */
  virtual std::string method_a() const = 0;
};

/**
 * @brief Concrete Product A variant (1)
 */
class ConcreteProductA1 : public AbstractProductA {
 public:
  /**
   * @brief method_a()
   *
   * @return std::string
   */
  std::string method_a() const override {
    return "The result of the product A1.";
  }
};

/**
 * @brief Concrete Product A variant (2)
 */
class ConcreteProductA2 : public AbstractProductA {
 public:
  /**
   * @brief method_a()
   *
   * @return std::string
   */
  std::string method_a() const override {
    return "The result of the product A2.";
  }
};

/**
 * Here's the the base interface of another product. All products can interact
 * with each other, but proper interaction is possible only between products of
 * the same concrete variant.
 */

/**
 * @brief Abstract class defining a family <ProductB>
 */
class AbstractProductB {
 public:
  /**
   * @brief Destructor
   */
  virtual ~AbstractProductB(){};

  /**
   * @brief method_b()
   *
   * @return std::string
   */
  virtual std::string method_b() const = 0;

  /**
   * @brief another_method_b() that can collaborate with the ProductA
   *
   * @return std::string
   *
   * @note The Abstract Factory makes sure that all products it creates are of
   * the same variant and thus, compatible.
   */
  virtual std::string another_method_b(
      const AbstractProductA &collaborator) const = 0;
};

/**
 * Concrete Products are created by corresponding Concrete Factories.
 */

/**
 * @brief Concrete Product B variant (1)
 */
class ConcreteProductB1 : public AbstractProductB {
 public:
  /**
   * @brief method_b()
   *
   * @return std::string
   */
  std::string method_b() const override {
    return "The result of the product B1.";
  }

  /**
   * @brief another_method_b() that can collaborate with the ProductA
   *
   * @return std::string
   *
   * The variant, Product B1, is only able to work correctly with the variant,
   * Product A1. Nevertheless, it accepts any instance of AbstractProductA as an
   * argument.
   */
  std::string another_method_b(
      const AbstractProductA &collaborator) const override {
    const std::string result = collaborator.method_a();
    return "The result of the B1 collaborating with ( " + result + " )";
  }
};

/**
 * @brief Concrete Product B variant (2)
 */
class ConcreteProductB2 : public AbstractProductB {
 public:
  /**
   * @brief method_b()
   *
   * @return std::string
   */
  std::string method_b() const override {
    return "The result of the product B2.";
  }

  /**
   * @brief another_method_b() that can collaborate with the ProductA
   *
   * @return std::string
   *
   * The variant, Product B2, is only able to work correctly with the variant,
   * Product A2. Nevertheless, it accepts any instance of AbstractProductA as an
   * argument.
   */
  std::string another_method_b(
      const AbstractProductA &collaborator) const override {
    const std::string result = collaborator.method_a();
    return "The result of the B2 collaborating with ( " + result + " )";
  }
};

/**
 * The Abstract Factory interface declares a set of methods that return
 * different abstract products. These products are called a family and are
 * related by a high-level theme or concept. Products of one family are usually
 * able to collaborate among themselves. A family of products may have several
 * variants, but the products of one variant are incompatible with products of
 * another.
 */
class AbstractFactory {
 public:
  /**
   * @brief Constructor
   */
  AbstractFactory() = default;

  /**
   * @brief Destructor
   */
  virtual ~AbstractFactory() = default;

  /**
   * @brief Create a Product A object
   *
   * @return AbstractProductA*
   */
  virtual AbstractProductA *CreateProductA() const = 0;

  /**
   * @brief Create a Product B object
   *
   * @return AbstractProductB*
   */
  virtual AbstractProductB *CreateProductB() const = 0;
};

/**
 * Concrete Factories produce a family of products that belong to a single
 * variant. The factory guarantees that resulting products are compatible. Note
 * that signatures of the Concrete Factory's methods return an abstract product,
 * while inside the method a concrete product is instantiated.
 */

/**
 * @brief Concrete Factory for product families of variant (1)
 */
class ConcreteFactory1 : public AbstractFactory {
 public:
  /**
   * @brief Constructor
   */
  ConcreteFactory1() = default;

  /**
   * @brief Destructor
   */
  ~ConcreteFactory1() = default;

  /**
   * @brief Create a Product A object
   *
   * @return AbstractProductA*
   */
  AbstractProductA *CreateProductA() const override {
    return new ConcreteProductA1();
  }

  /**
   * @brief Create a Product B object
   *
   * @return AbstractProductB*
   */
  AbstractProductB *CreateProductB() const override {
    return new ConcreteProductB1();
  }
};

/**
 * Each Concrete Factory has a corresponding product variant.
 */
class ConcreteFactory2 : public AbstractFactory {
 public:
  /**
   * @brief Constructor
   */
  ConcreteFactory2() = default;

  /**
   * @brief Destructor
   */
  ~ConcreteFactory2() = default;

  /**
   * @brief Create a Product A object
   *
   * @return AbstractProductA*
   */
  AbstractProductA *CreateProductA() const override {
    return new ConcreteProductA2();
  }

  /**
   * @brief Create a Product B object
   *
   * @return AbstractProductB*
   */
  AbstractProductB *CreateProductB() const override {
    return new ConcreteProductB2();
  }
};

/**
 * The client code works with factories and products only through abstract
 * types: AbstractFactory and AbstractProduct. This lets you pass any factory or
 * product subclass to the client code without breaking it.
 */

void run_client(const AbstractFactory &factory) {
  const AbstractProductA *product_a = factory.CreateProductA();
  const AbstractProductB *product_b = factory.CreateProductB();
  std::cout << product_b->method_b() << "\n";
  std::cout << product_b->another_method_b(*product_a) << "\n";
  delete product_a;
  delete product_b;
}

int main() {
  {
    std::cout << "Client: Testing client code with the 1st factory type:\n";
    ConcreteFactory1 f1 = ConcreteFactory1();
    run_client(f1);
    std::cout << std::endl;
  }

  {
    std::cout
        << "Client: Testing the same client code with the 2nd factory type:\n";
    ConcreteFactory2 f2 = ConcreteFactory2();
    run_client(f2);
    std::cout << std::endl;
  }

  return 0;
}
