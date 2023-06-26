#ifndef SOIL_SIGNAL_SPECTRUM_HPP
#define SOIL_SIGNAL_SPECTRUM_HPP

#include "Eigen/Dense"
#include "soil_export.h"

namespace soil {
namespace signal {

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
    Spectrum(const Eigen::VectorXd &freq, const Eigen::VectorXcd &values);
    /**
     * @brief Construct a new Spectrum object
     *
     * @param [in] freq frequency axis
     * @param [in] values value axis
     *
     * @note Throw runtime error if point count is less than 2 or sizes of two
     *       axes don't match.
     */
    Spectrum(Eigen::VectorXd &&freq, Eigen::VectorXcd &&values);
    /**
     * @brief Construct a new Spectrum object
     *
     * @param [in] f0 beginning of frequency axis, unit: Hz
     * @param [in] f_step frequency step, unit: Hz
     * @param [in] values value axis
     *
     * @note Throw runtime error if size of value axis is less than 2
     */
    Spectrum(double f0, double f_step, const Eigen::VectorXcd &values);

    Eigen::Index Count() const;/**< point count */
    const Eigen::VectorXd &Frenquencies() const;/**< frequency axis */
    const Eigen::VectorXcd &Values() const;/**< value axis */

private:
    SpectrumPriv *priv;
};

} // namespace signal
} // namespace soil

#endif // SOIL_SIGNAL_SPECTRUM_HPP
