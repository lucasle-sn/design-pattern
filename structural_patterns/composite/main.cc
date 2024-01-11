#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <string>

/**
 * @brief Composite is a "structural design pattern" that lets you compose
 * objects into tree structures and then work with these structures as if they
 * were individual object.
 *
 * # Problem: Having 2 types of objects: "Products" and "Boxes". "Boxes" may
 * contain multi "Products". The expectation is to treat "Boxes" and "Products"
 * uniformly, e.g. <get_price()>.
 *
 * # Structure: refers to "composite_sttructure.png"
 *
 * # Applicability:
 *  + When you have to implement a tree-like object structure.
 *  + When you want to treat both simple and complex elements uniformly.
 * E.g. A tree has <branches> and <leaves>. <branches> has <brnaches> and
 * <leaves>. -> <branches> and <leaves> are treated equally.
 *
 * # Pros & cons:
 *  + Pros: - work with complex tree structures more conveniently, using
 *            polymophism and recursion.
 *          - align with "Open/Closed principle"
 *  + Cons: - be difficult to provide a common interface. e.g. <branches> &
 *            <leaves> are different.
 */

/**
 * # Implementation:
 *
 * Step 1: The Component interface describes operations that are common to both
 * simple and complex elements of the tree.
 *
 * Step 2: The Leaf is a basic element of a tree that doesn’t have sub-elements.
 * Usually, leaf components end up doing most of the real work, since they don’t
 * have anyone to delegate the work to.
 *
 * Step 3: The Container (aka composite) is an element that has sub-elements:
 * leaves or other containers. A container doesn’t know the concrete classes of
 * its children. It works with all sub-elements only via the component
 * interface. Upon receiving a request, a container delegates the work to its
 * sub-elements, processes intermediate results and then returns the final
 * result to the client.
 *
 * Step 4: The Client works with all elements through the component interface.
 * As a result, the client can work in the same way with both simple or complex
 * elements of the tree.
 */

//////////////////////////////////////////////////////////////////////

/**
 * @brief The base Component class declares common operations for both simple
 * and complex objects of a composition.
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
   * @note In some cases, it would be beneficial to define the child-management
   * operations right in the base Component class. This way, you won't need to
   * expose any concrete component classes to the client code, even during the
   * object tree assembly. The downside is that these methods will be empty for
   * the leaf-level components. => CONS
   */
  virtual void add(Component *component) {}
  virtual void remove(Component *component) {}

  /**
   * @brief Check if object is composite
   */
  virtual bool is_composite() const { return false; }

  /**
   * @note The base Component may implement some default behavior or leave it to
   * concrete classes (by declaring the method containing the behavior as
   * "abstract").
   */
  virtual std::string execute() const = 0;

  /**
   * @brief Parent setter
   *
   * @param parent Parent
   */
  void set_parent(Component *parent) { this->parent_ = parent; }

  /**
   * @brief Parent getter
   *
   * @return Component*
   */
  Component *get_parent() const { return this->parent_; }

 protected:
  /**
   * @brief Parent component
   *
   * @note Optionally, the base Component can declare an interface for setting
   * and accessing a parent of the component in a tree structure. It can also
   * provide some default implementation for these methods.
   */
  Component *parent_;
};

/**
 * @brief The Leaf class represents the end objects of a composition. A leaf
 * can't have any children.
 *
 * Usually, it's the Leaf objects that do the actual work, whereas Composite
 * objects only delegate to their sub-components.
 */
class Leaf : public Component {
 public:
  /**
   * @brief Constructor
   */
  Leaf() = default;

  Leaf(const Leaf &) = delete;
  Leaf(Leaf &&) = delete;
  Leaf operator=(const Leaf &) = delete;
  Leaf operator=(Leaf &&) = delete;

  /**
   * @brief Destructor
   */
  ~Leaf() = default;

  /**
   * @brief Override the implementation of operation()
   *
   * @return std::string
   */
  std::string execute() const override { return "Leaf"; }
};

/**
 * @brief The Composite class represents the complex components that may have
 * children.
 *
 * Usually, the Composite objects delegate the actual work to their children and
 * then "sum-up" the result.
 */
class Composite : public Component {
 public:
  /**
   * @brief Constructor
   */
  Composite() = default;

  Composite(const Composite &) = delete;
  Composite(Composite &&) = delete;
  Composite operator=(const Composite &) = delete;
  Composite operator=(Composite &&) = delete;

  /**
   * @brief Destructor
   */
  ~Composite() = default;

  /**
   * @brief add child to composite
   *
   * @note A composite object can add or remove other components (both simple or
   * complex) to or from its child list.
   */
  void add(Component *component) override {
    this->children_.push_back(component);
    component->set_parent(this);
  }

  /**
   * @brief remove child from the composite
   *
   * @note Have in mind that this method removes the pointer to the list but
   * doesn't frees the memory, you should do it manually or better use smart
   * pointers.
   */
  void remove(Component *component) override {
    children_.remove(component);
    component->set_parent(nullptr);
  }

  /**
   * @brief Check if the object is composite
   *
   * @return bool
   */
  bool is_composite() const override { return true; }

  /**
   * @note The Composite executes its primary logic in a particular way. It
   * traverses recursively through all its children, collecting and summing
   * their results. Since the composite's children pass these calls to their
   * children and so forth, the whole object tree is traversed as a result.
   */
  std::string execute() const override {
    std::string result;
    for (const auto &c : children_) {
      if (c == children_.back()) {
        result += c->execute();
      } else {
        result += c->execute() + "+";
      }
    }
    return "Branch(" + result + ")";
  }

 protected:
  /**
   * @brief List of children
   */
  std::list<Component *> children_;
};

/**
 * @brief The client code works with all of the components via the base
 * interface.
 */
void run_client(Component *component) {
  std::cout << "RESULT: " << component->execute();
}

int main() {
  /**
   * Simple component (leaf)
   */
  auto simple = std::make_unique<Leaf>();
  std::cout << "Client: I've got a simple component:\n";
  run_client(simple.get());
  std::cout << "\n\n";

  /**
   * Complex composites.
   */
  auto leaf_1 = std::make_shared<Leaf>();
  auto leaf_2 = std::make_shared<Leaf>();
  auto leaf_3 = std::make_shared<Leaf>();

  auto branch_1 = std::make_shared<Composite>();
  branch_1->add(leaf_1.get());
  branch_1->add(leaf_2.get());

  auto branch_2 = std::make_shared<Composite>();
  branch_2->add(leaf_3.get());

  auto tree = std::make_shared<Composite>();
  tree->add(branch_1.get());
  tree->add(branch_2.get());

  std::cout << "Client: Now I've got a composite tree:\n";
  run_client(tree.get());
  std::cout << "\n\n";

  return 0;
}
