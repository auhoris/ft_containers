#ifndef __VECTOR_SRCS_INCLUDES_VECTOR_HPP__
#define __VECTOR_SRCS_INCLUDES_VECTOR_HPP__

#include <cstddef>
#include <iostream>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>

#include "utils/algorithm.hpp"
#include "utils/iterator.hpp"
#include "utils/type_traits.hpp"
#include "utils/vector_iterator.hpp"

namespace ft {

template <class T, class Alloc = std::allocator<T> >
class vector {
   public:
    // Definitions for types
    typedef T value_type;
    typedef Alloc allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef VectorIterator<T, false> iterator;
    typedef VectorIterator<T, true> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef typename iterator_traits<iterator>::difference_type difference_type;
    typedef std::size_t size_type;

   private:
    allocator_type _alloc;
    pointer _vector;
    size_type _used_size;
    size_type _capacity;

   public:
    //===================================
    // Default constructor: creates an empty array with size of 0
    explicit vector(const allocator_type& alloc = allocator_type())
        : _alloc(alloc), _used_size(0), _capacity(0) {
        _vector = _alloc.allocate(_capacity);
    }
    // Fill constructor: creates an array size of n and fills with copy of val
    explicit vector(size_type n, const value_type& val = value_type(),
                    const allocator_type& alloc = allocator_type())
        : _alloc(alloc), _vector(NULL), _used_size(0), _capacity(0) {
        reserve(n);
        for (size_type i = 0; i < n; i++) {
            push_back(val);
        }
    }
    // Range constructor: Constructs a container with as many elements
    // as the range [first,last), with each element constructed from
    // its corresponding element in that range, in the same order.
    template <class InputIterator>
    vector(InputIterator first, InputIterator last,
           const allocator_type& alloc = allocator_type(),
           typename enable_if<!is_integral<InputIterator>::value>::type* = 0)
        : _alloc(alloc), _vector(0), _used_size(0), _capacity(0) {
        for (; first != last; first++) {
            push_back(*first);
        }
    }
    // Copy construcor: copies a container
    vector(const vector& copy)
        : _alloc(copy._alloc), _vector(0), _used_size(0), _capacity(0) {
        _vector = _alloc.allocate(0);
        reserve(copy.capacity());
        try {
            for (size_type i = 0; i < copy.size(); i++) {
                push_back(copy[i]);
            }
        } catch (...) {
            clear();
            _alloc.deallocate(_vector, _capacity);
            throw;
        }
    }
    // Destructor: destroyes and deallocates all elements
    ~vector() {
        clear();
        _alloc.deallocate(_vector, capacity());
    }
    vector& operator=(const vector& copy) {
        if (this == &copy) return (*this);
        if (capacity() <= copy.size()) {
            clear();
            for (size_type i = 0; i < copy.size(); i++) {
                push_back(copy[i]);
            }
        } else {
            vector tmp(copy);
            tmp.swap(*this);
        }
        // clear();
        // _alloc.deallocate(_vector, capacity());
        // _vector = _alloc.allocate(0);
        // _capacity = 0;
        // for (const_iterator it = copy.begin(); it != copy.end(); it++) {
        //     push_back(*it);
        // }
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
    size_type size() const { return (_used_size); }
    size_type max_size() const { return (_alloc.max_size()); }
    void resize(size_type n, value_type val = value_type()) {
        if (n > capacity()) {
            reserve(n);
        }
        for (size_type i = size(); i < n; i++) {
            _alloc.construct(_vector + i, val);
        }
        if (n < size()) {
            for (size_type i = n; i < size(); i++) {
                _alloc.destroy(_vector + i);
            }
        }
        _used_size = n;
    }
    size_type capacity() const { return (_capacity); }
    bool empty() const { return (_used_size == 0); }
    void reserve(size_type n) {
        pointer new_vector = NULL;

        if (n > max_size()) throw std::bad_alloc();
        if (n <= capacity()) return;
        new_vector = _alloc.allocate(n);
        try {
            std::uninitialized_copy(begin(), end(), new_vector);
        } catch (...) {
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
    reference operator[](size_type n);
    const_reference operator[](size_type n) const;
    reference at(size_type n);
    const_reference at(size_type n) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    // Modifiers
    template <class InputIterator>
    void assign(
        InputIterator first, InputIterator last,
        typename enable_if<!is_integral<InputIterator>::value>::type* = NULL) {
        difference_type tmp;

        tmp = last - first;
        reserve(tmp);
        clear();
        while (first != last) {
            push_back(*first++);
        }
        // std::uninitialized_copy(first, last, _vector);
        // _used_size = tmp;
    }
    void assign(size_type n, const value_type& val) {
        reserve(n);
        clear();
        for (size_type i = 0; i != n; i++) {
            push_back(val);
            // _alloc.construct(_vector + i, val);
        }
        // _used_size = n;
    }
    void push_back(const value_type& val) {
        if (size() == 0) reserve(1);
        if (size() == capacity()) reserve(size() * 2);
        _alloc.construct(_vector + size(), val);
        _used_size++;
    }
    void pop_back() {
        _alloc.destroy(std::addressof(*--end()));
        _used_size--;
    }
    iterator insert(iterator position, const value_type& val) {
        size_type pos;

        pos = position - begin();
        insert(position, 1, val);
        // if (_used_size + 1 >= _capacity) {
        //     reserve(_used_size * 2);
        // }
        // size_type i = _used_size++;
        // for (; i > pos; i--) {
        //     _alloc.construct(_vector + i, _vector[i - 1]);
        // }
        // _alloc.destroy(_vector + i);
        // _alloc.construct(_vector + i, val);
        return (begin() + pos);
    }
    void insert(iterator position, size_type n, const value_type& val) {
        size_type pos = position - begin();

        if (_used_size + n >= _capacity) reserve(_used_size + n);
        size_type i = _used_size;
        for (; i > pos; i--) {
            _alloc.construct(_vector + i + n - 1, _vector[i - 1]);
        }
        _used_size += n;
        for (; i < pos + n; i++) {
            _alloc.destroy(_vector + i);
            _alloc.construct(_vector + i, val);
        }
    }
    template <class InputIterator>
    void insert(
        iterator position, InputIterator first, InputIterator last,
        typename enable_if<!is_integral<InputIterator>::value>::type* = NULL) {
        size_type pos = ft::distance(begin(), position);
        size_type n = last - first;

        if (_used_size + n >= _capacity) reserve(_used_size + n);
        size_type i = _used_size;
        for (; i > pos; i--) {
            _alloc.construct(_vector + i + n - 1, _vector[i - 1]);
        }
        _used_size += n;
        for (; i < pos + n; i++) {
            _alloc.destroy(_vector + i);
            _alloc.construct(_vector + i, *first++);
        }
    }
    iterator erase(iterator position) { return (erase(position, ++position)); }
    iterator erase(iterator first, iterator last) {
        size_type pos = first - begin();
        iterator ret;
        size_type n = last - first;

        if (n == _used_size) {
            clear();
            return (begin());
        }
        size_type i = pos;
        for (; i < n + pos; i++) {
            _alloc.destroy(_vector + i);
        }
        ret = begin() + i;
        for (; i < _used_size; i++) {
            _alloc.construct(_vector + i - n, _vector[i]);
        }
        _used_size -= n;
        return (ret);
    }
    void swap(vector& x) {
        std::swap(_alloc, x._alloc);
        std::swap(_vector, x._vector);
        std::swap(_used_size, x._used_size);
        std::swap(_capacity, x._capacity);
    }
    // ===========================
    void clear() {
        for (size_type i = 0; i < _used_size; i++) {
            _alloc.destroy(_vector + i);
        }
        _used_size = 0;
    }
    void show_data() {
        std::cout << "size = " << size() << " ";
        std::cout << "capacity = " << capacity() << std::endl;
        for (iterator it = begin(); it != end(); it++) {
            std::cout << *it << " ";
        }
        std::cout << '\n';
    }
    // Accessors
    allocator_type get_allocator() const { return (_alloc); }
};

// Non member
template <class T, class Alloc>
void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {
    x.swap(y);
}

template <class T, class Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    size_t i;
    size_t size;

    size = lhs.size();
    if (size != rhs.size()) return (false);
    i = 0;
    while (i < size && lhs[i] == rhs[i]) i++;
    return (i == size);
}

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return (!(lhs == rhs));
}

template <class T, class Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    if (lhs.size() < rhs.size()) return (true);
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                    rhs.end()));
}

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return (!(rhs < lhs));
}

template <class T, class Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return (rhs < lhs);
}

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return (!(lhs < rhs));
}

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
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin()
    const {
    return (const_reverse_iterator(end()));
}

template <class T, class Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend() {
    return (reverse_iterator(begin()));
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend()
    const {
    return (const_reverse_iterator(begin()));
}
// Iterators section end

// Element access
template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](size_type n) {
    return (*(_vector + n));
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](
    size_type n) const {
    return (*(_vector + n));
}

template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type n) {
    if (n < 0 || n > size() || size() == 0)
        throw std::out_of_range("ft_vector: out of range");
    return (_vector[n]);
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(
    size_type n) const {
    if (n < 0 || n > size()) throw std::out_of_range("ft_vector: out of range");
    return (_vector[n]);
}

template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::front() {
    return (*begin());
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const {
    return (*begin());
}

template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::back() {
    return (*--end());
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const {
    return (*--end());
}  // Element access end

}  // namespace ft

#endif /* ifndef __VECTOR_SRCS_INCLUDES_VECTOR_HPP__ */
