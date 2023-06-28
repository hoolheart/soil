#ifndef SOIL_SIGNAL_CONVERT_HPP
#define SOIL_SIGNAL_CONVERT_HPP

#include <optional>

#include "soil_export.h"
#include "soil/signal/wavement.hpp"
#include "soil/signal/spectrum.hpp"

namespace soil {
namespace signal {

/**
 * @brief Fourier transformation
 *
 * Convert time-domain wavement to frequency-domain spectrum.
 * Referee of input wavement must be monotonous sequence of time
 * with fixed sample rate.
 */
std::optional<Spectrum> SOIL_EXPORT wavementToSpectrum(const Wavement &w);

/**
 * @brief Inverse fourier transformation
 *
 * Convert frequency-domain spectrum to time-domain wavement.
 * Frequency axis of input spectrum must be monotonous sequence
 * with fixed interval.
 */
std::optional<Wavement> SOIL_EXPORT spectrumToWavement(const Spectrum &spec);

} // namespace signal
} // namespace soil

#endif // SOIL_SIGNAL_CONVERT_HPP
