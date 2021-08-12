#ifndef __VECTOR_SRCS_INCLUDES_VECTOR_HPP__
# define __VECTOR_SRCS_INCLUDES_VECTOR_HPP__

# include <iterator>
# include <memory>
# include <iostream>
# include <stdexcept>

// Using own namespace
namespace ft {

template < class T, class Alloc = std::allocator<T> >
class vector {
 public:
     // Definitions for types
     typedef T                                          value_type;
     typedef Alloc                                      allocator_type;
     typedef value_type&                                reference;
     typedef const value_type&                          const_reference;
     typedef value_type*                                pointer;
     typedef const value_type*                          const_pointer;
     typedef value_type*                                iterator;
     typedef const value_type*                          const_iterator;
     typedef std::reverse_iterator<value_type>          reverse_iterator;
     typedef const std::reverse_iterator<value_type>    const_reverse_iterator;
     typedef std::ptrdiff_t                             difference_type;
     typedef std::size_t                                size_type;

 private:
     std::allocator<T>  _alloc;
     value_type*        _vector;
     iterator           _start;
     iterator           _finish;
     iterator           _end_of_storage;

 public:
     //===================================
     // Default constructor: creates an empty array with size of 0
     explicit vector(const allocator_type& alloc = allocator_type())
         : _alloc(alloc) {
         _vector = _alloc.allocate(0);
         _start = _vector;
         _finish = _start;
         _end_of_storage = _finish;
     }
     // Fill constructor: creates an array size of n and fills with copy of val
     explicit vector(size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type())
         : _alloc(alloc) {
         _vector = _alloc.allocate(n);
         _start = _vector;
         _finish = _start + n;
         _end_of_storage = _finish;
         for (size_type i = 0; i < n; i++) {
             _alloc.construct(_vector + i, val);
         }
     }
     // Range constructor: Constructs a container with as many elements
     // as the range [first,last), with each element constructed from
     // its corresponding element in that range, in the same order.
     template <class InputIterator>
     vector(InputIterator first, InputIterator last,
             const allocator_type& alloc = allocator_type()) : _alloc(alloc) {
         size_type  n = 0;

         n = std::distance(first, last);
         _vector = _alloc.allocate(n);
         _start = _vector;
         _finish = std::uninitialized_copy(first, last, _start);
         _end_of_storage = _finish;
     }
     // Copy construcor: copies a container
     vector(const vector& x) : _alloc(x._alloc) {
         // size_type  i;

         _vector = _alloc.allocate(x.capacity());
         // std::cout << "capacity in copy construcor: " << x.capacity() << std::endl;
         _start = _vector;
         _finish = std::uninitialized_copy(x.begin(), x.end(), _start);
         // _finish = _start + x.size();
         _end_of_storage = _start + x.capacity();
         std::cout << size() << std::endl;
         /* i = 0;
         for (const_iterator it = x.begin(); it != x.end(); it++, i++) {
             _alloc.construct(_vector[i], x[i]);
         } */
     }
     // Destructor: destroyes and deallocates all elements
     ~vector() {
         for (iterator it = begin(); it != end(); it++) {
             _alloc.destroy(std::addressof(*it));
         }
         _alloc.deallocate(_vector, capacity());
     }
     vector& operator=(const vector& copy) {
         if (this == &copy)
             return (*this);
         for (iterator it = begin(); it != end(); it++)
             _alloc.destroy(std::addressof(*it));
         _alloc.deallocate(_vector, capacity());
         _vector = _alloc.allocate(copy.capacity());
         _finish = std::uninitialized_copy(copy.begin(), copy.end(), _start);
         _end_of_storage = _start + copy.capacity();
         return (*this);
     }

     //===================================
     // Iterators section
     iterator begin() {
         return (_start);
     }
     const_iterator begin() const {
         return (const_iterator(_start));
     }
     iterator end() {
         return (_finish);
     }
     const_iterator end() const {
          return (const_iterator(_finish));
     }
     reverse_iterator rbegin() {
         return (reverse_iterator(end()));
     }
     const_reverse_iterator rbegin() const {
         return (const_reverse_iterator(end()));
     }
     reverse_iterator rend() {
         return (reverse_iterator(begin()));
     }
     const_reverse_iterator rend() const {
         return (const_reverse_iterator(begin()));
     }

     //===================================
     // Capacity
     size_type size() const {
         return (_finish - _start);
     }
     size_type max_size() const {
         return (_alloc.max_size());
     }
     void resize (size_type n, value_type val = value_type()) {
         if (n > capacity())
             reserve(n);
         for (size_type i = size(); i < n; i++)
             _alloc.construct(_vector[i], val);
         if (n < size())
         {
             for (iterator it = begin(); it != end(); it++)
                 _alloc.destroy(std::addressof(*it));
         }
         _finish = _start + n;
     }
     size_type capacity() const {
         // std::cout << "in function: " << _end_of_storage - _start << std::endl;
         return (_end_of_storage - _start);
     }
     bool empty() const {
         return (_start == _finish);
     }
     void reserve (size_type n) {
         pointer    new_vector = NULL;

         if (n <= capacity())
         {
             return ;
         }
         new_vector = _alloc.allocate(n);
         try {
             std::uninitialized_copy(begin(), end(), new_vector);
         } catch(...) {
             _alloc.deallocate(new_vector, n);
             throw;
         }
         for (iterator it = begin(); it != end(); it++)
             _alloc.destroy(std::addressof(*it));
         _alloc.deallocate(_vector, capacity());
         _vector = new_vector;
         // Хз надо ли это: по логике надо, т.к. _vector указывает на другую область памяти теперь
         _start = _vector;
         _finish = _start + size();
         _end_of_storage = _start + n;
     }
     reference operator[] (size_type n) {
         return (_vector[n]);
     }
     const_reference operator[] (size_type n) const {
         return (const_reference(_vector[n]));
     }
     reference at (size_type n) {
         if (n < 0 || n > size())
             throw std::out_of_range("ft_vector: out of range");
         return (_vector[n]);
     }
     const_reference at (size_type n) const {
         if (n < 0 || n > size())
             throw std::out_of_range("ft_vector: out of range");
         return (const_reference(_vector[n]));
     }
     reference front() {
         return (*_start);
     }
     const_reference front() const {
         return (const_reference(*_start));
     }
     reference back() {
         return (*(_finish - 1));
     }
     const_reference back() const {
         return (const_reference(*(_finish - 1)));
     }
     void push_back (const value_type& val) {
         if (size() == capacity())
         {
             reserve(size() * 2);
             _end_of_storage = _start + size() * 2;
         }
         _alloc.construct(_vector + size(), val);
         _finish++;
     }
     void pop_back() {
         _alloc.destroy(--_finish);
     }
     void   show_data() {
         for (iterator it = begin(); it != end(); it++)
             std::cout << *it << " ";
         std::cout << '\n';
     }
};

}  // namespace ft

#endif /* ifndef __VECTOR_SRCS_INCLUDES_VECTOR_HPP__ */
