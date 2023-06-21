#include <unordered_map>

#include "soil/signal/wavement.hpp"
#include "soil/signal/signal.hpp"

namespace soil {
namespace signal {

struct WavementPriv {
    Sequence referee;
    std::unordered_map<std::string, Sequence> values;
};

struct SignalPriv {
    std::string name;
    std::unordered_map<std::string, std::any> parameters;
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

int Wavement::PointCount() const { return priv->referee.size(); }

int Wavement::ValueCount() const { return priv->values.size(); }

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

std::optional<Wavement::Point> Wavement::PointAt(int index) const {
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

Signal::Signal(const std::string &name) {
    priv = new SignalPriv{name, std::unordered_map<std::string, std::any>()};
}

std::string Signal::Name() const { return priv->name; }

std::vector<std::string> Signal::ParameterNames() const {
    std::vector<std::string> keys_;
    keys_.reserve(priv->parameters.size());
    for (const auto &pair : priv->parameters) {
        keys_.push_back(pair.first);
    }
    return keys_;
}

std::any Signal::Parameter(const std::string &name,
                           const std::any &def) const {
    auto it = priv->parameters.find(name);
    if (it != priv->parameters.end()) {
        return it->second;
    }
    return def;
}

bool Signal::setParameter(const std::string &name, const std::any &value) {
    auto it = priv->parameters.find(name);
    if ((it != priv->parameters.end()) &&
        checkParameter(name, it->second, value)) {
        it->second = value;
        return true;
    }
    return false;
}

void Signal::prepareParameter(const std::string &name,
                              const std::any &init_value) {
    priv->parameters.insert({name, init_value});
}

bool Signal::checkParameter(const std::string &_, const std::any &current,
                            const std::any &next) const {
    return current.type() == next.type();
}

} // namespace signal
} // namespace soil
