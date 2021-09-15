#ifndef __MAP_SRSC_INCLUDES_MAP_HPP__
# define __MAP_SRSC_INCLUDES_MAP_HPP__

# include <iostream>
# include <functional>
# include <memory>
# include "utils/rbtree.hpp"

namespace ft {

template < class Key,                                              // map::key_type -- key
           class T,                                                // map::mapped_type -- value
           class Compare = std::less<Key>,                         // map::key_compare -- comparator
           class Alloc = std::allocator<ft::pair<const Key, T> >  // map::allocator_type -- allocator
           >
class map {
 public:
     typedef Key                                        key_type;
     typedef T                                          mapped_type;
     typedef ft::pair<const key_type, mapped_type>     value_type;
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
     typedef rbtree<key_type, value_type, value_compare, Alloc>     rb_type;
     typedef Alloc                                      allocator_type;
     typedef typename rb_type::reference                reference;
     typedef typename rb_type::const_reference          const_reference;
     typedef typename rb_type::pointer                  pointer;
     typedef typename rb_type::const_pointer            const_pointer;
     typedef typename rb_type::iterator                 iterator;
     typedef typename rb_type::const_iterator           const_iterator;
     typedef typename rb_type::reverse_iterator         reverse_iterator;
     typedef typename rb_type::const_reverse_iterator   const_reverse_iterator;
     typedef typename rb_type::difference_type          difference_type;
     typedef typename rb_type::size_type                size_type;

 private:
     rbtree<key_type, value_type, value_compare, Alloc>   t;

 public:
     // Default things
     explicit map(const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()) : t(value_compare(comp), alloc) { }
     template <class InputIterator>
     map(InputIterator first, InputIterator last,
             const key_compare& comp = key_compare(),
             const allocator_type& alloc = allocator_type(),
             typename enable_if<!is_integral<InputIterator>::value>::type* = NULL) : t(first, last, comp, alloc) { }
     map(const map& x) : t(x.t) { }
     ~map() { }
     map& operator=(const map& x) { t = x.t; return (*this); }

     // Iterators
     iterator               begin() { return (t.begin()); }
     const_iterator         begin() const { return (t.begin()); }
     iterator               end() { return (t.end()); }
     const_iterator         end() const { return (t.end()); }
     reverse_iterator       rbegin() { return (t.rbegin()); }
     const_reverse_iterator rbegin() const { return (t.rbegin()); }
     reverse_iterator       rend() { return (t.rend()); }
     const_reverse_iterator rend() const { return (t.rend()); }

     // Capacity
     bool       empty() const { return (t.empty());}
     size_type  size() const { return (t.size()); }
     size_type  max_size() const { return (t.max_size());}

     // Accessors
     mapped_type& operator[](const key_type& k) { return ((t.insert(ft::make_pair(k, mapped_type())).first)->second); }

     // Modifiers
     ft::pair<iterator, bool>  insert(const value_type& val) { return (t.insert(val)); }
     iterator                   insert(iterator position, const value_type& val) { return (t.insert(position, val)); }
     template <class InputIterator>
     void                       insert(InputIterator first, InputIterator last,
                                typename enable_if<!is_integral<InputIterator>::value>::type* = NULL) { return (t.insert(first, last)); }
     void                       erase(iterator position) { t.erase(position); }
     size_type                  erase(const key_type& k) { t.erase(k); }
     void                       erase(iterator first, iterator last) { t.erase(first, last); }
     void                       swap(map& x);
     void                       clear() { t.clear(); }

     // Observers
     key_compare key_comp() const { return (key_comp()); }
     value_compare value_comp() const { return (value_comp()); }

     // Operatrions
     iterator find(const key_type& k) { return (t.find(k)); }
     const_iterator find(const key_type& k) const { return (t.find(k)); }
     size_type count(const key_type& k) const { return (t.count(k)); }
     iterator lower_bound(const key_type& k) { return (t.lower_bound(k)); }
     const_iterator lower_bound(const key_type& k) const { return (t.lower_bound(k)); }
     iterator upper_bound(const key_type& k) { return (t.upper_bound(k)); }
     const_iterator upper_bound(const key_type& k) const { return (t.upper_bound(k)); }
     ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const { return (t.equal_range(k)); }
     ft::pair<iterator,iterator>             equal_range(const key_type& k) { return (t.equal_range(k)); }

     // Allocator
     allocator_type get_allocator() const { return (t.get_allocator()); }
};

}   // namespace ft

#endif /* ifndef __MAP_SRSC_INCLUDES_MAP_HPP__ */
