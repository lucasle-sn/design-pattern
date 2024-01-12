#include <cstddef>
#include <cstdio>
#include <memory>

/**
 * # Implementation:
 *
 * Builder focuses on constructing complex objects step by step. Abstract
 * Factory specializes in creating families of related objects. Abstract Factory
 * returns the product immediately, whereas Builder lets you run some additional
 * construction steps before fetching the product.
 *
 *
 */

namespace {

enum class Engine {
  V4,
  V6,
  V12,
};

const char *name(Engine engine) {
  switch (engine) {
    case Engine::V4:
      return "V4";
    case Engine::V6:
      return "V6";
    case Engine::V12:
      return "V12";
    default:
      nullptr;
  }
}

class Car {
 public:
  explicit Car(size_t seat, Engine engine, bool trip_computer, bool gps)
      : seat_number_(seat),
        engine_(engine),
        trip_computer_enabled_(trip_computer),
        gps_enabled_(gps){};

  Car() = delete;
  Car(const Car &) = delete;
  Car(Car &&) = delete;
  Car operator=(const Car &) = delete;
  Car operator=(Car &&) = delete;

  ~Car() = default;

  size_t get_seat_number() { return seat_number_; }
  Engine get_engine() { return engine_; }
  size_t get_trip_computer_enabled() { return trip_computer_enabled_; }
  size_t get_gps_enabled() { return gps_enabled_; }

 private:
  size_t seat_number_;
  Engine engine_;
  bool trip_computer_enabled_;
  bool gps_enabled_;
};

class Manual {};

class Builder {
 public:
  Builder() = default;
  Builder(const Builder &) = delete;
  Builder(Builder &&) = delete;

  virtual ~Builder() = default;

  virtual void reset() = 0;

  virtual void assemble_seat() = 0;

  virtual void assemble_engine() = 0;

  virtual void assemble_trip_computer() = 0;

  virtual void assemble_gps() = 0;
};

class CarBuilder : public Builder {
 public:
  explicit CarBuilder(size_t seat, Engine engine, bool trip_computer,
                      bool gps) {
    car_ = std::make_unique<Car>(seat, engine, trip_computer, gps);
  };

  CarBuilder() = delete;
  CarBuilder(const CarBuilder &) = delete;
  CarBuilder(CarBuilder &&) = delete;
  CarBuilder operator=(const CarBuilder &) = delete;
  CarBuilder operator=(CarBuilder &&) = delete;

  ~CarBuilder() = default;

  void reset() override{};

  void assemble_seat() override {
    if (!car_) {
      return;
    }
    fprintf(stdout, "Assembling %zu seats\n", car_->get_seat_number());
  }

  void assemble_engine() override {
    if (!car_) {
      return;
    }
    fprintf(stdout, "Assembling engine type %s\n", name(car_->get_engine()));
  }

  void assemble_trip_computer() override {
    if (!car_) {
      return;
    }
    if (car_->get_trip_computer_enabled()) {
      fprintf(stdout, "Assembling trip computer\n");
    }
  }

  void assemble_gps() override {
    if (!car_) {
      return;
    }
    if (car_->get_gps_enabled()) {
      fprintf(stdout, "Assembling GPS\n");
    }
  }

 private:
  std::unique_ptr<Car> car_{nullptr};
};

class Director {
 public:
  void make_mvp(Builder *builder) {
    builder->assemble_seat();
    builder->assemble_engine();
  }

  void make_full_feature(Builder *builder) {
    builder->assemble_seat();
    builder->assemble_engine();
    builder->assemble_trip_computer();
    builder->assemble_gps();
  }
};

void run_client() {
  {
    auto director = std::make_unique<Director>();
    auto sedan_ptr = std::make_unique<CarBuilder>(5, Engine::V4, true, false);
    director->make_mvp(sedan_ptr.get());
    fprintf(stdout, "\n");

    director->make_full_feature(sedan_ptr.get());
  }
}

}  // namespace

int main() {
  run_client();
  return 0;
}
