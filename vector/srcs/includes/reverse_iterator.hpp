#ifndef __VECTOR_SRCS_INCLUDES_REVERSE_ITERATOR_HPP__
# define __VECTOR_SRCS_INCLUDES_REVERSE_ITERATOR_HPP__

# include "random_access_iterator.hpp"

namespace ft {
template<typename T>
class ReverseIterator : public RandomAccesIterator<T> {
 public:
     typedef std::random_access_iterator_tag iterator_category;
     typedef T value_type;
     typedef std::ptrdiff_t difference_type;
     typedef T* pointer;
     typedef T& reference;

 public:
     // Default
     ReverseIterator() : RandomAccesIterator<T>() { }
     ReverseIterator(pointer type) : RandomAccesIterator<T>(type) { }
     virtual ~ReverseIterator() {}
     ReverseIterator(const ReverseIterator &other) : RandomAccesIterator<T>(other) { }

     // operators
     ReverseIterator&   operator=(ReverseIterator const & other) {
         (void)other;
         using RandomAccesIterator<T>::operator=;
     }

     // arithmetic
     ReverseIterator&   operator++() {
         this->_ptr--;
         return (*this);
     }
     ReverseIterator   operator++(int) {
         ReverseIterator tmp(*this);

         operator++();
         return (tmp);
     }
     ReverseIterator&   operator--() {
         this->_ptr++;
         return (*this);
     }
     ReverseIterator   operator--(int) {
         ReverseIterator tmp(*this);

         operator--();
         return (tmp);
     }
     ReverseIterator&  operator+=(const difference_type & move) {
         this->_ptr -= move;
         return (*this);
     }
     ReverseIterator&  operator-=(const difference_type & move) {
         this->_ptr += move;
         return (*this);
     }
     pointer     operator+(const difference_type & move) {
         return (this->_ptr - move);
     }
     pointer     operator-(const difference_type & move) {
         return (this->_ptr + move);
     }
     difference_type    operator-(ReverseIterator const & iter) {
         return (std::distance(iter._ptr, this->_ptr));
     }
};

} // namespace ft
#endif /* ifndef __VECTOR_SRCS_INCLUDES_REVERSE_ITERATOR_HPP__ */
