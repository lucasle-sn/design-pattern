#include <cstring>
#include <iostream>
#include <memory>

/**
 * @brief Strategy is a behavioral design pattern that lets you define a family
 * of algorithms, put each of them into a separate class, and make their objects
 * interchangeable.
 *
 * # Problem: Create a navigation app for casual travellers. In the app, a user
 * should be able to enter an address and see the fastest route to that
 * destination displayed on the map. The features include generating the route
 * for: Road, Public Transport, and Walking.
 *
 * # Structure: refers to "strategy_structure.png"
 *
 * # Applicability:
 *  + When using different variants of an algorithm within an object, and be
 * able to switch algorithm during runtime.
 *  + When having similar classes that only differ in some behavior.
 *  + Isolates logic of classesfrom implementation details.
 *  + When context class has a massive conditional statement that switches
 * between variants.
 *
 * # Pros & cons:
 * + Pros:  - can swap algorithm at rum time.
 *          - isolate implementation details from the code that uses it.
 *          - Can replace inheritance with composition.
 *          - align with "Open/closed principle"
 * + Cons:  - do not use when having a couple of algorithms which rarely change.
 *
 * # Note:
 * "Template Method" is based on inheritance. "Strategy" is based on
 * composition.
 */

/**
 * # Implementation:
 *
 * Step 1: The Context maintains a reference to one of the concrete strategies
 * and communicates with this object only via the strategy interface.
 *
 * Step2: The Strategy interface is common to all concrete strategies. It
 * declares a method the context uses to execute a strategy.
 *
 * Step 3: Concrete Strategies implement different variations of an algorithm
 * the context uses.
 *
 * Step 4: The context calls the execution method on the linked strategy object
 * each time it needs to run the algorithm. The context doesn’t know what type
 * of strategy it works with or how the algorithm is executed.
 *
 * Step 5: The Client creates a specific strategy object and passes it to the
 * context. The context exposes a setter which lets clients replace the strategy
 * associated with the context at runtime.
 */

/**
 * @brief Strategy
 */
class Strategy {
 public:
  /**
   * @brief Default constructor
   */
  Strategy() = default;

  Strategy(const Strategy &) = delete;
  Strategy(Strategy &&) = delete;

  /**
   * @brief Destructor
   */
  virtual ~Strategy() = default;

  /**
   * @brief Execution
   *
   * @param data
   * @return std::string
   */
  virtual void execute(const char *data = nullptr) const = 0;
};

/**
 * @brief Context defines the interface of interest to clients.
 */
class Context {
 public:
  /**
   * @brief Constructor
   *
   * @param strategy Strategy
   */
  explicit Context(std::unique_ptr<Strategy> &&strategy = nullptr)
      : strategy_(std::move(strategy)){};

  Context(const Context &) = delete;
  Context(Context &&) = delete;
  Context operator=(const Context &) = delete;
  Context operator=(Context &&) = delete;

  /**
   * @brief Destructor
   */
  ~Context() = default;

  /**
   * @brief Strategy setter to set trategy object at runtime.
   */
  void set_strategy(std::unique_ptr<Strategy> &&strategy) {
    strategy_ = std::move(strategy);
  }

  /**
   * The Context delegates some work to the Strategy object instead of
   * implementing +multiple versions of the algorithm on its own.
   */
  void do_something() const {
    if (!strategy_) {
      std::cout << "Context: Strategy isn't set\n";
      return;
    }

    std::cout << "Context: Execute strategy:\n";
    strategy_->execute();
    std::cout << "\n";
  }

 private:
  /**
   * @brief strategy
   *
   * The Context maintains a reference to one of the Strategy objects. The
   * Context does not know the concrete class of a strategy. It should work with
   * all strategies via the Strategy interface.
   */
  std::unique_ptr<Strategy> strategy_;
};

/**
 * @brief ConcreteStrategyA inherites from Strategy
 */
class ConcreteStrategyA : public Strategy {
 public:
  ConcreteStrategyA() = delete;
  ConcreteStrategyA(const ConcreteStrategyA &) = delete;
  ConcreteStrategyA(ConcreteStrategyA &&) = delete;
  ConcreteStrategyA operator=(const ConcreteStrategyA &) = delete;
  ConcreteStrategyA operator=(ConcreteStrategyA &&) = delete;

  /**
   * @brief Constructor
   */
  explicit ConcreteStrategyA(size_t number) : internal_number_(number){};

  /**
   * @brief Execute
   *
   * @param data Data
   */
  void execute(const char *data = nullptr) const override {
    fprintf(stdout, "Doing something using Strategy A - Internal data \"%zu\"",
            internal_number_);
  }

 private:
  /**
   * @brief Internal number
   */
  size_t internal_number_{0};
};

/**
 * @brief ConcreteStrategyB inherites from Strategy
 */
class ConcreteStrategyB : public Strategy {
 public:
  ConcreteStrategyB() = delete;
  ConcreteStrategyB(const ConcreteStrategyB &) = delete;
  ConcreteStrategyB(ConcreteStrategyB &&) = delete;
  ConcreteStrategyB operator=(const ConcreteStrategyB &) = delete;
  ConcreteStrategyB operator=(ConcreteStrategyB &&) = delete;

  /**
   * @brief Constructor
   *
   * @param string String
   */
  explicit ConcreteStrategyB(const char *string) : internal_char_(string){};

  /**
   * @brief Destructor
   */
  ~ConcreteStrategyB() = default;

  /**
   * @brief Execute
   *
   * @param data Data
   */
  void execute(const char *data = nullptr) const override {
    fprintf(stdout, "Doing something using Strategy B - Internal data \"%s\"",
            internal_char_);
  }

 private:
  /**
   * @brief Internal string
   */
  const char *internal_char_{nullptr};
};

void client_run() {
  {
    Context context(nullptr);
    std::cout << "Client: Running without Strategy.\n";
    context.do_something();
    std::cout << "\n";
  }

  {
    Context context(std::make_unique<ConcreteStrategyA>(100));
    std::cout << "Client: Running using Strategy A.\n";
    context.do_something();
    std::cout << "\n";

    std::cout << "Client: Running using Strategy B.\n";
    context.set_strategy(std::make_unique<ConcreteStrategyB>("abcd"));
    context.do_something();
  }
}

int main() {
  client_run();
  return 0;
}
