#include <stdexcept>

#include "soil/signal/spectrum.hpp"

namespace soil {
namespace signal {

struct SpectrumPriv {
    Eigen::VectorXd freq;
    Eigen::VectorXcd values;
};

Spectrum::Spectrum(const Eigen::VectorXd &freq, const Eigen::VectorXcd &values)
    : priv(new SpectrumPriv{freq, values}) {
    if ((priv->freq.size() <= 0) ||
        (priv->freq.size() != priv->values.size())) {
        throw std::runtime_error("Invalid axes sizes");
    }
}

Spectrum::Spectrum(Eigen::VectorXd &&freq, Eigen::VectorXcd &&values)
    : priv(new SpectrumPriv{freq, values}) {
    if ((priv->freq.size() < 2) || (priv->freq.size() != priv->values.size())) {
        throw std::runtime_error("Invalid axes sizes");
    }
}

Spectrum::Spectrum(double f0, double f_step, const Eigen::VectorXcd &values) {
    auto n = values.size();
    if (n < 2) {
        throw std::runtime_error("Empty spectrum");
    }
    auto freq = Eigen::VectorXd::LinSpaced(n, f0, f0 + (n - 1) * f_step);
    priv = new SpectrumPriv{freq, values};
}

Eigen::Index Spectrum::Count() const { return priv->freq.size(); }

const Eigen::VectorXd &Spectrum::Frenquencies() const { return priv->freq; }

const Eigen::VectorXcd &Spectrum::Values() const { return priv->values; }

} // namespace signal
} // namespace soil
