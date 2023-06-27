#ifndef SOIL_SIGNAL_TUNER_HPP
#define SOIL_SIGNAL_TUNER_HPP

#include <memory>

#include "soil_export.h"
#include "soil/signal/spectrum.hpp"
#include "soil/util/parameterized.hpp"
#include "soil/signal/processor.hpp"

namespace soil {
namespace signal {

/**
 * @brief Abstract interface of any tuner on frequency spectrum
 *
 * Any tuner is a parameterized object. The subclasses should do 3
 * implementations:
 * - use protected constructor to specify name
 * - use `prepareParameter` define specific parameters, and use `checkParameter`
 *   if necessary
 * - implement `tune` function to define behavior
 */
class SOIL_EXPORT Tuner : public util::Parameterized {
public:
    /**
     * @brief tuning process, must be implemented
     *
     * @param [in] spec input spectrum
     * @return tuned spectrum
     */
    virtual Spectrum tune(const Spectrum &spec) const = 0;

protected:
    explicit Tuner(const std::string &name);
};

/** Shared pointer of tuner */
using Tuner_ptr = std::shared_ptr<Tuner>;
/** Use tuner as S-Parameter */
using SParameter = Tuner;

class MeasuredSPriv;

/** S-Parameter with measured frequency characteristics */
class SOIL_EXPORT MeasuredSParameter : SParameter {
public:
    /**
     * @brief Construct a new Measured S Parameter object
     *
     * @param [in] f0 beginning frequency of measured data
     * @param [in] f_step frequency step, >1e-9
     * @param [in] ch measured characteristics
     */
    explicit MeasuredSParameter(double f0, double f_step,
                                const Characteristics &ch);
    ~MeasuredSParameter();
    Spectrum tune(const Spectrum &spec) const;

private:
    MeasuredSPriv *priv;
};

/** Signal channel considered as a frequency tuner */
class SOIL_EXPORT TunerChannel : public Channel {
public:
    /**
     * @brief Construct a new Tuner Channel object
     *
     * @param [in] tuner default tuner shared pointer
     */
    explicit TunerChannel(const Tuner_ptr &tuner);

    /** Change tuner */
    void setTuner(const Tuner_ptr &tuner);

    Wavement via(const Wavement &w) const;

private:
    Tuner_ptr tuner;
};

} // namespace signal
} // namespace soil

#endif // SOIL_SIGNAL_TUNER_HPP
