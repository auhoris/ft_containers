#ifndef __SET_HPP__
#define __SET_HPP__

#include "utils/rbtree.hpp"

namespace ft {
template <class Key, class Compare = std::less<Key>,
          class Alloc = std::allocator<Key> >
class set {
 public:
    typedef Key key_type;
    typedef Key value_type;
    typedef Compare key_compare;
    typedef Compare value_compare;
    typedef rbtree<value_type, value_compare, Alloc> rb_type;
    typedef Alloc allocator_type;
    typedef typename rb_type::reference reference;
    typedef typename rb_type::const_reference const_reference;
    typedef typename rb_type::pointer pointer;
    typedef typename rb_type::const_pointer const_pointer;
    typedef typename rb_type::iterator iterator;
    typedef typename rb_type::const_iterator const_iterator;
    typedef typename rb_type::reverse_iterator reverse_iterator;
    typedef typename rb_type::const_reverse_iterator const_reverse_iterator;
    typedef typename rb_type::difference_type difference_type;
    typedef typename rb_type::size_type size_type;

 private:
    rbtree<value_type, value_compare, Alloc> t;

 public:
    explicit set(const key_compare& comp = key_compare(),
                 const allocator_type& alloc = allocator_type())
        : t(value_compare(comp), alloc) {}
    template <class InputIterator>
    set(InputIterator first, InputIterator last,
        const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type(),
        typename enable_if<!is_integral<InputIterator>::value>::type* = NULL)
        : t(first, last, comp, alloc) {}
    set(const set& x) : t(x.t) {}
    ~set() {}
    set& operator=(const set& x) {
        t = x.t;
        return (*this);
    }

    // Iterators
    iterator begin() { return (t.begin()); }
    const_iterator begin() const { return (t.begin()); }
    iterator end() { return (t.end()); }
    const_iterator end() const { return (t.end()); }
    reverse_iterator rbegin() { return (t.rbegin()); }
    const_reverse_iterator rbegin() const { return (t.rbegin()); }
    reverse_iterator rend() { return (t.rend()); }
    const_reverse_iterator rend() const { return (t.rend()); }

    // Capacity
    bool empty() const { return (t.empty()); }
    size_type size() const { return (t.size()); }
    size_type max_size() const { return (t.max_size()); }

    // Modifiers
    ft::pair<iterator, bool> insert(const value_type& val) {
        return (t.insert(val));
    }
    iterator insert(iterator position, const value_type& val) {
        return (t.insert(position, val));
    }
    template <class InputIterator>
    void insert(
        InputIterator first, InputIterator last,
        typename enable_if<!is_integral<InputIterator>::value>::type* = NULL) {
        return (t.insert(first, last));
    }
    void erase(iterator position) { t.erase(position); }
    size_type erase(const key_type& k) { return (t.erase(k)); }
    void erase(iterator first, iterator last) { t.erase(first, last); }
    void swap(set& x) { t.swap(x.t); }
    void clear() { t.clear(); }

    // Observers
    key_compare key_comp() const { return (key_comp()); }
    value_compare value_comp() const { return (value_comp()); }

    // Operatrions
    iterator find(const key_type& k) { return (t.find(k)); }
    const_iterator find(const key_type& k) const { return (t.find(k)); }
    size_type count(const key_type& k) const { return (t.count(k)); }
    iterator lower_bound(const key_type& k) { return (t.lower_bound(k)); }
    const_iterator lower_bound(const key_type& k) const {
        return (t.lower_bound(k));
    }
    iterator upper_bound(const key_type& k) { return (t.upper_bound(k)); }
    const_iterator upper_bound(const key_type& k) const {
        return (t.upper_bound(k));
    }
    ft::pair<const_iterator, const_iterator> equal_range(
        const key_type& k) const {
        return (t.equal_range(k));
    }
    ft::pair<iterator, iterator> equal_range(const key_type& k) {
        return (t.equal_range(k));
    }

    // Allocator
    allocator_type get_allocator() const { return (t.get_allocator()); }
};

}  // namespace ft
#endif /* ifndef __SET_HPP__ */
