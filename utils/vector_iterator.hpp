#ifndef __UTILS_VECTOR_ITERATOR_HPP__
# define __UTILS_VECTOR_ITERATOR_HPP__

# include <bitset>
# include <cstddef>
#include <iterator>
# include "iterator.hpp"
# include "utils.hpp"

namespace ft {
template<typename T, bool IsConst>
class VectorIterator : public iterator<random_access_iterator_tag, T> {
 public:
     typedef typename conditional<IsConst, const T, T>::type    value_type;
     typedef typename conditional<IsConst, const T*, T*>::type  pointer;
     typedef typename conditional<IsConst, const T&, T&>::type  reference;
     typedef random_access_iterator_tag                         iterator_category;
     typedef ptrdiff_t                                          difference_type;

 protected:
     pointer    _iter;

 public:
     // Default things
     VectorIterator() : _iter() { }
     VectorIterator(pointer type) : _iter(type) { };
     virtual ~VectorIterator() { }
     VectorIterator(const VectorIterator<T, IsConst> &copy) : _iter(copy._iter) { }

     // operators
     VectorIterator<T, IsConst>&    operator=(VectorIterator<T, IsConst> const & copy) {
         if (this == &copy)
             return (*this);
         _iter = copy._iter;
         return (*this);
     }
     /* VectorIterator<T, IsConst>&    operator=(VectorIterator<T, true> & copy) {
         if (this == &copy)
             return (*this);
         _iter = copy._iter;
         return (*this);
     } */
     operator VectorIterator<T, true>() const {
         return (VectorIterator<T, true>(_iter));
     }

     // logical
     bool   operator==(VectorIterator<T, IsConst> const & other) { return (_iter == other._iter); }
     bool   operator!=(VectorIterator<T, IsConst> const & other) { return (_iter != other._iter); }
     bool   operator<(VectorIterator<T, IsConst> const & other) { return (_iter < other._iter); }
     bool   operator>(VectorIterator<T, IsConst> const & other) { return (_iter > other._iter); }
     bool   operator<=(VectorIterator<T, IsConst> const & other) { return (_iter <= other._iter); }
     bool   operator>=(VectorIterator<T, IsConst> const & other) { return (_iter >= other._iter); }

     // arithmetic
     VectorIterator<T, IsConst>&   operator++() {
         _iter++;
         return (*this);
     }
     VectorIterator<T, IsConst>   operator++(int) {
         VectorIterator<T, IsConst> tmp(*this);

         operator++();
         return (tmp);
     }
     VectorIterator<T, IsConst>&   operator--() {
         _iter--;
         return (*this);
     }
     VectorIterator<T, IsConst>   operator--(int) {
         VectorIterator<T, IsConst> tmp(*this);

         operator--();
         return (tmp);
     }
     VectorIterator<T, IsConst>&  operator+=(const difference_type & move) {
         _iter += move;
         return (*this);
     }
     VectorIterator<T, IsConst>&  operator-=(const difference_type & move) {
         _iter -= move;
         return (*this);
     }
     pointer     operator+(const difference_type & move) {
         return (_iter + move);
     }
     pointer     operator-(const difference_type & move) {
         return (_iter - move);
     }
     difference_type    operator-(VectorIterator<T, IsConst> const & iter) {
         return (std::distance(_iter, iter._iter));
     }

     // other
     reference   operator*() { return (*_iter); }
     reference   operator*() const { return (*_iter); }
     pointer     operator->() { return (_iter); }
     value_type  operator[](difference_type n) { return (*(_iter + n)); }
};

}   // namespace ft

#endif /* ifndef __UTILS_VECTOR_ITERATOR_HPP__ * */
