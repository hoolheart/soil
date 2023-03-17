#ifndef SOIL_SIGNAL_HPP
#define SOIL_SIGNAL_HPP

#include <string>
#include <vector>
#include "Eigen/Dense"

class WavementPriv;
class SignalPriv;

class Wavement {
public:
    explicit Wavement();
    explicit Wavement(const Eigen::VectorXd &referee);

    void setReferee(const Eigen::VectorXd &referee);
    void setValues(const std::string &key, const Eigen::VectorXd &values);

    int point_count() const;
    int value_count() const;

    Eigen::VectorXd referee() const;
    std::vector<std::string> keys() const;
    Eigen::VectorXd values(const std::string &key) const;

private:
    WavementPriv *priv;
};

class Signal {
public:
    std::string name() const;

    std::vector<std::string> parameters() const;
    double getParameter(const std::string &para_name) const;
    void setParameter(const std::string &para_name, double para_value);

    virtual std::vector<std::string> keys() const = 0;
    virtual double get(const std::string &key, double referee) const = 0;
    virtual Wavement get(const Eigen::VectorXd &referee) const = 0;

protected:
    explicit Signal(const std::string &name);

    void prepareParameter(const std::string &para_name, double init_value);
    virtual bool checkParameter(const std::string &para_name, double para_value) = 0;

private:
    SignalPriv *priv;
};

#endif // SOIL_SIGNAL_HPP
