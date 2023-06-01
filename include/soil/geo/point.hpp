#ifndef SOIL_GEO_POINT_HPP
#define SOIL_GEO_POINT_HPP

#include <stdexcept>
#include <string>
#include <cstdlib>
#include <vector>
#include "soil_export.h"

namespace soil {
namespace geo {

/**
 * @brief Geometry point of any scalar type and any dimension
 *
 * @tparam _ScalarType type of scalar value
 * @tparam _dimension space dimension, > 0
 */
template<typename _ScalarType, std::size_t _dimension>
class Point {
public:
    /** data type */
    typedef _ScalarType dtype;

    /** default constructor */
    Point() noexcept {
        if (_dimension>0) {
            d.resize(_dimension);
        }
    }
    /** constructor with initial value for all dimensions */
    Point(const _ScalarType &def) noexcept {
        if (_dimension > 0) {
            d.resize(_dimension, def);
        }
    }
    /** constructor initialized by a vector */
    Point(const std::vector<_ScalarType> &init) noexcept {
        if (_dimension > 0) {
            d.resize(_dimension);
            auto it0 = init.cbegin();
            auto it1 = d.begin();
            for (; it0!=init.cend() && it1!=d.end(); ++it0, ++it1) {
                *it1 = *it0;
            }
        }
    }
    /** copy constructor */
    Point(const Point<_ScalarType, _dimension> &other) noexcept {
        if (_dimension > 0) {
            d = other.d;
        }
    }
    /** move constructor */
    Point(Point<_ScalarType, _dimension> &&other) noexcept {
        if (_dimension > 0) {
            d.swap(other.d);
        }
    }

    Point<_ScalarType, _dimension> &
    operator=(const Point<_ScalarType, _dimension> &other) {
        if (_dimension > 0) {
            d = other.d;
        }
        return *this;
    }
    Point<_ScalarType, _dimension> &
    operator=(Point<_ScalarType, _dimension> &&other) {
        if (_dimension > 0) {
            d.swap(other.d);
        }
        return *this;
    }

    /** get dimension */
    std::size_t dimension() const noexcept {
        return d.size();
    }
    /** get data pointer */
    const dtype* ptr() const noexcept { return d.data(); }

    /** modifiable access of `index`-th dimension */
    dtype &operator[](std::size_t index) { return d[index]; }
    /** read-only access of `index`-th dimension */
    const dtype &operator[](std::size_t index) const { return d[index]; }
    /** read-only access of `index`-th dimension */
    const dtype &at(std::size_t index) const { return d[index]; }

    /**
     * @brief convert to another data type
     *
     * @tparam U destination data type
     * @return Point<U, _dimension> point with given data type
     */
    template<typename U>
    Point<U, _dimension> as() const {
        Point<U, _dimension> other;
        for(size_t i=0; i<_dimension; ++i) {
            other[i] = U(d[i]);
        }
        return other;
    }
    /** convert to vector */
    std::vector<dtype> to_vector() const {
        std::vector<dtype> vec = d;
        return vec;
    }

    /** read-only access of first dimension by using special name "x" */
    const dtype &x() const { return at(0); }
    /** set first dimension by using special name "x" */
    void x(const dtype &val) {
        if (_dimension>0) {
            d[0] = val;
        } else {
            throw std::out_of_range("No x element");
        }
    }
    /** read-only access of second dimension by using special name "y" */
    const dtype &y() const { return at(1); }
    /** set second dimension by using special name "y" */
    void y(const dtype &val) {
        if (_dimension > 1) {
            d[1] = val;
        } else {
            throw std::out_of_range("No y element");
        }
    }
    /** read-only access of third dimension by using special name "z" */
    const dtype &z() const { return at(2); }
    /** set third dimension by using special name "z" */
    void z(const dtype &val) {
        if (_dimension > 2) {
            d[2] = val;
        } else {
            throw std::out_of_range("No z element");
        }
    }

private:
    std::vector<_ScalarType> d;
};

typedef Point<float, 3> FPoint3D; /**< 3D point with float precision */
typedef Point<float, 2> FPoint2D; /**< 2D point with float precision */
typedef Point<double, 3> DPoint3D; /**< 3D point with double precision */
typedef Point<double, 2> DPoint2D; /**< 2D point with double precision */
typedef Point<int32_t, 3> I32Point3D; /**< 3D point with 32bit integer */
typedef Point<int32_t, 2> I32Point2D; /**< 2D point with 32bit integer */
typedef Point<int64_t, 3> I64Point3D; /**< 3D point with 64bit integer */
typedef Point<int64_t, 2> I64Point2D; /**< 2D point with 64bit integer */

} // namespace geo
} // namespace soil

#endif // SOIL_GEO_POINT_HPP
