#ifndef SOIL_SIGNAL_PROCESS_PRIV_HPP
#define SOIL_SIGNAL_PROCESS_PRIV_HPP

#include <string>
#include <unordered_map>
#include <functional>
#include "Eigen/Dense"

namespace soil {
namespace dsp {

struct WavementPriv {
    Eigen::VectorXd referee;
    std::unordered_map<std::string, Eigen::VectorXd> values;
};

struct SignalPriv {
    std::string name;
    std::unordered_map<std::string, double> parameters;
};

struct FunctionalSignalPriv {
    std::unordered_map<std::string, std::function<double(double)> > functions;
};

} // namespace dsp
} // namespace soil

#endif // SOIL_SIGNAL_PROCESS_PRIV_HPP
