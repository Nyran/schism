
namespace std {

template<typename scal_type, const unsigned dim>
inline void swap(scm::math::vec<scal_type, dim>& lhs,
                 scm::math::vec<scal_type, dim>& rhs)
{
    lhs.swap(rhs);
}

} // namespace std

namespace scm {
namespace math {

template<typename scal_type,
         const unsigned dim>
inline const vec<scal_type, dim>
operator++(vec<scal_type, dim>& v, int)
{
    vec<scal_type, dim> tmp(v);

    v += scal_type(1);

    return (tmp);
}

template<typename scal_type,
         const unsigned dim>
inline vec<scal_type, dim>&
operator++(vec<scal_type, dim>& v)
{
    v += scal_type(1);

    return (v);
}

template<typename scal_type,
         const unsigned dim>
inline const vec<scal_type, dim>
operator--(vec<scal_type, dim>& v, int)
{
    vec<scal_type, dim> tmp(v);

    v -= scal_type(1);

    return (tmp);
}

template<typename scal_type,
         const unsigned dim>
inline vec<scal_type, dim>&
operator--(vec<scal_type, dim>& v)
{
    v -= scal_type(1);

    return (v);
}

template<typename scal_type,
         const unsigned dim>
inline const vec<scal_type, dim>
operator-(const vec<scal_type, dim>& rhs)
{
    vec<scal_type, dim> tmp(rhs);

    tmp *= scal_type(-1);

    return (tmp);
}

// binary operators
template<typename scal_type,
         const unsigned dim>
inline const vec<scal_type, dim>
operator+(const vec<scal_type, dim>& lhs,
          const vec<scal_type, dim>& rhs)
{
    vec<scal_type, dim> tmp(lhs);
    
    tmp += rhs;

    return (tmp);
}

template<typename scal_type,
         const unsigned dim>
inline const vec<scal_type, dim>
operator+(const vec<scal_type, dim>& lhs,
          const scal_type            rhs)
{
    vec<scal_type, dim> tmp(lhs);
    
    tmp += rhs;

    return (tmp);
}

template<typename scal_type,
         const unsigned dim>
inline const vec<scal_type, dim>
operator-(const vec<scal_type, dim>& lhs,
          const vec<scal_type, dim>& rhs)
{
    vec<scal_type, dim> tmp(lhs);
    
    tmp -= rhs;

    return (tmp);
}

template<typename scal_type,
         const unsigned dim>
inline const vec<scal_type, dim>
operator-(const vec<scal_type, dim>& lhs,
          const scal_type            rhs)
{
    vec<scal_type, dim> tmp(lhs);
    
    tmp -= rhs;

    return (tmp);
}

template<typename scal_type,
         const unsigned dim>
inline const vec<scal_type, dim>
operator*(const vec<scal_type, dim>& lhs,
          const vec<scal_type, dim>& rhs)
{
    vec<scal_type, dim> tmp(lhs);
    
    tmp *= rhs;

    return (tmp);
}

template<typename scal_type,
         const unsigned dim>
inline const vec<scal_type, dim>
operator*(const scal_type            lhs,
          const vec<scal_type, dim>& rhs)
{
    vec<scal_type, dim> tmp(rhs);
    
    tmp *= lhs;

    return (tmp);
}

template<typename scal_type,
         const unsigned dim>
inline const vec<scal_type, dim>
operator*(const vec<scal_type, dim>& lhs,
          const scal_type            rhs)
{
    vec<scal_type, dim> tmp(lhs);
    
    tmp *= rhs;

    return (tmp);
}

template<typename scal_type,
         const unsigned dim>
inline const vec<scal_type, dim>
operator/(const vec<scal_type, dim>& lhs,
          const vec<scal_type, dim>& rhs)
{
    vec<scal_type, dim> tmp(lhs);
    
    tmp /= rhs;

    return (tmp);
}

template<typename scal_type,
         const unsigned dim>
inline const vec<scal_type, dim>
operator/(const vec<scal_type, dim>& lhs,
          const scal_type            rhs)
{
    vec<scal_type, dim> tmp(lhs);
    
    tmp /= rhs;

    return (tmp);
}


template<typename scal_type,
         const unsigned dim>
inline scal_type length_sqr(const vec<scal_type, dim>& lhs)
{
    return (dot(lhs, lhs));
}

template<typename scal_type,
         const unsigned dim>
inline scal_type length(const vec<scal_type, dim>& lhs)
{
    return (std::sqrt(length_sqr(lhs)));
}

template<typename scal_type,
         const unsigned dim>
inline const vec<scal_type, dim> normalize(const vec<scal_type, dim>& lhs)
{
    return (lhs / length(lhs));
}

template<typename scal_type,
         const unsigned dim>
inline scal_type distance(const vec<scal_type, dim>& lhs,
                          const vec<scal_type, dim>& rhs)
{
    return (length(lhs - rhs));
}

} // namespace math
} // namespace scm
