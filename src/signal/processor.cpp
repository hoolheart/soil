
#include "soil/signal/processor.hpp"

namespace soil {
namespace signal {

Processor::Processor(const std::string &name): util::Parameterized(name) {}

IdealChannel::IdealChannel(): Channel("ideal_channel") {}

Wavement IdealChannel::via(const Wavement &w) const { return w; }

} // namespace signal
} // namespace soil
