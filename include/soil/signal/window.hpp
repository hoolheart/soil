#ifndef SOIL_SIGNAL_WINDOW_HPP
#define SOIL_SIGNAL_WINDOW_HPP

#include "soil_export.h"
#include "soil/signal/processor.hpp"

namespace soil {
namespace signal {

/**
 * @brief Abstract interface of signal window
 *
 * Subclass of #Processor with 3 additional parameters:
 * - begin --- begin timestamp of window, unit: s
 * - duration --- duration of window, unit: s, >0.0
 * - max_amp --- maximum amplitude
 */
class SOIL_EXPORT Window : public Processor {
protected:
    /**
     * @brief Construct a new Window object
     *
     * @param [in] name name passed to #soil::util::Parameterized
     * @param [in] begin default begin timestamp
     * @param [in] duration default duration, use 1.0 if value is not positive
     * @param [in] max_amp default maximum amplitude
     */
    explicit Window(const std::string &name, double begin = 0.0,
                    double duration = 1.0, double max_amp = 1.0);

    virtual bool checkParameter(const std::string &name,
                                const std::any &current,
                                const std::any &next) const;
};

} // namespace signal
} // namespace soil

#endif // SOIL_SIGNAL_WINDOW_HPP
