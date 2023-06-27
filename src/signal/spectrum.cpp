#include <stdexcept>

#include "soil/signal/spectrum.hpp"
#include "../misc.hpp"

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

Spectrum::Spectrum(const Spectrum &other)
    : priv(new SpectrumPriv{other.priv->freq, other.priv->values}) {}

Spectrum::Spectrum(Spectrum &&other) : priv(other.priv) {
    other.priv = nullptr;
}

Spectrum::~Spectrum() { SAFE_DELETE(priv); }

Spectrum &Spectrum::operator=(const Spectrum &other) {
    priv->freq = other.priv->freq;
    priv->values = other.priv->values;
    return *this;
}

Spectrum &Spectrum::operator=(Spectrum &&other) {
    SAFE_DELETE(priv);
    priv = other.priv;
    other.priv = nullptr;
    return *this;
}

Size Spectrum::Count() const { return priv->freq.size(); }

const Sequence &Spectrum::Frenquencies() const { return priv->freq; }

const Characteristics &Spectrum::Values() const { return priv->values; }

} // namespace signal
} // namespace soil
