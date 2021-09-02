#ifndef __MAP_SRSC_INCLUDES_MAP_HPP__
# define __MAP_SRSC_INCLUDES_MAP_HPP__

# include <iostream>
# include <utility>
# include <functional>
# include <memory>
# include "bidirectional_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft {

template < class Key,                                              // map::key_type -- key
           class T,                                                // map::mapped_type -- value
           class Compare = std::less<Key>,                         // map::key_compare -- comparator
           class Alloc = std::allocator<std::pair<const Key, T> >  // map::allocator_type -- allocator
           >
class map {
 public:
     typedef Key                                        key_type;
     typedef T                                          mapped_type;
     typedef std::pair<const key_type, mapped_type>     value_type;
     typedef Compare                                    key_compare;
     // template <class Key, class T, class Compare, class Alloc>
 private:
     class value_compare {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
         friend class map;
      protected:
         Compare comp;
         value_compare(Compare c) : comp(c) {}  // constructed with map's comparison object
      public:
         typedef bool           result_type;
         typedef value_type     first_argument_type;
         typedef value_type     second_argument_type;
         bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
     };
 public:
     typedef Alloc                                      allocator_type;
     typedef value_type&                                reference;
     typedef const value_type&                          const_reference;
     typedef value_type*                                pointer;
     typedef const value_type*                          const_pointer;
     typedef BidirectionalIterator<T>                   iterator;
     typedef BidirectionalIterator<const T>             const_iterator;
     typedef ReverseIterator<T>                         reverse_iterator;
     typedef ReverseIterator<const T>                   const_reverse_iterator;
     typedef std::ptrdiff_t                             difference_type;
     typedef std::size_t                                size_type;
 private:
     // FIELDS;
     std::allocator<T>  _alloc;
     size_type          _size;
 public:
     // Default things
     explicit map(const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type());
     template <class InputIterator>
     map(InputIterator first, InputIterator last,
             const key_compare& comp = key_compare(),
             const allocator_type& alloc = allocator_type());
     map(const map& x);
     ~map();
     map& operator=(const map& x);

     // Iterators
     iterator               begin();
     const_iterator         begin() const;
     iterator               end();
     const_iterator         end() const;
     reverse_iterator       rbegin();
     const_reverse_iterator rbegin() const;
     reverse_iterator       rend();
     const_reverse_iterator rend() const;

     // Capacity
     bool       empty() const { return (_size == 0);}
     size_type  size() const { return (_size); }
     size_type  max_size() const { return (_alloc.max_size());}

     // Accessors
     mapped_type& operator[](const key_type& k);

     // Modifiers
     std::pair<iterator, bool>   insert(const value_type& val);
     iterator                   insert(iterator position, const value_type& val);
     template <class InputIterator>
     void                       insert(InputIterator first, InputIterator last);
     void                       erase(iterator position);
     size_type                  erase(const key_type& k);
     void                       erase(iterator first, iterator last);
     void                       swap(map& x);
     void                       clear();

     // Observers
     key_compare key_comp() const { return (Compare()); }
     value_compare value_comp() const { return (value_compare()); }

     // Operatrions
     iterator find(const key_type& k);
     const_iterator find(const key_type& k) const;
     size_type count(const key_type& k) const;
     iterator lower_bound(const key_type& k);
     const_iterator lower_bound(const key_type& k) const;
     iterator upper_bound(const key_type& k);
     const_iterator upper_bound(const key_type& k) const;
     std::pair<const_iterator,const_iterator> equal_range(const key_type& k) const;
     std::pair<iterator,iterator>             equal_range(const key_type& k);

     // Allocator
     allocator_type get_allocator() const { return (_alloc);}
};
}   // namespace ft

#endif /* ifndef __MAP_SRSC_INCLUDES_MAP_HPP__ */
