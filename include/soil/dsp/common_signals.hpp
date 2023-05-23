#define _USE_MATH_DEFINES
#include <math.h>
#include <functional>
#include "soil_export.h"
#include "soil/dsp/signal_process.hpp"

namespace soil {
namespace dsp {

class FunctionalSignalPriv;

/**
 * @brief Wrapper of signal functions
 *
 * It can wrap any number of signal functions via constructor.
 * Signal function receives only one double argument as referee and returns
 * a double value as signal amplitude.
 * Each function corresponds a non-empty key.
 *
 * No valid parameter.
 */
class SOIL_EXPORT FunctionalSignal : public Signal {
public:
    /** signal function */
    typedef std::function<double(double)> SIG_FUNC;

    /**
     * @brief Construct a new Functional Signal object
     *
     * @param [in] functions map of signal function and its key
     */
    explicit FunctionalSignal(
        const std::unordered_map<std::string, SIG_FUNC> &functions);

    std::vector<std::string> keys() const;
    Wavement get(const Eigen::VectorXd &referee) const;

protected:
    bool checkParameter(const std::string &para_name, double para_value) const;

private:
    FunctionalSignalPriv *priv;
};

/**
 * @brief Signal which holds to a fixed level
 *
 * One parameter:
 * - level, fixed level
 */
class SOIL_EXPORT FixedSignal : public Signal {
public:
    /**
     * @brief Construct a new Fixed Signal object
     *
     * @param [in] level default signal level
     */
    explicit FixedSignal(double level);

    std::vector<std::string> keys() const;
    Wavement get(const Eigen::VectorXd &referee) const;

protected:
    bool checkParameter(const std::string &para_name, double para_value) const;
};

/**
 * @brief Signal which is linear function of referee
 *
 * Two parameters:
 * - coeff, coefficient factor
 * - offset, offset at referee 0
 *
 * Note: amp = coeff * referee + offset
 */
class SOIL_EXPORT LinearSignal : public Signal {
public:
    /**
     * @brief Construct a new Linear Signal object
     *
     * @param [in] coeff default coefficient factor
     * @param [in] offset default offset at referee 0
     */
    explicit LinearSignal(double coeff, double offset);

    std::vector<std::string> keys() const;
    Wavement get(const Eigen::VectorXd &referee) const;

protected:
    bool checkParameter(const std::string &para_name, double para_value) const;
};

} // namespace dsp
} // namespace soil
