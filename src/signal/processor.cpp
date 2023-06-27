
#include "soil/signal/processor.hpp"

namespace soil {
namespace signal {

Processor::Processor(const std::string &name) : util::Parameterized(name) {}

IdealChannel::IdealChannel() : Channel("ideal_channel") {}

Wavement IdealChannel::via(const Wavement &w) const { return w; }

LinearChannel::LinearChannel(double delay, double coeff, double offset)
    : Channel("linear_channel") {
    prepareParameter("delay", delay);
    prepareParameter("coeff", coeff);
    prepareParameter("offset", offset);
}

Wavement LinearChannel::via(const Wavement &w) const {
    double delay = ParameterAs("delay", 0.0), coeff = ParameterAs("coeff", 1.0),
           offset = ParameterAs("offset", 0.0);
    auto referee = w.Referee();
    auto keys = w.Keys();
    for (auto &v : referee) {
        v += delay;
    }
    Wavement post(referee);
    for (auto key: keys) {
        Sequence values = w.Values(key);
        for (auto &v: values) {
            v = v * coeff + offset;
        }
        post.setValues(key, values);
    }
    return post;
}

} // namespace signal
} // namespace soil
