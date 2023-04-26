#define _USE_MATH_DEFINES
#include <math.h>
#include <functional>
#include "soil_export.h"
#include "soil/signal_process.hpp"

class FunctionalSignalPriv;

class SOIL_EXPORT FunctionalSignal : public Signal {
public:
    typedef std::function<double(double)> FUNC_TYPE;

    explicit FunctionalSignal(
        const std::unordered_map<std::string, FUNC_TYPE> &functions);

    std::vector<std::string> keys() const;
    Wavement get(const Eigen::VectorXd &referee) const;

protected:
    bool checkParameter(const std::string &para_name, double para_value) const;

private:
    FunctionalSignalPriv *priv;
};

class SOIL_EXPORT FixedSignal : public Signal {
public:
    explicit FixedSignal(double level);

    std::vector<std::string> keys() const;
    Wavement get(const Eigen::VectorXd &referee) const;

protected:
    bool checkParameter(const std::string &para_name, double para_value) const;
};

class SOIL_EXPORT LinearSignal : public Signal
{
public:
    explicit LinearSignal(double coeff, double offset);

    std::vector<std::string> keys() const;
    Wavement get(const Eigen::VectorXd &referee) const;

protected:
    bool checkParameter(const std::string &para_name, double para_value) const;
};
