#ifndef __VECTOR_SRCS_INCLUDES_REVERSE_ITERATOR_HPP__
# define __VECTOR_SRCS_INCLUDES_REVERSE_ITERATOR_HPP__

# include "bidirectional_iterator.hpp"

namespace ft {
template<typename T>
class ReverseIterator : public BidirectionalIterator<T> {
 public:
     typedef std::random_access_iterator_tag iterator_category;
     typedef T value_type;
     typedef std::ptrdiff_t difference_type;
     typedef T* pointer;
     typedef T& reference;

 public:
     // Default
     ReverseIterator() : BidirectionalIterator<T>() { }
     ReverseIterator(pointer type) : BidirectionalIterator<T>(type) { }
     virtual ~ReverseIterator() {}
     ReverseIterator(const ReverseIterator &other) : BidirectionalIterator<T>(other) { }

     // operators
     ReverseIterator&   operator=(ReverseIterator const & other) {
         (void)other;
         using BidirectionalIterator<T>::operator=;
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
};

} // namespace ft
#endif /* ifndef __VECTOR_SRCS_INCLUDES_REVERSE_ITERATOR_HPP__ */
