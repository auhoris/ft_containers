#ifndef __VECTOR_SRCS_RANDOM_ACCESS_ITERATOR_HPP__
# define __VECTOR_SRCS_RANDOM_ACCESS_ITERATOR_HPP__

# include <bitset>
# include <cstddef>
# include <iterator>

namespace ft {
template<typename T>
class RandomAccesIterator : public std::iterator<std::random_access_iterator_tag, T> {
 public:
     typedef std::random_access_iterator_tag iterator_category;
     typedef T value_type;
     typedef std::ptrdiff_t difference_type;
     typedef T* pointer;
     typedef T& reference;

 protected:
     T*    _ptr;

 public:
     // Default things
     RandomAccesIterator() : _ptr(NULL) { };
     RandomAccesIterator(pointer type) : _ptr(type) { };
     virtual ~RandomAccesIterator() { }
     RandomAccesIterator(const RandomAccesIterator &copy) : _ptr(copy._ptr) { }

     // operators
     RandomAccesIterator&    operator=(RandomAccesIterator const & copy) {
         if (this == &copy)
             return (*this);
         _ptr = copy._ptr;
         return (*this);
     }

     // logical
     bool   operator==(RandomAccesIterator const & other) { return (_ptr == other._ptr); }
     bool   operator!=(RandomAccesIterator const & other) { return (_ptr != other._ptr); }
     bool   operator<(RandomAccesIterator const & other) { return (_ptr < other._ptr); }
     bool   operator>(RandomAccesIterator const & other) { return (_ptr > other._ptr); }
     bool   operator<=(RandomAccesIterator const & other) { return (_ptr <= other._ptr); }
     bool   operator>=(RandomAccesIterator const & other) { return (_ptr >= other._ptr); }

     // arithmetic
     RandomAccesIterator&   operator++() {
         _ptr++;
         return (*this);
     }
     RandomAccesIterator   operator++(int) {
         RandomAccesIterator tmp(*this);

         operator++();
         return (tmp);
     }
     RandomAccesIterator&   operator--() {
         _ptr--;
         return (*this);
     }
     RandomAccesIterator   operator--(int) {
         RandomAccesIterator tmp(*this);

         operator--();
         return (tmp);
     }
     RandomAccesIterator&  operator+=(const difference_type & move) {
         _ptr += move;
         return (*this);
     }
     RandomAccesIterator&  operator-=(const difference_type & move) {
         _ptr -= move;
         return (*this);
     }
     pointer     operator+(const difference_type & move) {
         return (_ptr + move);
     }
     pointer     operator-(const difference_type & move) {
         return (_ptr - move);
     }
     difference_type    operator-(RandomAccesIterator const & iter) {
         return (std::distance(iter._ptr, _ptr));
     }

     // other
     T&         operator*() { return (*_ptr); }
     const T&   operator*() const { return (*_ptr); }
     T*         operator->() { return (_ptr); }
     T          operator[](difference_type n) {
         return (_ptr[n]);
     }
};

}   // namespace ft

#endif /* ifndef __VECTOR_SRCS_RANDOM_ACCESS_ITERATOR_HPP__ */
