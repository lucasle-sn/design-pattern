#include <cstdio>
#include <memory>

/**
 * @brief "Facade" is a structural design pattern that provides a simplified
 * interface to a library, a framework, or any other complex set of classes.
 *
 * # Problem: A shop to place a phone order, requires warehouse, payment, tax,
 * packaging, delivery, etc. A super class to all services is essential.
 *
 * # Structure: refers to "facade_structure.png"
 *
 * # Applicability:
 *  + Need a limited but stright forward interface to complex subsystems.
 *  + When want to structure a system into layers.
 *
 * # Pros & Cons:
 *  + Pros: - Isolate from complex subsystems.
 *  + Cons: - Facade becomes superclass (couples many classes)
 */

/**
 * # Implementation:
 *
 * Step 1: The Facade provides convenient access to a particular part of the
 * subsystem’s functionality. It knows where to direct the client’s request and
 * how to operate all the moving parts.
 *
 * Step 2: An Additional Facade class can be created to prevent polluting a
 * single facade with unrelated features that might make it yet another complex
 * structure. Additional facades can be used by both clients and other facades.
 *
 * Step 3: The Complex Subsystem consists of dozens of various objects. To make
 * them all do something meaningful, you have to dive deep into the subsystem’s
 * implementation details, such as initializing objects in the correct order and
 * supplying them with data in the proper format. Subsystem classes aren’t aware
 * of the facade’s existence. They operate within the system and work with each
 * other directly.
 *
 * Step 4: The Client uses the facade instead of calling the subsystem objects
 * directly.
 */

//////////////////////////////////////////////////////////////////////

namespace {

/**
 * @brief Subsystem A string
 */
static const char *cSubsystemAName{"SubsystemA"};

/**
 * @brief Subsystem B string
 */
static const char *cSubsystemBName{"SubsystemB"};

/**
 * @brief SubsystemA
 *
 * The Subsystem can accept requests either from the facade or client directly.
 * In any case, to the Subsystem, the Facade is yet another client, and it's not
 * a part of the Subsystem.
 */
class SubsystemA {
 public:
  /**
   * @brief Constructor
   */
  SubsystemA() = default;

  SubsystemA(const SubsystemA &) = delete;
  SubsystemA(SubsystemA &&) = delete;
  SubsystemA operator=(const SubsystemA &) = delete;
  SubsystemA operator=(SubsystemA &&) = delete;

  /**
   * @brief Destructor
   */
  ~SubsystemA() = default;

  /**
   * @brief Initialize
   */
  void init() const { fprintf(stdout, "%s: Initialized.\n", cSubsystemAName); }

  /**
   * @brief Deinitialize
   */
  void deinit() const {
    fprintf(stdout, "%s: Deinitialized.\n", cSubsystemAName);
  }

  /**
   * @brief Do something
   */
  void do_something() const {
    fprintf(stdout, "%s: Doing something.\n", cSubsystemAName);
  }
};

/**
 * @brief SubsystemB
 */
class SubsystemB {
 public:
  /**
   * @brief Constructor
   */
  SubsystemB() = default;

  SubsystemB(const SubsystemB &) = delete;
  SubsystemB(SubsystemB &&) = delete;
  SubsystemB operator=(const SubsystemB &) = delete;
  SubsystemB operator=(SubsystemB &&) = delete;

  /**
   * @brief Destructor
   */
  ~SubsystemB() = default;

  /**
   * @brief Initialize
   */
  void init() const { fprintf(stdout, "%s: Initialized.\n", cSubsystemBName); }

  /**
   * @brief Deinitialize
   */
  void deinit() const {
    fprintf(stdout, "%s: Deinitialized.\n", cSubsystemBName);
  }

  /**
   * @brief Do something
   */
  void do_something() const {
    fprintf(stdout, "%s: Doing something.\n", cSubsystemBName);
  }
};

/**
 * The Facade class provides a simple interface to the complex logic of one or
 * several subsystems. The Facade delegates the client requests to the
 * appropriate objects within the subsystem. The Facade is also responsible for
 * managing their lifecycle. All of this shields the client from the undesired
 * complexity of the subsystem.
 */
class Facade {
 public:
  /**
   * @brief Constructor
   *
   * @param has_subsystem_a Has subsystem A
   * @param has_subsystem_b Has subsystem B
   */
  Facade(bool has_subsystem_a, bool has_subsystem_b) {
    subsystem_a_ = has_subsystem_a ? std::make_unique<SubsystemA>() : nullptr;
    subsystem_b_ = has_subsystem_b ? std::make_unique<SubsystemB>() : nullptr;
  }

  Facade() = delete;
  Facade(const Facade &) = delete;
  Facade(Facade &&) = delete;
  Facade operator=(const Facade &) = delete;
  Facade operator=(Facade &&) = delete;

  /**
   * @brief Destructor
   */
  ~Facade() = default;

  /**
   * @brief Initialize
   */
  void init() const {
    fprintf(stdout, "Facade initializes subsystems:\n");
    if (subsystem_a_) {
      subsystem_a_->init();
    }
    if (subsystem_b_) {
      subsystem_b_->init();
    }
  }

  /**
   * @brief Deinitialize
   */
  void deinit() const {
    fprintf(stdout, "Facade deinitializes subsystems:\n");
    // Let's try to swap the order
    if (subsystem_a_) {
      subsystem_a_->deinit();
    }
    if (subsystem_b_) {
      subsystem_b_->deinit();
    }
  }

  /**
   * @brief Build facade
   */
  void build() {
    fprintf(stdout, "Facade' subsystems perform the action:\n");
    if (subsystem_a_) {
      subsystem_a_->do_something();
    }
    if (subsystem_b_) {
      subsystem_b_->do_something();
    }
  }

 protected:
  /**
   * @brief Subsystem A
   */
  std::unique_ptr<SubsystemA> subsystem_a_{nullptr};

  /**
   * @brief Subsystem B
   */
  std::unique_ptr<SubsystemB> subsystem_b_{nullptr};
};

/**
 * The client code works with complex subsystems through a simple interface
 * provided by the Facade. When a facade manages the lifecycle of the subsystem,
 * the client might not even know about the existence of the subsystem. This
 * approach lets you keep the complexity under control.
 */
void run_client(bool has_subsystem_a, bool has_subsystem_b) {
  auto facade = std::make_unique<Facade>(has_subsystem_a, has_subsystem_b);
  facade->init();
  facade->build();
  facade->deinit();
  fprintf(stdout, "\n");
}

}  // namespace

int main() {
  // Build facade with both subsystem A & B
  fprintf(stdout, "===== Building Facde with subsystem A & B =====\n");
  run_client(true, true);

  // Build facade with subsystem A only
  fprintf(stdout, "===== Building Facde with subsystem A only =====\n");
  run_client(true, false);

  return 0;
}
