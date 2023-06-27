#ifndef SOIL_SIGNAL_SIGNAL_HPP
#define SOIL_SIGNAL_SIGNAL_HPP

#include <any>
#include <string>
#include <vector>

#include "soil_export.h"
#include "soil/util/parameterized.hpp"
#include "soil/signal/wavement.hpp"

namespace soil {
namespace signal {

/**
 * @brief Abstract signal interface
 *
 * This interface can't be instantiated directly, user should implement all
 * methods in a derived class.
 *
 * The interface is designed in three ascepts:
 * 1. every signal has a name, such name can be only assigned by derived class
 *    in constructor;
 * 2. a signal can have any number of parameters, the derived class use
 *    `prepareParameter` method to initialize a parameter, and implement
 *    `checkParameter` method to guard parameter setting;
 * 3. most important function of a signal is to generate a wavement by giving a
 *    referee, such function is performed by `get` method which should be
 *    implemented in derived class.
 *
 * The necessary implemetations in derived class:
 * 1. constructor using protected `Signal(name)` to define name, and using
 *    `prepareParameter` to define parameters;
 * 2. `keys` method to specify keys of values in generated wavement;
 * 3. `get` method to achieve wavement generation;
 * 4. `checkParameter` method to guard parameter setting, the default
 *    implementation only concerns the value types.
 */
class SOIL_EXPORT Signal : public util::Parameterized {
public:
    /** Get keys of all columns */
    virtual std::vector<std::string> Keys() const = 0;
    /** Generate a wavement according to given referee */
    virtual Wavement get(const Sequence &referee) const = 0;

protected:
    /** Constructor with name assigning */
    explicit Signal(const std::string &name);
};

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

    /** Destructor */
    ~FunctionalSignal();

    std::vector<std::string> Keys() const;
    Wavement get(const Sequence &referee) const;

private:
    FunctionalSignalPriv *priv;
};

/**
 * @brief Signal which holds to a fixed level
 *
 * One parameter:
 * - level, fixed level, type: double
 */
class SOIL_EXPORT FixedSignal : public Signal {
public:
    /**
     * @brief Construct a new Fixed Signal object
     *
     * @param [in] level default signal level
     */
    explicit FixedSignal(double level);

    std::vector<std::string> Keys() const;
    Wavement get(const Sequence &referee) const;
};

/**
 * @brief Signal which is linear function of referee
 *
 * Two parameters:
 * - coeff, coefficient factor, type: double
 * - offset, offset at referee 0, type: double
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

    std::vector<std::string> Keys() const;
    Wavement get(const Sequence &referee) const;
};

/** Abstract periodical signal with 'freq' parameter (unit: Hz) */
class SOIL_EXPORT PeriodicalSignal : public Signal {
protected:
    /**
     * @brief Construct a new Periodical Signal object
     *
     * @param [in] name signal name, transferred to Signal::Signal
     * @param [in] freq default frequency
     */
    explicit PeriodicalSignal(const std::string &name, double freq);
};

/**
 * @brief Signal which is sine function of referee, subclass of PeriodicalSignal
 *
 * 3 additional parameters:
 * - phase, sine phase in radian
 * - A, maximum amplitude of AC part
 * - offset, DC offset of output
 *
 * @note amp = A * sin(2.0 * pi * freq * referee + phase) + offset
 */
class SOIL_EXPORT SineSignal : public PeriodicalSignal {
public:
    /**
     * @brief Construct a new Sine Signal object
     *
     * @param [in] freq default frequency
     * @param [in] phase default sine phase
     * @param [in] A default amplitude of AC part
     * @param [in] offset default DC offset
     */
    explicit SineSignal(double freq = 50.0, double phase = 0.0, double A = 1.0,
                        double offset = 0.0);

    std::vector<std::string> Keys() const;
    Wavement get(const Sequence &referee) const;
};

/**
 * @brief Signal which is sine function of referee, subclass of PeriodicalSignal
 *
 * 2 additional parameters:
 * - phase, sine phase in radian
 * - A, maximum amplitude of AC part
 *
 * @note complex sine signal means A exp(j(2 pi f t + phase)),
 *       generating a wavement containing two columns:
 *          - real = A * cos(2.0 * pi * freq * referee + phase)
 *          - imag = A * sin(2.0 * pi * freq * referee + phase)
 */
class SOIL_EXPORT ComplexSineSignal : public PeriodicalSignal {
public:
    /**
     * @brief Construct a new Complex Sine Signal object
     *
     * @param [in] freq default frequency
     * @param [in] phase default sine phase
     * @param [in] A default amplitude
     */
    explicit ComplexSineSignal(double freq = 50.0, double phase = 0.0,
                               double A = 1.0);

    std::vector<std::string> Keys() const;
    Wavement get(const Sequence &referee) const;
};

/**
 * @brief Abstract pulse signal with 'begin' and 'duration' parameters
 *
 * 'begin' parameter can be any value, 'duration' parameter must be positive,
 * their units are both seconds.
 *
 * @note Sub classes should call `PulseSignal::checkParameter` at the end
 *       of implemented `checkParameter` method
 */
class SOIL_EXPORT PulseSignal : public Signal {
protected:
    /**
     * @brief Construct a new Pulse Signal object
     *
     * @param [in] name signal name, transferred to Signal::Signal
     * @param [in] begin beginning time of pulse
     * @param [in] duration time duration of pulse
     */
    explicit PulseSignal(const std::string &name, double begin,
                         double duration);

    virtual bool checkParameter(const std::string &name,
                                const std::any &current,
                                const std::any &next) const;
};

} // namespace signal
} // namespace soil

#endif // SOIL_SIGNAL_SIGNAL_HPP
