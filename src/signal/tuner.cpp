#include <stdexcept>
#include <cmath>

#include "soil/signal/tuner.hpp"
#include "soil/signal/convert.hpp"
#include "../misc.hpp"

namespace soil {
namespace signal {

Tuner::Tuner(const std::string &name) : util::Parameterized(name) {}

struct MeasuredSPriv {
    double begin;
    double step;
    Characteristics ch;
};

MeasuredSParameter::MeasuredSParameter(double f0, double f_step,
                                       const Characteristics &ch)
    : Tuner("measured_sparameter"), priv(new MeasuredSPriv{f0, f_step, ch}) {
    if (f_step < 1e-9) {
        throw std::runtime_error("Invalid frequency step");
    }
}

MeasuredSParameter::~MeasuredSParameter() { SAFE_DELETE(priv); }

Spectrum MeasuredSParameter::tune(const Spectrum &spec) const {
    Sequence freq = spec.Frenquencies();
    Characteristics values = spec.Values();
    assert(freq.size() == values.size());
    for (Index i = 0; i < freq.size(); ++i) {
        Index pos = Index((freq[i] - priv->begin) / priv->step + 0.5);
        if ((pos >= 0) && (pos < priv->ch.size())) {
            values[i] *= priv->ch[pos];
        }
    }
    return Spectrum{std::move(freq), std::move(values)};
}

TunerChannel::TunerChannel(const Tuner_ptr &tuner)
    : Channel("tuner_channel"), tuner(tuner) {}

void TunerChannel::setTuner(const Tuner_ptr &tuner) { this->tuner = tuner; }

Wavement TunerChannel::via(const Wavement &w) const {
    auto spec = wavementToSpectrum(w);
    if (tuner && spec.has_value()) {
        auto tuned = spectrumToWavement(tuner->tune(spec.value()));
        if (tuned.has_value()) {
            return tuned.value();
        }
    }
    return w;
}

} // namespace signal
} // namespace soil
