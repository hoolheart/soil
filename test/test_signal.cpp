#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

#include "soil/signal/common_signals.hpp"
#include "soil/signal/signal.hpp"

using namespace soil::signal;

const double TWO_PI = M_PI * 2.0;

class MySineSignal : public Signal {
public:
    explicit MySineSignal(double amp = 1.0, double freq = 50.0,
                          double phase = 0.0)
        : Signal("my_sine") {
        prepareParameter("amp", (amp > 0.0) ? amp : 1.0);
        prepareParameter("freq", (freq > 0.0) ? freq : 50.0);
        while (phase < 0.0) {
            phase += TWO_PI;
        }
        while (phase > TWO_PI) {
            phase -= TWO_PI;
        }
        prepareParameter("phase", phase);
    }

    std::vector<std::string> Keys() const { return {"amp"}; }

    Wavement get(const Eigen::VectorXd &referee) const {
        Wavement w(referee);
        Eigen::VectorXd amps = referee;
        double amp = ParameterAs("amp", 1.0), freq = ParameterAs("freq", 50.0),
               phase = ParameterAs("phase", 0.0);
        std::for_each(amps.begin(), amps.end(),
                      [amp, freq, phase](double &val) {
                          val = amp * sin(TWO_PI * freq * val + phase);
                      });
        w.setValues("amp", amps);
        return w;
    }

protected:
  bool checkParameter(const std::string &name, const std::any &current,
                      const std::any &next) const {
        if ((name == "amp") || (name == "freq")) {
            return next.type() == typeid(double) &&
                   std::any_cast<double>(next) > 0.0;
        }
        return Signal::checkParameter(name, current, next);
  }
};

class MyRectWindow : public PulseSignal {
public:
    explicit MyRectWindow(double begin = 0.0, double duration = 1.0,
                          double amp = 1.0)
        : PulseSignal("my_rect_window", begin, duration) {
        prepareParameter("amp", amp);
    }

    std::vector<std::string> Keys() const { return {"amp"}; }

    Wavement get(const Eigen::VectorXd &referee) const {
        Wavement w(referee);
        Eigen::VectorXd amps = referee;
        double amp = ParameterAs("amp", 1.0), begin = ParameterAs("begin", 0.0),
               end = begin + ParameterAs("duration", 1.0);
        for (auto &value : amps) {
            if ((value >= begin) && (value <= end)) {
                value = amp;
            }
            else {
                value = 0.0;
            }
        }
        w.setValues("amp", amps);
        return w;
    }
};

void print_parameters(const Signal &signal) {
    auto parameters = signal.ParameterNames();
    size_t cnt = parameters.size();
    if (cnt > 1) {
        std::cout << "There are " << cnt << " parameters" << std::endl;
    }
    else if (cnt > 0) {
        std::cout << "There is 1 parameter" << std::endl;
    }
    else {
        return;
    }
    for (const auto &key: parameters) {
        std::cout << "  - " << key << ": "
                  << signal.ParameterAs<double>(key, HUGE_VAL) << std::endl;
    }
}

void test_wavement(const Signal &signal, const Eigen::VectorXd &ts,
                   const std::vector<std::string> &expected) {
    auto wave = signal.get(ts);
    auto keys = wave.Keys();
    assert(keys.size() == expected.size());
    std::cout << "Generate a wavement:" << std::endl;
    for (auto key: expected) {
        assert(std::find(keys.begin(), keys.end(), key) != keys.end());
        auto col = wave.Values(key);
        std::cout << "  - " << key << ": ";
        for (auto val : col) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "Test of signal process" << std::endl;

    MySineSignal signal;
    auto keys = signal.Keys();
    std::cout << "There is/are " << keys.size() << " columns in signal "
              << signal.Name() << ":" << std::endl;
    for (auto key : keys) {
        std::cout << "- " << key << std::endl;
    }
    std::cout << std::endl;

    print_parameters(signal);
    std::cout << std::endl;

    signal.setParameter("freq", 10.0);
    auto freq = signal.ParameterAs("freq", 50.0);
    if (fabs(freq - 10.0) < 1e-9) {
        std::cout << "Succeed to change frequency to 10Hz" << std::endl;
    } else {
        std::cout << "Failed to change frequency to 10Hz (" << freq << ")"
                  << std::endl;
    }
    std::cout << std::endl;

    Eigen::VectorXd ts = Eigen::VectorXd::LinSpaced(21, 0.0, 0.2);
    auto w = signal.get(ts);
    std::cout << "Generate a wavement:" << std::endl;
    auto col = w.Values(keys[0]);
    std::for_each(col.begin(), col.end(),
                  [](auto &val) { std::cout << val << " "; });
    std::cout << std::endl;
    bool correct = true;
    for (int i = 0; i < 10; ++i) {
        if (fabs(col(i) - col(i + 10)) > 1e-9) {
            std::cout << i << "th data don't match:" << col(i) << col(i + 10)
                      << std::endl;
            correct = false;
            break;
        }
    }
    if (correct) {
        std::cout << "Frequency of generated wavement is correct" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Test functional signal" << std::endl;
    FunctionalSignal func_sig({{"linear", [](double t) { return t + 0.1; }},
                               {"square", [](double t) { return t * t; }}});
    Eigen::VectorXd ts_func{{0.1}, {0.2}, {1.1}, {1.2}};
    test_wavement(func_sig, ts_func, {"linear", "square"});
    std::cout << std::endl;

    std::cout << "Test fixed signal" << std::endl;
    FixedSignal fix_sig(7.0);
    std::cout << "Initial level is " << fix_sig.ParameterAs("level", 1.0)
              << std::endl;
    fix_sig.setParameter("level", 0.75);
    std::cout << "Change level to " << fix_sig.ParameterAs("level", 1.0)
              << std::endl;
    test_wavement(fix_sig, ts_func, {"amp"});
    std::cout << std::endl;

    std::cout << "Test linear signal" << std::endl;
    LinearSignal linear_sig(2.0, 0.1);
    std::cout << "Initial coeff is " << linear_sig.ParameterAs("coeff", 1.0)
              << std::endl;
    linear_sig.setParameter("coeff", 0.5);
    std::cout << "Change coeff to " << linear_sig.ParameterAs("coeff", 1.0)
              << std::endl;
    test_wavement(linear_sig, ts_func, {"amp"});
    std::cout << std::endl;

    std::cout << "Test sine signal" << std::endl;
    SineSignal sine_sig(0.1, 0.0, 2.0, 0.1);
    print_parameters(sine_sig);
    test_wavement(sine_sig, ts, {"amp"});

    std::cout << "Test my rectangle window based on PulseSignal" << std::endl;
    MyRectWindow my_rect_win(0.5, 1.0, 0.7);
    my_rect_win.setParameter("begin", 0.15);
    print_parameters(my_rect_win);
    test_wavement(my_rect_win, ts_func, {"amp"});
    std::cout << std::endl;

    return 0;
}
