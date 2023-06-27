#ifndef SOIL_UTIL_PARAMETERIZED_HPP
#define SOIL_UTIL_PARAMETERIZED_HPP

#include <string>
#include <vector>
#include <any>

#include "soil_export.h"

namespace soil {
namespace util {

class ParameterizedPriv;

/**
 * @brief Abstract interface with parameters
 *
 * This interface can't be instantiated directly, user should implement all
 * methods in a derived class.
 *
 * The interface is designed in three ascepts:
 * 1. every object has a name, such name can be only assigned by derived class
 *    in constructor;
 * 2. a parameterized class can have any number of parameters, the derived class
 *    use `prepareParameter` method to initialize a parameter, and implement
 *    `checkParameter` method to guard parameter setting.
 *
 * The necessary implemetations in derived class:
 * 1. constructor using protected `Parameterized(name)` to define name, and
 *    using `prepareParameter` to define parameters;
 * 2. `checkParameter` method to guard parameter setting, the default
 *    implementation only concerns the value types.
 */
class SOIL_EXPORT Parameterized {
public:
    /** Destructor*/
    ~Parameterized();

    /** Get name */
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
    template <typename T>
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

protected:
    /** Constructor with name assigning */
    explicit Parameterized(const std::string &name);

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
    ParameterizedPriv *priv;
};

} // namespace util
} // namespace soil

#endif // SOIL_UTIL_PARAMETERIZED_HPP
