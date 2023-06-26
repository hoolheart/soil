#ifndef SOIL_SIGNAL_PROCESSOR_HPP
#define SOIL_SIGNAL_PROCESSOR_HPP

#include "soil_export.h"
#include "soil/signal/wavement.hpp"
#include "soil/util/parameterized.hpp"

namespace soil {
namespace signal {

/**
 * @brief Abstract interface of any processor of wavement
 *
 * Any processor is a parameterized object. The subclasses should do 3
 * implementations:
 * - use protected constructor to specify name
 * - use `prepareParameter` define specific parameters, and use `checkParameter`
 *   if necessary
 * - implement `via` function to define procession of wavement
 */
class SOIL_EXPORT Processor : public util::Parameterized {
public:
    /**
     * @brief process wavement, must be implemented
     *
     * @param [in] w input wavement
     * @return wavement after precession
     */
    virtual Wavement via(const Wavement &w) const = 0;

protected:
    explicit Processor(const std::string &name);
};

/** Define abstract signal channel by using #Processor directly */
using Channel = Processor;

/** Ideal signal channel, which means no change occurs to the wavement */
class SOIL_EXPORT IdealChannel : public Channel {
public:
    explicit IdealChannel();
    Wavement via(const Wavement &w) const;
};

} // namespace signal
} // namespace soil

#endif // SOIL_SIGNAL_PROCESSOR_HPP
