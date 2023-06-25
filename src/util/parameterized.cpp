#include <unordered_map>

#include "soil/util/parameterized.hpp"

namespace soil {
namespace util {

struct ParameterizedPriv {
    std::string name;
    std::unordered_map<std::string, std::any> parameters;
};

Parameterized::Parameterized(const std::string &name) {
    priv = new ParameterizedPriv{name,
                                 std::unordered_map<std::string, std::any>()};
}

std::string Parameterized::Name() const { return priv->name; }

std::vector<std::string> Parameterized::ParameterNames() const {
    std::vector<std::string> keys_;
    keys_.reserve(priv->parameters.size());
    for (const auto &pair : priv->parameters) {
        keys_.push_back(pair.first);
    }
    return keys_;
}

std::any Parameterized::Parameter(const std::string &name,
                                  const std::any &def) const {
    auto it = priv->parameters.find(name);
    if (it != priv->parameters.end()) {
        return it->second;
    }
    return def;
}

bool Parameterized::setParameter(const std::string &name,
                                 const std::any &value) {
    auto it = priv->parameters.find(name);
    if ((it != priv->parameters.end()) &&
        checkParameter(name, it->second, value)) {
        it->second = value;
        return true;
    }
    return false;
}

void Parameterized::prepareParameter(const std::string &name,
                                     const std::any &init_value) {
    priv->parameters.insert({name, init_value});
}

bool Parameterized::checkParameter(const std::string &_,
                                   const std::any &current,
                                   const std::any &next) const {
    return current.type() == next.type();
}

} //namespace util
} //namespace soil
