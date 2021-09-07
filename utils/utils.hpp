#ifndef __UTILS_UTILS_HPP__
# define __UTILS_UTILS_HPP__

namespace ft {

template <bool B, typename U, typename V>
struct conditional {
    typedef V type;
};

template <typename U, typename V>
struct conditional<true, U, V> {
    typedef U type;
};

/* template<bool B, typename U, typename V>
struct cond<B, U, V> {

}; */

} // namespace ft

#endif /* ifndef __UTILS_UTILS_HPP__ */
