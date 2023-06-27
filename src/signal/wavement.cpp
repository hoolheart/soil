#include <unordered_map>

#include "soil/signal/wavement.hpp"
#include "../misc.hpp"

namespace soil {
namespace signal {

struct WavementPriv {
    Sequence referee;
    std::unordered_map<std::string, Sequence> values;
};

Wavement::Wavement() : priv(new WavementPriv) {}

Wavement::Wavement(const Sequence &referee)
    : priv(new WavementPriv{referee, {}}) {}

Wavement::Wavement(Sequence &&referee) : priv(new WavementPriv{referee, {}}) {}

Wavement::Wavement(const Wavement &other)
    : priv(new WavementPriv{other.priv->referee, other.priv->values}) {}

Wavement::Wavement(Wavement &&other) : priv(other.priv) {
    other.priv = nullptr;
}

Wavement::~Wavement() { SAFE_DELETE(priv); }

Wavement &Wavement::operator=(const Wavement &other) {
    priv->referee = other.priv->referee;
    priv->values = other.priv->values;
    return *this;
}

Wavement &Wavement::operator=(Wavement &&other) {
    SAFE_DELETE(priv);
    priv = other.priv;
    other.priv = nullptr;
    return *this;
}

void Wavement::setReferee(const Sequence &referee) {
    priv->referee = referee;
    priv->values.clear();
}

void Wavement::setReferee(Sequence &&referee) {
    priv->referee = referee;
    priv->values.clear();
}

void Wavement::setValues(const std::string &key, const Sequence &values) {
    if ((key.size() > 0) && (priv->values.find(key) == priv->values.end()) &&
        (priv->referee.size() == values.size())) {
        priv->values.insert({key, values});
    }
}

void Wavement::setValues(const std::string &key, Sequence &&values) {
    if ((key.size() > 0) && (priv->values.find(key) == priv->values.end()) &&
        (priv->referee.size() == values.size())) {
        priv->values.insert({key, values});
    }
}

Size Wavement::PointCount() const { return priv->referee.size(); }

Size Wavement::ValueCount() const { return priv->values.size(); }

const Sequence &Wavement::Referee() const { return priv->referee; }

std::vector<std::string> Wavement::Keys() const {
    std::vector<std::string> keys_;
    keys_.reserve(priv->values.size());
    for (auto pair : priv->values) {
        keys_.push_back(pair.first);
    }
    return keys_;
}

const Sequence &Wavement::Values(const std::string &key) const {
    auto it = priv->values.find(key);
    if (it != priv->values.end()) {
        return it->second;
    }
    return Sequence();
}

std::optional<Wavement::Point> Wavement::PointAt(Index index) const {
    if ((index >= 0) && (index < priv->referee.size())) {
        Point p{priv->referee[index],
                std::unordered_map<std::string, double>()};
        for (auto it = priv->values.begin(); it != priv->values.end(); ++it) {
            p.values[it->first] = it->second[index];
        }
        return p;
    }
    return std::nullopt;
}

} // namespace signal
} // namespace soil
