#define _USE_MATH_DEFINES
#include <functional>
#include <math.h>
#include <unordered_map>

#include "soil/signal/signal.hpp"

using namespace soil::util;

namespace soil {
namespace signal {

Signal::Signal(const std::string &name) : Parameterized(name) {}

struct FunctionalSignalPriv {
    std::unordered_map<std::string, std::function<double(double)>> functions;
};

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

std::vector<std::string> FunctionalSignal::Keys() const {
    std::vector<std::string> keys;
    keys.reserve(priv->functions.size());
    for (auto [key, _] : priv->functions) {
        keys.push_back(key);
    }
    return keys;
}

Wavement FunctionalSignal::get(const Sequence &referee) const {
    Wavement w(referee);
    for (auto [key, func] : priv->functions) {
        Sequence values = referee;
        for (double &val : values) {
            val = func(val);
        }
        w.setValues(key, values);
    }
    return w;
}

FixedSignal::FixedSignal(double level) : Signal("fixed") {
    prepareParameter("level", level);
}

std::vector<std::string> FixedSignal::Keys() const { return {"amp"}; }

Wavement FixedSignal::get(const Sequence &referee) const {
    Wavement w(referee);
    w.setValues("amp",
                Sequence::Ones(referee.size()) * ParameterAs("level", 0.0));
    return w;
}

LinearSignal::LinearSignal(double coeff, double offset) : Signal("linear") {
    prepareParameter("coeff", coeff);
    prepareParameter("offset", offset);
}

std::vector<std::string> LinearSignal::Keys() const { return {"amp"}; }

Wavement LinearSignal::get(const Sequence &referee) const {
    Wavement w(referee);
    double coeff = ParameterAs("coeff", 1.0),
           offset = ParameterAs("offset", 0.0);
    Sequence values = referee;
    for (double &value : values) {
        value = value * coeff + offset;
    }
    w.setValues("amp", values);
    return w;
}

PeriodicalSignal::PeriodicalSignal(const std::string &name, double freq)
    : Signal(name) {
    prepareParameter("freq", freq);
}

SineSignal::SineSignal(double freq, double phase, double A,
                       double offset)
    : PeriodicalSignal("sine", freq) {
    prepareParameter("phase", phase);
    prepareParameter("A", A);
    prepareParameter("offset", offset);
}

std::vector<std::string> SineSignal::Keys() const { return {"amp"}; }

Wavement SineSignal::get(const Sequence &referee) const {
    Wavement w(referee);
    double omega = 2.0 * M_PI * ParameterAs("freq", 50.0),
           phase = ParameterAs("phase", 0.0), A = ParameterAs("A", 1.0),
           offset = ParameterAs("offset", 0.0);
    Sequence values = referee;
    for (double &value : values) {
        value = A * sin(omega * value + phase) + offset;
    }
    w.setValues("amp", values);
    return w;
}

ComplexSineSignal::ComplexSineSignal(double freq, double phase, double A)
    : PeriodicalSignal("complex_sine", freq) {
    prepareParameter("phase", phase);
    prepareParameter("A", A);
}

std::vector<std::string> ComplexSineSignal::Keys() const {
    return {"real", "imag"};
}

Wavement ComplexSineSignal::get(const Sequence &referee) const {
    Wavement w(referee);
    double omega = 2.0 * M_PI * ParameterAs("freq", 50.0),
           phase = ParameterAs("phase", 0.0), A = ParameterAs("A", 1.0);
    Sequence real = referee, imag = referee;
    for (double &value: real) {
        value = A * cos(omega * value + phase);
    }
    for (double &value: imag) {
        value = A * sin(omega * value + phase);
    }
    w.setValues("real", real);
    w.setValues("imag", imag);
    return w;
}

PulseSignal::PulseSignal(const std::string &name, double begin, double duration)
    : Signal(name) {
    prepareParameter("begin", begin);
    prepareParameter("duration", ((duration > 0.0) ? duration : 1.0));
}

bool PulseSignal::checkParameter(const std::string &name,
                                 const std::any &current,
                                 const std::any &next) const {
    if (name == "duration") {
        return next.type() == typeid(double) &&
               std::any_cast<double>(next) > 0.0;
    }
    return Signal::checkParameter(name, current, next);
}

} // namespace signal
} // namespace soil
