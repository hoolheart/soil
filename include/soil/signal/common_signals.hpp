#include "soil_export.h"
#include "soil/signal/base.hpp"

namespace soil {
namespace signal {

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
 * @note amp = coeff * referee + offset
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

/**
 * @brief Abstract periodical siganl with 'cycle' parameter, positive value
 * @note Sub classes should call `PeriodicalSignal::checkParameter` at the end
 *       of implemented `checkParameter` method
 */
class SOIL_EXPORT PeriodicalSignal : public Signal {
protected:
    /**
     * @brief Construct a new Periodical Signal object
     *
     * @param [in] name signal name, transferred to Signal::Signal
     * @param [in] cycle default cycle value
     */
    explicit PeriodicalSignal(const std::string &name, double cycle);
    virtual bool checkParameter(const std::string &para_name,
                                double para_value) const;
};

/**
 * @brief Signal which is sine function of referee, subclass of PeriodicalSignal
 *
 * 3 additional parameters:
 * - phase, sine phase in radian
 * - ac_amp, maximum amplitude of AC part
 * - dc_offset, DC offset of output
 *
 * @note amp = ac_amp * sin((2.0 * pi * referee) / cycle + phase) + dc_offset
 */
class SOIL_EXPORT SineSignal : public PeriodicalSignal {
public:
    /**
     * @brief Construct a new Sine Signal object
     *
     * @param [in] cycle default periodical cycle, positive
     * @param [in] phase default sine phase
     * @param [in] ac_amp default amplitude of AC part
     * @param [in] dc_offset default DC offset
     */
    explicit SineSignal(double cycle, double phase = 0.0, double ac_amp = 1.0,
                        double dc_offset = 0.0);

    std::vector<std::string> keys() const;
    Wavement get(const Eigen::VectorXd &referee) const;

protected:
    bool checkParameter(const std::string &para_name, double para_value) const;
};

} // namespace signal
} // namespace soil
