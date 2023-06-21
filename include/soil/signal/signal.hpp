#ifndef SOIL_SIGNAL_SIGNAL_HPP
#define SOIL_SIGNAL_SIGNAL_HPP

#include <string>
#include <vector>
#include <any>

#include "soil_export.h"
#include "soil/signal/wavement.hpp"

namespace soil {
namespace signal {

class SignalPriv;

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
class SOIL_EXPORT Signal {
  public:
    /** Get signal name */
    std::string Name() const;

    /** Get names of all parameters */
    std::vector<std::string> ParameterNames() const;
    /**
     * @brief Get the parameter value according to given name
     *
     * @param [in] name parameter name
     * @param [in] def default value
     * @return parameter value, use default if parameter name invalid
     */
    std::any Parameter(const std::string &name,
                       const std::any &def = 0.0) const;
    /**
     * @brief Get the parameter value with given type according to given name
     *
     * @tparam T value type
     * @param [in] name parameter name
     * @param [in] def default value
     * @return parameter value, use default if parameter name invalid
     */
    template<typename T>
    T ParameterAs(const std::string &name, const T &def) const {
        return std::any_cast<T>(Parameter(name, std::make_any<T>(def)));
    }
    /**
     * @brief Set the parameter value
     *
     * @param [in] name parameter name
     * @param [in] value parameter value
     */
    bool setParameter(const std::string &name, const std::any &value);

    /** Get keys of all columns */
    virtual std::vector<std::string> Keys() const = 0;
    /** Generate a wavement according to given referee */
    virtual Wavement get(const Sequence &referee) const = 0;

  protected:
    /** Constructor with name assigning */
    explicit Signal(const std::string &name);

    /**
     * @brief prepare a parameter, only the prepared one can be used
     *
     * @param [in] name parameter name
     * @param [in] init_value initial value
     */
    void prepareParameter(const std::string &name, const std::any &init_value);
    /**
     * @brief Guard the parameter setting
     *
     * @param [in] name paramter name
     * @param [in] current current value of parameter
     * @param [in] next the value prepared to set to the parameter
     * @return whether the setting can be performed
     */
    virtual bool checkParameter(const std::string &name,
                                const std::any &current,
                                const std::any &next) const;

  private:
    SignalPriv *priv;
};

} // namespace signal
} // namespace soil

#endif // SOIL_SIGNAL_SIGNAL_HPP
