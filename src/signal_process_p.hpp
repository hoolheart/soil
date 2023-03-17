#ifndef SOIL_SIGNAL_PROCESS_PRIV_HPP
#define SOIL_SIGNAL_PROCESS_PRIV_HPP

#include <string>
#include <unordered_map>
#include "Eigen/Dense"

struct WavementPriv {
    Eigen::VectorXd referee;
    std::unordered_map<std::string, Eigen::VectorXd> values;
};

struct SignalPriv {
    std::string name;
    std::unordered_map<std::string, double> parameters;
};

#endif // SOIL_SIGNAL_PROCESS_PRIV_HPP
