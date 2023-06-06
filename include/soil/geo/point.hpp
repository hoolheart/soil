#ifndef SOIL_GEO_POINT_HPP
#define SOIL_GEO_POINT_HPP

#include <vector>
#include <algorithm>
#include "soil_export.h"
#include "Eigen/Dense"

namespace soil {
namespace geo {

/**
 * @brief Geometry point of any scalar type and any dimension
 *
 * Defined by using Eigen::Vector, thus all operations of Eigen::Vector are
 * available.
 *
 * @tparam _dtype --- type of scalar value
 * @tparam _dimension --- space dimension, > 0
 */
template<typename _dtype, std::size_t _dimension>
using Point = Eigen::Vector<_dtype, _dimension>;

typedef Point<float_t, 3> FPoint3D; /**< 3D point with float precision */
typedef Point<float_t, 2> FPoint2D; /**< 2D point with float precision */
typedef Point<double_t, 3> DPoint3D; /**< 3D point with double precision */
typedef Point<double_t, 2> DPoint2D; /**< 2D point with double precision */

/** Homogeneous 3D point with float precision*/
typedef Point<float_t, 4> FPoint3D_h;
/** Homogeneous 3D point with double precision*/
typedef Point<double_t, 4> DPoint3D_h;

typedef Point<int32_t, 3> I32Point3D; /**< 3D point with 32bit integer */
typedef Point<int32_t, 2> I32Point2D; /**< 2D point with 32bit integer */
typedef Point<int64_t, 3> I64Point3D; /**< 3D point with 64bit integer */
typedef Point<int64_t, 2> I64Point2D; /**< 2D point with 64bit integer */

/** convert Point into a vector */
template <typename _dtype, std::size_t _dimension>
std::vector<_dtype> to_vector(const Point<_dtype, _dimension> &point) {
    std::vector<_dtype> vec;
    vec.reserve(_dimension);
    std::copy(point.begin(), point.end(), std::back_inserter(vec));
    return vec;
}

/**
 * @brief generate point from a vector
 *
 * The vector must have same scalar type, but can be any dimension
 */
template <typename _dtype, std::size_t _dimension>
Point<_dtype, _dimension> from_vector(const std::vector<_dtype> &vec) {
    Point<_dtype, _dimension> point;
    auto itp = point.begin();
    auto itv = vec.begin();
    for (; (itp!=point.end()) && (itv!=vec.end()); ++itp, ++itv) {
        *itp = *itv;
    }
    return point;
}

/**
 * @brief convert Point to another with different scalar type
 *
 * @tparam _dtype0 --- scalar type of original point
 * @tparam _dtype1 --- scalar type of new point
 * @tparam _dimension --- space dimension, > 0
 */
template <typename _dtype0, typename _dtype1, std::size_t _dimension>
Point<_dtype1, _dimension> as(const Point<_dtype0, _dimension> &from) {
    Point<_dtype1, _dimension> to;
    auto itf = from.begin();
    auto itt = to.begin();
    for (; (itf!=from.end()) && (itt!=to.end()); ++itf, ++itt) {
        *itt = _dtype1(*itf);
    }
    return to;
}

/** generate homogeneous point from normal one */
template <typename _dtype, std::size_t _dimension>
Point<_dtype, _dimension + 1>
to_homogeneous(const Point<_dtype, _dimension> &point) {
    return (Point<_dtype, _dimension + 1>() << point, _dtype(1)).finished();
}

/** generate normal point from homogeneous one */
template <typename _dtype, std::size_t _dimension>
Point<_dtype, _dimension>
from_homogeneous(const Point<_dtype, _dimension+1> &homo_point) {
    return homo_point.block<_dimension, 1>(0, 0) / homo_point[_dimension];
}

} // namespace geo
} // namespace soil

#endif // SOIL_GEO_POINT_HPP
