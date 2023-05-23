#include "soil/dsp/common_signals.hpp"
#include "signal_process_p.hpp"

using namespace soil::dsp;

FunctionalSignal::FunctionalSignal(
    const std::unordered_map<std::string, SIG_FUNC> &functions)
    : Signal("functional") {
    priv = new FunctionalSignalPriv;
    for (auto [key, func] : functions) {
        if (key.size() > 0) {
            priv->functions[key] = func;
        }
    }
}

std::vector<std::string> FunctionalSignal::keys() const {
    std::vector<std::string> keys;
    keys.reserve(priv->functions.size());
    for (auto [key, _] : priv->functions) {
        keys.push_back(key);
    }
    return keys;
}

Wavement FunctionalSignal::get(const Eigen::VectorXd &referee) const {
    Wavement w(referee);
    for (auto [key, func] : priv->functions) {
        Eigen::VectorXd values = referee;
        for (double &val : values) {
            val = func(val);
        }
        w.setValues(key, values);
    }
    return w;
}

bool FunctionalSignal::checkParameter(
    const std::string &para_name, double para_value) const {
    return false;
}

FixedSignal::FixedSignal(double level): Signal("fixed") {
    prepareParameter("level", level);
}

std::vector<std::string> FixedSignal::keys() const {
    return {"amp"};
}

Wavement FixedSignal::get(const Eigen::VectorXd &referee) const {
    Wavement w(referee);
    w.setValues("amp",
                Eigen::VectorXd::Ones(referee.size()) * getParameter("level"));
    return w;
}

bool FixedSignal::checkParameter(
    const std::string &para_name, double para_value) const {
    if (para_name == "level") {
        return true;
    }
    return false;
}

LinearSignal::LinearSignal(double coeff, double offset) : Signal("linear") {
    prepareParameter("coeff", coeff);
    prepareParameter("offset", offset);
}

std::vector<std::string> LinearSignal::keys() const {
    return {"amp"};
}

Wavement LinearSignal::get(const Eigen::VectorXd &referee) const {
    Wavement w(referee);
    double coeff = getParameter("coeff"), offset = getParameter("offset");
    Eigen::VectorXd values = referee;
    for (double &value : values) {
        value = value * coeff + offset;
    }
    w.setValues("amp", values);
    return w;
}

bool LinearSignal::checkParameter(const std::string &para_name,
                                  double para_value) const {
    if ((para_name == "coeff") || (para_name == "offset")) {
        return true;
    }
    return false;
}
