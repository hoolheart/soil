#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "soil/signal_process.hpp"

const double TWO_PI = M_PI * 2.0;

class MySineSignal: public Signal {
public:
    explicit MySineSignal(
        double amp = 1.0, double freq = 50.0, double phase = 0.0
    ): Signal("my_sine") {
        prepareParameter("amp", (amp>0.0) ? amp : 1.0);
        prepareParameter("freq", (freq>0.0) ? freq : 50.0);
        while (phase < 0.0) {
            phase += TWO_PI;
        }
        while (phase > TWO_PI) {
            phase -= TWO_PI;
        }
        prepareParameter("phase", phase);
    }

    std::vector<std::string> keys() const {
        return {"amp"};
    }

    Wavement get(const Eigen::VectorXd &referee) const {
        Wavement w(referee);
        Eigen::VectorXd amps = referee;
        double amp = getParameter("amp"), freq = getParameter("freq"),
               phase = getParameter("phase");
        std::for_each(amps.begin(), amps.end(),
            [amp, freq, phase](double &val) {val = amp * sin(TWO_PI * freq * val + phase);});
        w.setValues("amp", amps);
        return w;
    }

protected:
    bool checkParameter(const std::string &para_name, double para_value) {
        if ((para_name == "amp") || (para_name == "freq")) {
            return para_value > 0.0;
        }
        else if (para_name == "phase") {
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
    for (auto key: keys) {
        std::cout << "- " << key << std::endl;
    }
    std::cout << std::endl;

    auto parameters = signal.parameters();
    std::cout << "There is/are " << parameters.size() << " parameters:" << std::endl;
    for (auto para: parameters) {
        std::cout << "- " << para << ": " << signal.getParameter(para) << std::endl;
    }
    std::cout << std::endl;

    signal.setParameter("freq", 10.0);
    auto freq = signal.getParameter("freq");
    if (fabs(freq - 10.0) < 1e-9) {
        std::cout << "Succeed to change frequency to 10Hz" << std::endl;
    }
    else {
        std::cout << "Failed to change frequency to 10Hz (" << freq << ")" << std::endl;
    }
    std::cout << std::endl;

    Eigen::VectorXd ts = Eigen::VectorXd::LinSpaced(21, 0.0, 0.2);
    auto w = signal.get(ts);
    std::cout << "Generate a wavement:" << std::endl;
    auto col = w.values(keys[0]);
    std::for_each(col.begin(), col.end(), [](auto &val)
                  { std::cout << val << " "; });
    std::cout << std::endl;
    bool correct = true;
    for (int i=0; i<10; ++i) {
        if (fabs(col(i) - col(i+10)) > 1e-9) {
            std::cout << i << "th data don't match:" << col(i) << col(i+10) << std::endl;
            correct = false;
            break;
        }
    }
    if (correct) {
        std::cout << "Frequency of generated wavement is correct" << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
