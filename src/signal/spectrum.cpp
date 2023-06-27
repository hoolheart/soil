#include <stdexcept>

#include "soil/signal/spectrum.hpp"

namespace soil {
namespace signal {

struct SpectrumPriv {
    Sequence freq;
    Characteristics values;
};

Spectrum::Spectrum(const Sequence &freq, const Characteristics &values)
    : priv(new SpectrumPriv{freq, values}) {
    if ((priv->freq.size() <= 0) ||
        (priv->freq.size() != priv->values.size())) {
        throw std::runtime_error("Invalid axes sizes");
    }
}

Spectrum::Spectrum(Sequence &&freq, Characteristics &&values)
    : priv(new SpectrumPriv{freq, values}) {
    if ((priv->freq.size() < 2) || (priv->freq.size() != priv->values.size())) {
        throw std::runtime_error("Invalid axes sizes");
    }
}

Spectrum::Spectrum(double f0, double f_step, const Characteristics &values) {
    auto n = values.size();
    if (n < 2) {
        throw std::runtime_error("Empty spectrum");
    }
    auto freq = Sequence::LinSpaced(n, f0, f0 + (n - 1) * f_step);
    priv = new SpectrumPriv{freq, values};
}

Spectrum::Spectrum(double f0, double f_step, Characteristics &&values) {
    auto n = values.size();
    if (n < 2) {
        throw std::runtime_error("Empty spectrum");
    }
    auto freq = Sequence::LinSpaced(n, f0, f0 + (n - 1) * f_step);
    priv = new SpectrumPriv{freq, values};
}

Size Spectrum::Count() const { return priv->freq.size(); }

const Sequence &Spectrum::Frenquencies() const { return priv->freq; }

const Characteristics &Spectrum::Values() const { return priv->values; }

} // namespace signal
} // namespace soil
