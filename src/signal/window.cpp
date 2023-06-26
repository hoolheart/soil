
#include "soil/signal/window.hpp"

namespace soil {
namespace signal {

Window::Window(const std::string &name, double begin, double duration,
               double max_amp)
    : Processor(name) {
    prepareParameter("begin", begin);
    prepareParameter("duration", (duration > 0) ? duration : 1.0);
    prepareParameter("max_amp", max_amp);
}

bool Window::checkParameter(const std::string &name, const std::any &current,
                            const std::any &next) const {
    if (name == "duration") {
        return (next.type() == typeid(double)) &&
               (std::any_cast<double>(next) > 0.0);
    }
    return Processor::checkParameter(name, current, next);
}

} // namespace signal
} // namespace soil
