#include <iostream>

/**
 * @brief The Abstract Class defines a template method that contains a skeleton
 * of some algorithm, composed of calls to (usually) abstract primitive
 * operations.
 *
 * Concrete subclasses should implement these operations, but leave the template
 * method itself intact.
 */
class AbstractClass {
 public:
  /**
   * @brief The template method defines the skeleton of an algorithm.
   */
  void execute_algorithm() const {
    this->execute_step_1();
    this->execute_step_2();
    this->execute_step_3();
    this->execute_step_4();
    this->execute_step_5();
    this->execute_step_6();
  }

 protected:
  /**
   * Step 1 & 2 (Base operations)
   */
  void execute_step_1() const {
    std::cout << "AbstractClass: Implements step 1\n";
  }
  void execute_step_2() const {
    std::cout << "AbstractClass: Implements step 2\n";
  }

  /**
   * Step 3 & 4 (overriding required).
   */
  virtual void execute_step_3() const = 0;
  virtual void execute_step_4() const = 0;

  /**
   * Step 3 & 4 (overriding optional).
   */
  virtual void execute_step_5() const {}
  virtual void execute_step_6() const {}
};

/**
 * @brief Concrete class 2
 *
 * This class overrides required steps (3 & 4), and uses default implementation
 * of step 5
 */
class ConcreteClass1 : public AbstractClass {
 protected:
  /**
   * Override step 3 4 (required)
   */
  void execute_step_3() const override {
    std::cout << "ConcreteClass1: Implements step 3\n";
  }

  void execute_step_4() const override {
    std::cout << "ConcreteClass1: Implemented step 4\n";
  }
};

/**
 * @brief Concrete class 2
 *
 * This class overrides required steps (3 & 4), and some optional steps (5)
 */
class ConcreteClass2 : public AbstractClass {
 protected:
  /**
   * Override step 3 4 (required)
   */
  void execute_step_3() const override {
    std::cout << "ConcreteClass2: Implements step 3\n";
  }

  void execute_step_4() const override {
    std::cout << "ConcreteClass2: Implemented step 4\n";
  }

  /**
   * Override step 5
   */
  void execute_step_5() const override {
    std::cout << "ConcreteClass2: Implemented step 5\n";
  }
};

/**
 * The client code calls the template method to execute the algorithm. Client
 * code does not have to know the concrete class of an object it works with, as
 * long as it works with objects through the interface of their base class.
 */
void run_client(AbstractClass *obj) { obj->execute_algorithm(); }

int main() {
  std::cout << "Same client code can work with different subclasses:\n";
  ConcreteClass1 concrete_class_1 = ConcreteClass1();
  run_client(&concrete_class_1);
  std::cout << "\n";

  std::cout << "Same client code can work with different subclasses:\n";
  ConcreteClass2 concrete_class_2 = ConcreteClass2();
  run_client(&concrete_class_2);

  return 0;
}
