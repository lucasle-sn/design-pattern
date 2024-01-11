#include <cstdio>

/**
 * @brief Template Method is a behavioral design pattern that defines the
 * skeleton of an algorithm in the superclass but lets subclasses override
 * specific steps of the algorithm without changing its structure.
 *
 * # Problem: Creating an application that analyses documents, and extracts
 * data. These document are in various formats (PDF, DOC, CSV, ...). For
 * different types of document formats, the algorithms to analyse useful
 * information are the same, but data extraction and data parsing are different.
 * => Create a Template method (class) that breaks algorithm into many steps,
 * and modifies the bahaviors based on concrete classes.
 *
 * # Applicability:
 *  + When letting clients to extend only particular steps of an algorithm, not
 * the whole algorithm.
 *  + When having several classes with almost identical algorithm.
 *
 * # Pros & Cons:
 *  + Pros: - Override certain parts of a large algorithm.
 *          - Put duplicate code in super class.
 *  + Cons: - limited by the provided algorithm.
 *          - Violates "Liskov Substitution Principle" (when assuming pre/post
 *            condition of each step)
 */

/**
 * # Implementation:
 *
 * Step 1: The Abstract Class declares methods that act as steps of an
 * algorithm, as well as the actual template method which calls these methods in
 * a specific order. The steps may either be declared abstract or have some
 * default implementation.
 *
 * Step 2: Concrete Classes can override all of the steps, but not the template
 * method itself.
 */

////////////////////////////////////////////////////////////

/**
 * @brief AbstractClass name
 */
static const char *cAbstractClassName{"AbstractClass"};

/**
 * @brief ConcreteClass1 name
 */
static const char *cConcreteClass1Name{"ConcreteClass1"};

/**
 * @brief ConcreteClass2 name
 */
static const char *cConcreteClass2Name{"ConcreteClass2"};

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
    fprintf(stdout, "%s: Implements step 1\n", cAbstractClassName);
  }
  void execute_step_2() const {
    fprintf(stdout, "%s: Implements step 2\n", cAbstractClassName);
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
 * of step 5 & 6
 */
class ConcreteClass1 : public AbstractClass {
 protected:
  /**
   * Override step 3 4 (required)
   */
  void execute_step_3() const override {
    fprintf(stdout, "%s: Implements step 3\n", cConcreteClass1Name);
  }

  void execute_step_4() const override {
    fprintf(stdout, "%s: Implements step 4\n", cConcreteClass1Name);
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
    fprintf(stdout, "%s: Implements step 3\n", cConcreteClass2Name);
  }

  void execute_step_4() const override {
    fprintf(stdout, "%s: Implements step 4\n", cConcreteClass2Name);
  }

  /**
   * Override step 5
   */
  void execute_step_5() const override {
    fprintf(stdout, "%s: Implements step 5\n", cConcreteClass2Name);
  }
};

/**
 * The client code calls the template method to execute the algorithm. Client
 * code does not have to know the concrete class of an object it works with, as
 * long as it works with objects through the interface of their base class.
 */
void run_client(AbstractClass *obj) { obj->execute_algorithm(); }

int main() {
  fprintf(stdout, "Same client code can work with different subclasses:\n");
  ConcreteClass1 concrete_class_1 = ConcreteClass1();
  run_client(&concrete_class_1);
  fprintf(stdout, "\n");

  fprintf(stdout, "Same client code can work with different subclasses:\n");
  ConcreteClass2 concrete_class_2 = ConcreteClass2();
  run_client(&concrete_class_2);

  return 0;
}
