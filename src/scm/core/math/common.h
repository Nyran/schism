
#ifndef MATH_COMMON_H_INCLUDED
#define MATH_COMMON_H_INCLUDED

#include <cassert>
#include <cmath>
#include <limits>

#include <scm/core/int_types.h>

namespace scm {
namespace math {

using std::sin;
using std::asin;
using std::cos;
using std::acos;
using std::tan;
using std::atan;
using std::sqrt;
using std::log;
using std::log10;

using std::abs;
using std::fabs;
using std::floor;
using std::ceil;
using std::pow;

template<typename scal_type>
inline int sign(const scal_type val)
{
    return ((val < scal_type(0)) ? -1 : 1);
}

template<typename T> 
inline T max(const T a,
             const T b)
{ 
    return ((a > b) ? a : b);
}

template<typename T>
inline T min(const T a,
             const T b)
{
    return ((a < b) ? a : b);
}

template<typename T> 
inline T fract(const T a)
{ 
    return (a - std::floor(a));
}

template<typename T> 
inline T round(const T a)
{ 
    return ((fract(a) < T(0.5)) ? std::floor(a) : std::ceil(a));
}

template<typename T>
inline bool in_range(const T x,
                     const T a,
                     const T b)
{
    return ((x >= a) && (x <= b));
}

template<typename T>
inline T sqr(const T& a)
{
    return (a * a);
}

template<typename T>
const T clamp(const T val,
              const T min,
              const T max)
{
    return ((val > max) ? max : (val < min) ? min : val);
}

template<typename T, typename scal_type>
inline T lerp(const T min,
              const T max,
              const scal_type a)
{
    return (T(a * max + (scal_type(1) - a) * min));
}

template<typename scal_type>
inline scal_type shoothstep(const scal_type min,
                            const scal_type max,
                            const scal_type x)
{
    scal_type s = clamp((x - min) / (max-min), 0.0f, 1.0f);
    s = (s*s*(3.0f-2.0f*s));

    return (s);
}

template<typename scal_type>
inline const scal_type rad2deg(const scal_type rad)
{
    return (rad * scal_type(57.295779513082320876798154814105));
}

template<typename scal_type>
inline scal_type deg2rad(const scal_type deg)
{
    return (deg * scal_type(0.017453292519943295769236907684886));
}

template<typename int_type>
inline bool is_power_of_two(int_type x)
{
    assert(    std::numeric_limits<int_type>::is_integer
           && !std::numeric_limits<int_type>::is_signed);

    return (! ( x & (x-1)));
}

// From: http://tekpool.wordpress.com/category/bit-count/
template<typename int_type>
inline unsigned bit_count(int_type x)
{
    assert(    std::numeric_limits<int_type>::is_integer
           &&  sizeof(int_type) == 4);

    int& i = *static_cast<int*>(&x);
    unsigned count;

    count =     i
            - ((i >> 1) & 033333333333)
            - ((i >> 2) & 011111111111);

    return (((count + (count >> 3)) & 030707070707) % 63);
}

template<typename int_type>
inline unsigned first_zero_bit(int_type x)
{
    assert(    std::numeric_limits<int_type>::is_integer
           &&  sizeof(int_type) == 4);

    int& i = *static_cast<int*>(&x);

    i = ~i;

    return bit_count((i & (-i)) - 1);
}

template<typename int_type>
inline int floor_log2(int_type x)
{
    assert(    std::numeric_limits<int_type>::is_integer
           && !std::numeric_limits<int_type>::is_signed
           &&  sizeof(int_type) == 4);

    int pos = 0;

    if (x >= scm::uint32(1) << 16) { x >>= 16; pos += 16; }
    if (x >= scm::uint32(1) << 8)  { x >>=  8; pos +=  8; }
    if (x >= scm::uint32(1) << 4)  { x >>=  4; pos +=  4; }
    if (x >= scm::uint32(1) << 2)  { x >>=  2; pos +=  2; }
    if (x >= scm::uint32(1) << 1)  {           pos +=  1; }

    return ((x == 0) ? (-1) : pos);
}

inline int floor_log2(scm::uint64 x)
{
    int pos = 0;

    if (x >= scm::uint64(1) << 32) { x >>= 32; pos += 32; }
    if (x >= scm::uint64(1) << 16) { x >>= 16; pos += 16; }
    if (x >= scm::uint64(1) << 8)  { x >>=  8; pos +=  8; }
    if (x >= scm::uint64(1) << 4)  { x >>=  4; pos +=  4; }
    if (x >= scm::uint64(1) << 2)  { x >>=  2; pos +=  2; }
    if (x >= scm::uint64(1) << 1)  {           pos +=  1; }

    return ((x == 0) ? (-1) : pos);
}

template<typename int_type>
inline unsigned next_power_of_two(int_type x)
{
    assert(    std::numeric_limits<int_type>::is_integer
           && !std::numeric_limits<int_type>::is_signed
           &&  sizeof(int_type) == 4);

    --x;

    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    return (++x);
}

} // namespace math
} // namespace scm

#endif // MATH_COMMON_H_INCLUDED
