#include "soil/signal_process.hpp"
#include "signal_process_p.hpp"

Wavement::Wavement() {
    priv = new WavementPriv{};
}

Wavement::Wavement(const Eigen::VectorXd &referee) {
    priv = new WavementPriv{referee, std::unordered_map<std::string, Eigen::VectorXd>()};
}

void Wavement::setReferee(const Eigen::VectorXd &referee) {
    priv->referee = referee;
    priv->values.clear();
}

void Wavement::setValues(const std::string &key, const Eigen::VectorXd &values) {
    if ((key.size() > 0) && (priv->values.find(key) == priv->values.end()) &&
            (priv->referee.size() == values.size())) {
        priv->values.insert({key, values});
    }
}

int Wavement::point_count() const {
    return priv->referee.size();
}

int Wavement::value_count() const {
    return priv->values.size();
}

Eigen::VectorXd Wavement::referee() const {
    return priv->referee;
}

std::vector<std::string> Wavement::keys() const {
    std::vector<std::string> keys_;
    keys_.reserve(priv->values.size());
    for (auto pair: priv->values) {
        keys_.push_back(pair.first);
    }
    return keys_;
}

Eigen::VectorXd Wavement::values(const std::string &key) const {
    auto it = priv->values.find(key);
    if (it != priv->values.end()) {
        return it->second;
    }
    return Eigen::VectorXd();
}

std::optional<Wavement::Point> Wavement::point(int index) const
{
    if ((index>=0) && (index<priv->referee.size())) {
        Point p{priv->referee[index], std::unordered_map<std::string, double>()};
        for (auto it = priv->values.begin(); it != priv->values.end(); ++it) {
            p.values[it->first] = it->second[index];
        }
        return p;
    }
    return std::nullopt;
}

Signal::Signal(const std::string &name) {
    priv = new SignalPriv{name, std::unordered_map<std::string, double>()};
}

std::string Signal::name() const {
    return priv->name;
}

std::vector<std::string> Signal::parameters() const {
    std::vector<std::string> keys_;
    keys_.reserve(priv->parameters.size());
    for (auto pair: priv->parameters) {
        keys_.push_back(pair.first);
    }
    return keys_;
}

double Signal::getParameter(const std::string &para_name, double def) const {
    auto it = priv->parameters.find(para_name);
    if (it != priv->parameters.end()) {
        return it->second;
    }
    return def;
}

void Signal::setParameter(const std::string &para_name, double para_value) {
    auto it = priv->parameters.find(para_name);
    if ((it != priv->parameters.end()) && checkParameter(para_name, para_value)) {
        it->second = para_value;
    }
}

void Signal::prepareParameter(const std::string &para_name, double init_value) {
    priv->parameters.insert({para_name, init_value});
}
