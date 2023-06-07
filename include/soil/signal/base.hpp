#ifndef SOIL_SIGNAL_HPP
#define SOIL_SIGNAL_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
#include "soil_export.h"
#include "Eigen/Dense"

namespace soil {
namespace signal {

/** referee and value sequence, using Eigen double vector */
using Sequence = Eigen::VectorXd;

class WavementPriv;

/**
 * @brief Wavement composed by a referee and any number of values
 *
 * The referee is a vector, normally representing time sequence.
 * The values can contain any number of columns, each has a key and a vector.
 * The size of referee must be the same with the size of every column in values.
 */
class SOIL_EXPORT Wavement {
public:
    /** Constructor with empty referee */
    explicit Wavement();
    /** Constructor with given referee */
    explicit Wavement(const Sequence &referee);

    /**
     * @brief Set referee of wavement, it would clear values as well
     *
     * @param [in] referee referee vector
     */
    void setReferee(const Sequence &referee);
    /**
     * @brief Add a specific value column
     *
     * @param [in] key column key
     * @param [in] values column vector
     */
    void setValues(const std::string &key, const Sequence &values);

    /** Get count of point, a.k.a. size of referee or any column of values*/
    int point_count() const;
    /** Get count of columns in values */
    int value_count() const;

    /** Get referee vector */
    Sequence referee() const;
    /** Get keys of all columns in values */
    std::vector<std::string> keys() const;
    /**
     * Get vector of column with given key
     *
     * @param [in] key column key
     * @return column vector, empty vector if `key` non-exists
     */
    Sequence values(const std::string &key) const;

    /** Information of a single point in wavement */
    struct Point {
        double referee;
        std::unordered_map<std::string, double> values;
    };

    /**
     * Get a single point at given index
     *
     * @param [in] index point index
     * @return point information, nullopt if index is invalid
     */
    std::optional<Point> point(int index) const;

private:
    WavementPriv *priv;
};

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
 * 4. `checkParameter` method to guard parameter setting.
 */
class SOIL_EXPORT Signal {
public:
    /** Get signal name */
    std::string name() const;

    /** Get names of all parameters */
    std::vector<std::string> parameters() const;
    /**
     * @brief Get the parameter value according to given name
     *
     * @param [in] para_name parameter name
     * @param [in] def default value
     * @return parameter value, use default if parameter name invalid
     */
    double getParameter(const std::string &para_name, double def = 0.0) const;
    /**
     * @brief Set the parameter value
     *
     * @param [in] para_name parameter name
     * @param [in] para_value parameter value
     */
    void setParameter(const std::string &para_name, double para_value);

    /** Get keys of all columns */
    virtual std::vector<std::string> keys() const = 0;
    /** Generate a wavement according to given referee */
    virtual Wavement get(const Sequence &referee) const = 0;

protected:
    /** Constructor with name assigning */
    explicit Signal(const std::string &name);

    /**
     * @brief prepare a parameter, only the prepared one can be used
     *
     * @param [in] para_name parameter name
     * @param [in] init_value initial value
     */
    void prepareParameter(const std::string &para_name, double init_value);
    /**
     * @brief Guard the parameter setting
     *
     * @param [in] para_name paramter name
     * @param [in] para_value the value prepared to set to the parameter
     * @return whether the setting can be performed
     */
    virtual bool checkParameter(const std::string &para_name,
                                double para_value) const = 0;

private:
    SignalPriv *priv;
};

} // namespace signal
} // namespace soil

#endif // SOIL_SIGNAL_HPP
