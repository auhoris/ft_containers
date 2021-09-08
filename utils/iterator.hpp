#ifndef __UTILS_ITERATOR_HPP__
# define __UTILS_ITERATOR_HPP__

# include <cstddef>
# include <memory>
# include <type_traits>

namespace ft {

// iterator tags
struct input_iterator_tag { };
struct forward_iterator_tag : public input_iterator_tag { };
struct bidirectional_iterator_tag : public forward_iterator_tag { };
struct random_access_iterator_tag : public bidirectional_iterator_tag { };
// --------------- end : iterator tags

// iterator
template <class Category,
         class T,
         class Distance = std::ptrdiff_t,
         class Pointer = T*,
         class Reference = T&>
struct iterator {
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};
// --------------- end : iterator

// iterator traits
template<class Iter>
struct iterator_traits {
    typedef typename Iter::iterator_category    iterator_category;
    typedef typename Iter::value_type           value_type;
    typedef typename Iter::difference_type      difference_type;
    typedef typename Iter::pointer              pointer;
    typedef typename Iter::reference            reference;
};

template<class T>
struct iterator_traits<T*> {
    typedef random_access_iterator_tag  iterator_category;
    typedef T                           value_type;
    typedef ptrdiff_t                   difference_type;
    typedef T*                          pointer;
    typedef T&                          reference;
};
// --------------- end : iterator_traits

// reverse iterator
template<typename Iter>
class reverse_iterator
: public iterator<typename iterator_traits<Iter>::iterator_category,
                typename iterator_traits<Iter>::value_type,
                typename iterator_traits<Iter>::difference_type,
                typename iterator_traits<Iter>::pointer,
                typename iterator_traits<Iter>::reference> {
 protected:
     Iter   _iter;

 public:
     typedef Iter  iterator_type;
     typedef typename iterator_traits<Iter>::iterator_category  iterator_category;
     typedef typename iterator_traits<Iter>::value_type  value_type;
     typedef typename iterator_traits<Iter>::difference_type  difference_type;
     typedef typename iterator_traits<Iter>::pointer  pointer;
     typedef typename iterator_traits<Iter>::reference  reference;

     reverse_iterator() : _iter() { }
     explicit reverse_iterator(iterator_type iter) : _iter(iter) { }
     reverse_iterator(const reverse_iterator<Iter>& iter) : _iter(iter.base()) { }
     iterator_type base() const { return (_iter); }
     reference operator*() const { Iter   tmp = _iter; tmp--; return (*tmp); }
     reverse_iterator operator+(difference_type n) const { return (reverse_iterator(_iter - n));}
     reverse_iterator& operator++() { _iter--; return (*this); }
     reverse_iterator  operator++(int) {
         reverse_iterator   tmp(*this);
         _iter--;
         return (tmp);
     }
     reverse_iterator& operator+=(difference_type n) {
         _iter -= n;
         return (*this);
     }
     reverse_iterator operator-(difference_type n) const { return (reverse_iterator(_iter + n)); }
     reverse_iterator& operator--() {
         _iter++;
         return (*this);
     }
     reverse_iterator  operator--(int) {
         reverse_iterator   tmp(*this);
         _iter--;
         return (tmp);
     }
     reverse_iterator& operator-= (difference_type n) {
         _iter += n;
         return (*this);
     }
     pointer operator->() const { return (std::addressof(operator*())); }
     reference operator[] (difference_type n) const { return (*(*this + n)); }
};

// relational operators
template <class Iterator>
bool operator==(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
    return (lhs.base() == rhs.base());
}
template <class Iterator>
bool operator!=(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
    return (lhs.base() != rhs.base());
}
template <class Iterator>
bool operator<(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
    return (lhs.base() < rhs.base());
}
template <class Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
    return (lhs.base() <= rhs.base());
}
template <class Iterator>
bool operator>(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
    return (lhs.base() > rhs.base());
}
template <class Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
    return (lhs.base() >= rhs.base());
}

template <class Iterator>
reverse_iterator<Iterator> operator+(
             typename reverse_iterator<Iterator>::difference_type n,
             const reverse_iterator<Iterator>& rev_it) {
    return (rev_it + n);
}
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {
    return (rhs.base() - lhs.base());
}
// --------------- end : reverse_iterator

} // namespace ft

#endif /* ifndef __UTILS_ITERATOR_TRAITS_HPP__ */
