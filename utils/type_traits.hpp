#ifndef __UTILS_UTILS_HPP__
# define __UTILS_UTILS_HPP__

#include "iterator.hpp"
#include <iterator>
#include <type_traits>
namespace ft {

// conditional
template <bool B, typename U, typename V>
struct conditional {
    typedef V type;
};

template <typename U, typename V>
struct conditional<true, U, V> {
    typedef U type;
};
// --------------- end : conditional

// enable_if
template <bool B, typename T = void>
struct enable_if { };

template <typename T>
struct enable_if<true, T> {
    typedef T type;
};
// --------------- end : enable_if

// is_integral
template< class T >
struct is_integral {
    static const bool value = false;
};

template<>
struct is_integral<bool> {
    static const bool value = true;
};

template<>
struct is_integral<char> {
    static const bool value = true;
};

template<>
struct is_integral<char16_t> {
    static const bool value = true;
};

template<>
struct is_integral<char32_t> {
    static const bool value = true;
};

template<>
struct is_integral<wchar_t> {
    static const bool value = true;
};

template<>
struct is_integral<short> {
    static const bool value = true;
};

template<>
struct is_integral<int> {
    static const bool value = true;
};

template<>
struct is_integral<long> {
    static const bool value = true;
};

template<>
struct is_integral<long long> {
    static const bool value = true;
};

template<>
struct is_integral<unsigned char> {
    static const bool value = true;
};

template<>
struct is_integral<unsigned short> {
    static const bool value = true;
};

template<>
struct is_integral<unsigned int> {
    static const bool value = true;
};

template<>
struct is_integral<unsigned long> {
    static const bool value = true;
};

template<>
struct is_integral<unsigned long long> {
    static const bool value = true;
};
template<class T, class U>
struct is_same {
    static const bool value = false;
};
 
template<class T>
struct is_same<T, T> {
    static const bool value = true;
};
// is_input_iterator
template<typename Tag>
struct is_iterator {
    static const bool value = false;
};

template<>
struct is_iterator<input_iterator_tag> {
    static const bool value = true;
};

template<>
struct is_iterator<forward_iterator_tag> {
    static const bool value = true;
};

template<>
struct is_iterator<bidirectional_iterator_tag> {
    static const bool value = true;
};

template<>
struct is_iterator<random_access_iterator_tag> {
    static const bool value = true;
};

// is_input_iterator
template<typename Tag>
struct is_input_iterator {
    static const bool value = false;
};

template<>
struct is_input_iterator<input_iterator_tag> {
    static const bool value = true;
};

// is_input_iterator
template<typename Tag>
struct is_forward_iterator {
    static const bool value = false;
};

template<>
struct is_forward_iterator<forward_iterator_tag> {
    static const bool value = true;
};

// is_input_iterator
template<typename Tag>
struct is_bidirectional_iterator {
    static const bool value = false;
};

template<>
struct is_bidirectional_iterator<bidirectional_iterator_tag> {
    static const bool value = true;
};

// is_input_iterator
template<typename Tag>
struct is_random_access_iterator {
    static const bool value = false;
};

template<>
struct is_random_access_iterator<random_access_iterator_tag> {
    static const bool value = true;
};

} // namespace ft

#endif /* ifndef __UTILS_UTILS_HPP__ */
