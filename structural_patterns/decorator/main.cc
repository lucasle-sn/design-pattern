#include <iostream>
#include <memory>

/**
 * @brief "Decorator" is a structural design pattern that lets you attach new
 * behaviors to objects by placing these objects inside special wrapper objects
 * that contain the behaviors.
 *
 * # Problem: Wearing clothes is an example.
 *  + When it is cold, wrap with a sweater.
 *  + When it is raining, put on a raincoat.
 *  + etc
 *
 * # Structure: refers to "decorator_structure.png"
 *
 * # Applicability:
 *  + When you need to be able to assign extra behaviours without breaking the
 *    code.
 *  + When not possible to extend object's behaviour using inheritance.
 *
 * # Pros & Cons:
 *  + Pros: - Extend objects's behaviour without new subclass.
 *          - Add/remove responsibilities from object at runtime.
 *          - Can combine several behaviours with multi decorators.
 *          - align with "Single Responsibility Principle".
 *  + Cons: - Hard to remove wrapper
 *          - Code layer is ugly.
 *
 * Note: "Composite" and "Decorator" have similar structure diagrams since both
 * rely on recursive composition to organize an open-ended number of objects.
 *
 * A "Decorator" is like a "Composite" but only has one child component. Also,
 * "Decorator" adds additional responsibilities to the wrapped object, while
 * "Composite" just sums up its children’s results.
 */

/**
 * # Implementation:
 *
 * Step 1: The Component declares the common interface for both wrappers and
 * wrapped objects.
 *
 * Step 2: Concrete Component is a class of objects being wrapped. It defines
 * the basic behavior, which can be altered by decorators.
 *
 * Step 3: The Base Decorator class has a field for referencing a wrapped
 * object. The field’s type should be declared as the component interface so it
 * can contain both concrete components and decorators. The base decorator
 * delegates all operations to the wrapped object.
 *
 * Step 4:Concrete Decorators define extra behaviors that can be added to
 * components dynamically. Concrete decorators override methods of the base
 * decorator and execute their behavior either before or after calling the
 * parent method.
 *
 * Step 5: The Client can wrap components in multiple layers of decorators, as
 * long as it works with all objects via the component interface.
 *
 */

/**
 * @brief The base Component interface defines operations that can be altered by
 * decorators.
 */
class Component {
 public:
  /**
   * @brief Constructor
   */
  Component() = default;

  Component(const Component &) = delete;
  Component(Component &&) = delete;

  /**
   * @brief Destructor
   */
  virtual ~Component() = default;

  /**
   * @brief Execution
   *
   * @return std::string
   */
  virtual std::string execute() const = 0;
};

/**
 * @brief Concrete Components provide default implementations of the operations.
 */
class ConcreteComponent : public Component {
 public:
  /**
   * @brief Constructor
   */
  ConcreteComponent() = default;

  ConcreteComponent(const ConcreteComponent &) = delete;
  ConcreteComponent(ConcreteComponent &&) = delete;
  ConcreteComponent operator=(const ConcreteComponent &) = delete;
  ConcreteComponent operator=(ConcreteComponent &&) = delete;

  /**
   * @brief Destructor
   */
  ~ConcreteComponent() = default;

  /**
   * @brief Execution
   *
   * @return std::string
   */
  std::string execute() const override { return "ConcreteComponent"; }
};

/**
 * @brief The base Decorator class
 *
 * The base Decorator class follows the same interface as the other components.
 * The primary purpose of this class is to define the wrapping interface for all
 * concrete decorators. The default implementation of the wrapping code might
 * include a field for storing a wrapped component and the means to initialize
 * it.
 */
class Decorator : public Component {
 public:
  /**
   * @brief Constructor
   */
  Decorator() = delete;
  Decorator(const Decorator &) = delete;
  Decorator(Decorator &&) = delete;

  explicit Decorator(Component *component) : component_(component) {}

  /**
   * @brief Destructor
   */
  virtual ~Decorator() = default;

  /**
   * @brief Execution
   *
   * @return std::string
   */
  std::string execute() const override { return this->component_->execute(); }

 protected:
  /**
   * @brief Base component
   */
  Component *component_;
};

/**
 * @brief Concrete Decorators call the wrapped object and alter its result in
 * some way.
 *
 * Decorators may call parent implementation of the operation, instead of
 * calling the wrapped object directly. This approach simplifies extension of
 * decorator classes.
 */
class ConcreteDecoratorA : public Decorator {
 public:
  /**
   * @brief Constructor
   */
  ConcreteDecoratorA() = delete;
  ConcreteDecoratorA(const ConcreteDecoratorA &) = delete;
  ConcreteDecoratorA(ConcreteDecoratorA &&) = delete;
  ConcreteDecoratorA operator=(const ConcreteDecoratorA &) = delete;
  ConcreteDecoratorA operator=(ConcreteDecoratorA &&) = delete;

  ConcreteDecoratorA(Component *component) : Decorator(component) {}

  /**
   * @brief Destructor
   */
  ~ConcreteDecoratorA() = default;

  /**
   * @brief Execution
   *
   * @return std::string
   */
  std::string execute() const override {
    return "ConcreteDecoratorA(" + Decorator::execute() + ")";
  }
};

/**
 * @brief ConcreteDecoratorB class
 */
class ConcreteDecoratorB : public Decorator {
 public:
  /**
   * @brief Constructor
   */
  ConcreteDecoratorB() = delete;
  ConcreteDecoratorB(const ConcreteDecoratorB &) = delete;
  ConcreteDecoratorB(ConcreteDecoratorB &&) = delete;
  ConcreteDecoratorB operator=(const ConcreteDecoratorB &) = delete;
  ConcreteDecoratorB operator=(ConcreteDecoratorA &&) = delete;

  ConcreteDecoratorB(Component *component) : Decorator(component) {}

  /**
   * @brief Destructor
   */
  ~ConcreteDecoratorB() = default;

  /**
   * @brief Execution
   *
   * @return std::string
   */
  std::string execute() const override {
    return "ConcreteDecoratorB(" + Decorator::execute() + ")";
  }
};

/**
 * The client code works with all objects using the Component interface. This
 * way it can stay independent of the concrete classes of components it works
 * with.
 */
void run_client(Component *component) {
  std::cout << "RESULT: " << component->execute();
}

int main() {
  /**
   * This way the client code can support both simple components...
   */
  auto simple = std::make_unique<ConcreteComponent>();
  std::cout << "Client: I've got a simple component:\n";
  run_client(simple.get());
  std::cout << "\n\n";

  /**
   * Note how decorators can wrap not only simple components but the other
   * decorators as well.
   */
  auto decorator_1 = std::make_unique<ConcreteDecoratorA>(simple.get());
  auto decorator_2 = std::make_unique<ConcreteDecoratorB>(decorator_1.get());
  std::cout << "Client: Now I've got a decorated component:\n";
  run_client(decorator_2.get());
  std::cout << "\n\n";

  return 0;
}
