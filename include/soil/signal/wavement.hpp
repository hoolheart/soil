#ifndef SOIL_SIGNAL_WAVEMENT_HPP
#define SOIL_SIGNAL_WAVEMENT_HPP

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "Eigen/Dense"
#include "soil_export.h"

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
    int PointCount() const;
    /** Get count of columns in values */
    int ValueCount() const;

    /** Get referee vector */
    Sequence Referee() const;
    /** Get keys of all columns in values */
    std::vector<std::string> Keys() const;
    /**
     * Get vector of column with given key
     *
     * @param [in] key column key
     * @return column vector, empty vector if `key` non-exists
     */
    Sequence Values(const std::string &key) const;

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
    std::optional<Point> PointAt(int index) const;

private:
    WavementPriv *priv;
};

} // namespace signal
} // namespace soil

#endif // SOIL_SIGNAL_WAVEMENT_HPP
