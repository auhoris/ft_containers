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
     typedef T                                                                  value_type;
     typedef Alloc                                                              allocator_type;
     typedef value_type&                                                        reference;
     typedef const value_type&                                                  const_reference;
     typedef value_type*                                                        pointer;
     typedef const value_type*                                                  const_pointer;
     typedef std::iterator<std::random_access_iterator_tag, value_type>         iterator;
     typedef const std::iterator<std::random_access_iterator_tag, value_type>   const_iterator;
     typedef std::reverse_iterator<iterator>                                    reverse_iterator;
     typedef const std::reverse_iterator<iterator>                              const_reverse_iterator;
     typedef std::ptrdiff_t                                                     difference_type;
     typedef std::size_t                                                        size_type;

 private:
     std::allocator<T>  _alloc;
     value_type*        _vector;
     size_type          _used_size;
     size_type          _capacity;

 public:
     //===================================
     // Default constructor: creates an empty array with size of 0
     explicit vector(const allocator_type& alloc = allocator_type())
         : _alloc(alloc), _used_size(0), _capacity(0) {
         _vector = _alloc.allocate(0);
     }
     // Fill constructor: creates an array size of n and fills with copy of val
     explicit vector(size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type())
         : _alloc(alloc) {
         _vector = _alloc.allocate(n);
         _used_size = n;
         _capacity = n;
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
         reserve(n);
         // _vector = _alloc.allocate(n);
         _used_size = n;
         // _capacity = n;
         std::uninitialized_copy(first, last, _vector);
     }
     // Copy construcor: copies a container
     vector(const vector& x) : _alloc(x._alloc), _used_size(x._used_size), _capacity(x._capacity) {
         _vector = _alloc.allocate(x.capacity());
         std::uninitialized_copy(x.begin(), x.end(), _vector);
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
         for (iterator it = begin(); it != end(); it++) {
             _alloc.destroy(it);
         }
         _alloc.deallocate(_vector, capacity());
         _used_size = copy._used_size;
         _capacity = copy._capacity;
         _vector = _alloc.allocate(_capacity);
         std::uninitialized_copy(copy.begin(), copy.end(), _vector);
         return (*this);
     }

     //===================================
     // Iterators section
     iterator begin();
     const_iterator begin() const;
     iterator end();
     const_iterator end() const;
     reverse_iterator rbegin();
     const_reverse_iterator rbegin() const;
     reverse_iterator rend();
     const_reverse_iterator rend() const;

     //===================================
     // Capacity
     size_type size() const {
         return (_used_size);
     }
     size_type max_size() const {
         return (_alloc.max_size());
     }
     void resize(size_type n, value_type val = value_type()) {
         if (n > capacity())
             reserve(n);
         for (size_type i = size(); i < n; i++)
             _alloc.construct(_vector[i], val);
         if (n < size())
         {
             for (iterator it = begin(); it != end(); it++)
                 _alloc.destroy(std::addressof(*it));
         }
         _used_size = n;
     }
     size_type capacity() const {
         return (_capacity);
     }
     bool empty() const {
         return (_capacity == 0);
     }
     void reserve (size_type n) {
         pointer    new_vector = NULL;

         if (n <= capacity())
             return ;
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
         _capacity = n;
     }
     // Element access
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
         return (*_vector);
     }
     const_reference front() const {
         return (const_reference(*_vector));
     }
     reference back() {
         return (*(_vector + (_used_size - 1)));
     }
     const_reference back() const {
         return (const_reference(*(_vector + (_used_size - 1))));
     }

     // Modifiers
     void push_back (const value_type& val) {
         if (size() == 0)
             reserve(2);
         if (size() == capacity())
             reserve(size() * 2);
         _alloc.construct(_vector + size(), val);
         _used_size++;
     }
     void pop_back() {
         _alloc.destroy(back());
         _used_size--;
     }
     void   show_data() {
         for (iterator it = begin(); it != end(); it++)
             std::cout << *it << " ";
         std::cout << '\n';
     }
};

// Iterators section
template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() {
    return (iterator(_vector));
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin() const {
    return (const_iterator(_vector));
}

template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::end() {
    return (iterator(_vector + _used_size));
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const {
    return (const_iterator(_vector + _used_size));
}

template <class T, class Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin() {
    return (reverse_iterator(end()));
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin() const {
    return (const_reverse_iterator(end()));
}

template <class T, class Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend() {
    return (reverse_iterator(begin()));
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend() const {
    return (const_reverse_iterator(begin()));
} // Iterators section end

}  // namespace ft

#endif /* ifndef __VECTOR_SRCS_INCLUDES_VECTOR_HPP__ */
