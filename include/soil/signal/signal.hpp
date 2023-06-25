#ifndef SOIL_SIGNAL_SIGNAL_HPP
#define SOIL_SIGNAL_SIGNAL_HPP

#include <string>
#include <vector>
#include <any>

#include "soil_export.h"
#include "soil/signal/wavement.hpp"
#include "soil/util/parameterized.hpp"

namespace soil {
namespace signal {

/**
 * @brief Abstract signal interface
 *
 * This interface can't be instantiated directly, user should implement all
 * methods in a derived class.
 *
 * The interface is designed in three ascepts:
 * 1. every signal has a name, such name can be only assigned by derived class
 *    in constructor;
 * 2. a signal can have any number of parameters, the derived class use
 *    `prepareParameter` method to initialize a parameter, and implement
 *    `checkParameter` method to guard parameter setting;
 * 3. most important function of a signal is to generate a wavement by giving a
 *    referee, such function is performed by `get` method which should be
 *    implemented in derived class.
 *
 * The necessary implemetations in derived class:
 * 1. constructor using protected `Signal(name)` to define name, and using
 *    `prepareParameter` to define parameters;
 * 2. `keys` method to specify keys of values in generated wavement;
 * 3. `get` method to achieve wavement generation;
 * 4. `checkParameter` method to guard parameter setting, the default
 *    implementation only concerns the value types.
 */
class SOIL_EXPORT Signal : public util::Parameterized {
  public:
    /** Get keys of all columns */
    virtual std::vector<std::string> Keys() const = 0;
    /** Generate a wavement according to given referee */
    virtual Wavement get(const Sequence &referee) const = 0;

  protected:
    /** Constructor with name assigning */
    explicit Signal(const std::string &name);
};

} // namespace signal
} // namespace soil

#endif // SOIL_SIGNAL_SIGNAL_HPP
