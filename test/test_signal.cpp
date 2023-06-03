#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "soil/signal/common_signals.hpp"
#include "soil/signal/base.hpp"

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

    std::vector<std::string> keys() const { return {"amp"}; }

    Wavement get(const Eigen::VectorXd &referee) const {
        Wavement w(referee);
        Eigen::VectorXd amps = referee;
        double amp = getParameter("amp"), freq = getParameter("freq"),
               phase = getParameter("phase");
        std::for_each(amps.begin(), amps.end(),
                      [amp, freq, phase](double &val) {
                          val = amp * sin(TWO_PI * freq * val + phase);
                      });
        w.setValues("amp", amps);
        return w;
    }

  protected:
    bool checkParameter(const std::string &para_name, double para_value) const {
        if ((para_name == "amp") || (para_name == "freq")) {
            return para_value > 0.0;
        } else if (para_name == "phase") {
            return true;
        }
        return false;
    }
};

int main() {

    std::cout << "Test of signal process" << std::endl;

    MySineSignal signal;
    auto keys = signal.keys();
    std::cout << "There is/are " << keys.size() << " columns in signal "
              << signal.name() << ":" << std::endl;
    for (auto key : keys) {
        std::cout << "- " << key << std::endl;
    }
    std::cout << std::endl;

    auto parameters = signal.parameters();
    std::cout << "There is/are " << parameters.size()
              << " parameters:" << std::endl;
    for (auto para : parameters) {
        std::cout << "- " << para << ": " << signal.getParameter(para)
                  << std::endl;
    }
    std::cout << std::endl;

    signal.setParameter("freq", 10.0);
    auto freq = signal.getParameter("freq");
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
    auto col = w.values(keys[0]);
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
    auto w_func = func_sig.get(ts_func);
    std::cout << "Generate a wavement:" << std::endl;
    auto keys_func = w_func.keys();
    for (auto key : keys_func) {
        std::cout << "- " << key << ": ";
        auto col = w_func.values(key);
        for (auto val : col) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Test fixed signal" << std::endl;
    FixedSignal fix_sig(7.0);
    std::cout << "Initial level is " << fix_sig.getParameter("level")
              << std::endl;
    fix_sig.setParameter("level", 0.75);
    std::cout << "Change level to " << fix_sig.getParameter("level")
              << std::endl;
    auto w_fix = fix_sig.get(ts_func);
    std::cout << "Generate a wavement:";
    assert(w_fix.keys().size() == 1);
    assert(w_fix.keys()[0] == "amp");
    auto col_fix = w_fix.values("amp");
    for (auto val : col_fix) {
        std::cout << " " << val;
    }
    std::cout << std::endl << std::endl;

    std::cout << "Test linear signal" << std::endl;
    LinearSignal linear_sig(2.0, 0.1);
    std::cout << "Initial coeff is " << linear_sig.getParameter("coeff")
              << std::endl;
    linear_sig.setParameter("coeff", 0.5);
    std::cout << "Change coeff to " << linear_sig.getParameter("coeff")
              << std::endl;
    auto w_linear = linear_sig.get(ts_func);
    std::cout << "Generate a wavement:";
    assert(w_linear.keys().size() == 1);
    assert(w_linear.keys()[0] == "amp");
    auto col_linear = w_linear.values("amp");
    for (auto val : col_linear) {
        std::cout << " " << val;
    }
    std::cout << std::endl << std::endl;

    std::cout << "Test sine signal" << std::endl;
    SineSignal sine_sig(0.1, 0.0, 2.0, 0.1);
    parameters = sine_sig.parameters();
    std::cout << "There is/are " << parameters.size()
              << " parameters:" << std::endl;
    for (auto para : parameters) {
        std::cout << "- " << para << ": " << sine_sig.getParameter(para)
                  << std::endl;
    }
    auto w_sine = sine_sig.get(ts);
    std::cout << "Generate a wavement:";
    assert(w_sine.keys().size() == 1);
    assert(w_sine.keys()[0] == "amp");
    auto col_sine = w_sine.values("amp");
    for (auto val : col_sine) {
        std::cout << " " << val;
    }
    std::cout << std::endl << std::endl;

    return 0;
}
