
#ifndef MATH_VEC4_H_INCLUDED
#define MATH_VEC4_H_INCLUDED

#include "vec.h"

namespace scm {
namespace math {

template<typename scal_type>
class vec<scal_type, 4>
{
public:
    typedef scal_type   value_type;

public:
    // ctors
    vec();
    vec(const vec<scal_type, 4>& v);
    //vec(const scal_type a[4]);

    vec(const vec<scal_type, 3>& v,
        const scal_type w);

    explicit vec(const scal_type s);
    explicit vec(const scal_type s,
                 const scal_type t,
                 const scal_type u,
                 const scal_type v = scal_type(0));

    template<typename rhs_scal_t> explicit vec(const vec<rhs_scal_t, 4>& v);

    // dtor
    //~vec();

    // swap
    void swap(vec<scal_type, 4>& rhs);

    // assign
    vec<scal_type, 4>&              operator=(const vec<scal_type, 4>& rhs);
    template<typename rhs_scal_t>
    vec<scal_type, 4>&              operator=(const vec<rhs_scal_t, 4>& rhs);

    // data access
    //inline scal_type*const          operator&()          { return (data_array); }
    //inline const scal_type*const    operator&() const    { return (data_array); }

    // index
    inline scal_type&               operator[](const int i)         { return data_array[i]; };
    inline scal_type                operator[](const int i) const   { return data_array[i]; };

    // unary operators
    vec<scal_type, 4>&              operator+=(const scal_type          s);
    vec<scal_type, 4>&              operator+=(const vec<scal_type, 4>& v);
    vec<scal_type, 4>&              operator-=(const scal_type          s);
    vec<scal_type, 4>&              operator-=(const vec<scal_type, 4>& v);
    vec<scal_type, 4>&              operator*=(const scal_type          s);
    vec<scal_type, 4>&              operator*=(const vec<scal_type, 4>& v);
    vec<scal_type, 4>&              operator/=(const scal_type          s);
    vec<scal_type, 4>&              operator/=(const vec<scal_type, 4>& v);

    // data definition
    union {
        struct {scal_type x, y, z, w;};
        struct {scal_type r, g, b, a;};
        struct {scal_type s, t, p, q;};
        scal_type data_array[4];
    };

}; // class vec<scal_type, 4>

} // namespace math
} // namespace scm

#include "vec4.inl"

#endif // MATH_VEC4_H_INCLUDED
