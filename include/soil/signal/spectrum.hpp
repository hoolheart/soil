#ifndef SOIL_SIGNAL_SPECTRUM_HPP
#define SOIL_SIGNAL_SPECTRUM_HPP

#include "Eigen/Dense"
#include "soil_export.h"
#include "soil/signal/wavement.hpp"

namespace soil {
namespace signal {

/** frequency characteristics, using Eigen complex vector */
using Characteristics = Eigen::VectorXcd;

class SpectrumPriv;

/**
 * @brief Frequency spectrum
 *
 * Frenquency axis is a double vector, value axis is a complex vector.
 */
class SOIL_EXPORT Spectrum {
public:
    /**
     * @brief Construct a new Spectrum object
     *
     * @param [in] freq frequency axis
     * @param [in] values value axis
     *
     * @note Throw runtime error if point count is less than 2 or sizes of two
     *       axes don't match.
     */
    Spectrum(const Sequence &freq, const Characteristics &values);
    /**
     * @brief Construct a new Spectrum object
     *
     * @param [in] freq frequency axis
     * @param [in] values value axis
     *
     * @note Throw runtime error if point count is less than 2 or sizes of two
     *       axes don't match.
     */
    Spectrum(Sequence &&freq, Characteristics &&values);
    /**
     * @brief Construct a new Spectrum object
     *
     * @param [in] f0 beginning of frequency axis, unit: Hz
     * @param [in] f_step frequency step, unit: Hz
     * @param [in] values value axis
     *
     * @note Throw runtime error if size of value axis is less than 2
     */
    Spectrum(double f0, double f_step, const Characteristics &values);

    Size Count() const;                    /**< point count */
    const Sequence &Frenquencies() const;  /**< frequency axis */
    const Characteristics &Values() const; /**< value axis */

private:
    SpectrumPriv *priv;
};

} // namespace signal
} // namespace soil

#endif // SOIL_SIGNAL_SPECTRUM_HPP
