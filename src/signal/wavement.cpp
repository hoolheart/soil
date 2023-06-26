#include <unordered_map>

#include "soil/signal/wavement.hpp"

namespace soil {
namespace signal {

struct WavementPriv {
    Sequence referee;
    std::unordered_map<std::string, Sequence> values;
};

Wavement::Wavement() { priv = new WavementPriv{}; }

Wavement::Wavement(const Sequence &referee) {
    priv =
        new WavementPriv{referee, std::unordered_map<std::string, Sequence>()};
}

void Wavement::setReferee(const Sequence &referee) {
    priv->referee = referee;
    priv->values.clear();
}

void Wavement::setValues(const std::string &key, const Sequence &values) {
    if ((key.size() > 0) && (priv->values.find(key) == priv->values.end()) &&
        (priv->referee.size() == values.size())) {
        priv->values.insert({key, values});
    }
}

Eigen::Index Wavement::PointCount() const { return priv->referee.size(); }

Eigen::Index Wavement::ValueCount() const { return priv->values.size(); }

Sequence Wavement::Referee() const { return priv->referee; }

std::vector<std::string> Wavement::Keys() const {
    std::vector<std::string> keys_;
    keys_.reserve(priv->values.size());
    for (auto pair : priv->values) {
        keys_.push_back(pair.first);
    }
    return keys_;
}

Sequence Wavement::Values(const std::string &key) const {
    auto it = priv->values.find(key);
    if (it != priv->values.end()) {
        return it->second;
    }
    return Sequence();
}

std::optional<Wavement::Point> Wavement::PointAt(Eigen::Index index) const {
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
