#ifndef __MAP_SRCS_INCLUDES_RBTREE_HPP__
# define __MAP_SRCS_INCLUDES_RBTREE_HPP__

# include <iostream>
# include <cstddef>
# include <functional>
# include <memory>
# include <string>
# include "utility.hpp"
# include "rbtree_iterator.hpp"

# define YELLOW  "\033[33m"      /* Yellow */
# define BLACK   "\033[30m"      /* Black */
# define RED     "\033[31m"      /* Red */
# define RESET   "\033[0m"

namespace ft {

template < class Key,
           class Value,
           class Compare = std::less<Value>,
           class Alloc = std::allocator<Value>,
           class Node_alloc = std::allocator<Node<Value> > >
class rbtree {
 public:    // Main Typedefs
     typedef Key                                                    key_type;
     typedef Value                                                  value_type;
     typedef Compare                                                key_compare;
     typedef Alloc                                                  allocator_type;
     typedef Node_alloc                                             node_allocator_type;
     typedef typename allocator_type::reference                     reference;
     typedef typename allocator_type::const_reference               const_reference;
     typedef typename allocator_type::pointer                       pointer;
     typedef typename allocator_type::const_pointer                 const_pointer;
     typedef RBTreeIterator<Value, false>                           iterator;
     typedef RBTreeIterator<Value, true>                            const_iterator;
     typedef ft::reverse_iterator<iterator>                         reverse_iterator;
     typedef ft::reverse_iterator<const_iterator>                   const_reverse_iterator;
     typedef typename iterator_traits<iterator>::difference_type    difference_type;
     typedef std::size_t                                            size_type;

 private:   // Fields
     // Node typedefs
     typedef Node<value_type>  Node;
     typedef Node*             link_type;
     link_type                      _root;
     link_type                      _header;
     link_type                      _nil;    // для экономии памяти - будет являться конечным узлом
     Compare                        _comp;
     std::allocator<value_type>     _valloc;
     std::allocator<Node>           _nalloc;
     size_type                      _size;

 private:   // Functions section
     // Accessors to Node fields =======================
     reference        value(link_type nd) { return (*nd->value); }
     bool&            color(link_type nd) { return (nd->color); }
     link_type&       left(link_type x) { return (x->left); }
     link_type&       right(link_type x) { return (x->right); }
     link_type&       left(link_type x) const { return (x->left); }
     link_type&       right(link_type x) const { return (x->right); }
     link_type&       parent(link_type x) { return (x->parent); }

     // Utils ==========================================
     link_type&       leftmost() { return (left(_header)); }
     link_type&       leftmost() const { return (left(_header)); }
     link_type&       rightmost() { return (right(_header)); }
     link_type&       rightmost() const { return (right(_header)); }
     link_type        minimum(link_type x);
     link_type        maximum(link_type x);
     pointer          create_value(const_reference val);
     link_type        create_node(link_type childs = NULL, link_type parent = NULL, pointer value = NULL);
     bool             _is_red(link_type nd);
     void             _clear(link_type nd);
     iterator         _insert(link_type insert_to, link_type node, const_reference val);
     iterator         _insert_fixup(link_type & node);
     void             _rotate_right(link_type nd);
     void             _rotate_left(link_type nd);
     void             _swap_colors(link_type nd);
     void             _transplant(link_type u, link_type v);
     void             _delete_fixup(link_type node);
     void             _clear_node(link_type node);
     void             _delete_node(link_type node);
     void             _show(link_type nd, int place);

 public:    // Member funcs
     link_type      search(const value_type & val);

     // Default things
     explicit rbtree(const key_compare& comp = key_compare(),
             const allocator_type& allocator = allocator_type(),
             const node_allocator_type & nallocator = node_allocator_type());
     template <class InputIterator>
     rbtree(InputIterator first, InputIterator last, 
             const key_compare & comp = key_compare(),
             const allocator_type & allocator = allocator_type(),
             const node_allocator_type & nallocator = node_allocator_type(),
             typename enable_if<!is_integral<InputIterator>::value>::type* = NULL);
     rbtree(const rbtree & copy);
     ~rbtree();
     rbtree&    operator=(const rbtree & copy);

     // Iterators
     iterator begin() { return (leftmost()); }
     const_iterator begin() const { return (leftmost()); }
     iterator end() { return (_header); }
     const_iterator end() const { return (_header); }
     reverse_iterator rbegin() { return (reverse_iterator(end())); }
     const_reverse_iterator rbegin() const { return (reverse_iterator(end())); }
     reverse_iterator rend() { return (reverse_iterator(begin())); }
     const_reverse_iterator rend() const { return (reverse_iterator(begin())); }

     // Capacity
     bool empty() const { return (_size == 0); }
     size_type  size() const { return (_size); }
     size_type max_size() const { return (_nalloc.max_size()); }

     // Modifiers
     typedef ft::pair<iterator, bool> pair_iterator_bool;
     pair_iterator_bool     insert(const_reference val);
     iterator               insert(iterator position, const value_type& val);
     template <class InputIterator>
     void insert(InputIterator first, InputIterator last,
             typename enable_if<!is_integral<InputIterator>::value>::type* = NULL)
     { while (first != last) insert(*first++); }
     void erase(iterator position) {
         if (position.node() == _header)
             return;
         _delete_node(position.node());
     }
     size_type erase(const value_type & val) {
         erase(iterato(search(val)));
         return (1);
     }
     void erase(iterator first, iterator last) {
         iterator   tmp;

         while (first != last) {
             tmp = first;
             first++;
             erase(tmp);
         }
     }
     void clear() { erase(begin(), end()); }

     // Operations
     iterator find(const value_type & val) {
         link_type  found = search(val);
         if (found == _nil)
             return (end());
         return (iterator(search(val)));
     }
     const_iterator find(const value_type & val) const {
         link_type  found = search(val);
         if (found == _nil)
             return (end());
         return (const_iterator(search(val)));

     }
     size_type count(const value_type & val) const { return (search(val) != _nil ? 1 : 0); }
     iterator lower_bound(const value_type & val) {
         return (find(val));
     }
     const_iterator lower_bound(const value_type & val) const {
         return (find(val));
     }
     iterator upper_bound(const value_type & val) {
         iterator   found = find(val);
         return (++found);
     }
     const_iterator upper_bound(const value_type & val) const {
         iterator   found = find(val);
         return (++found);
     }
     typedef ft::pair<const_iterator, const_iterator>  const_iterator_pair;
     typedef ft::pair<iterator, iterator>              iterator_pair;
     const_iterator_pair    equal_range(const value_type & val) const { return (ft::make_pair(lower_bound(val), upper_bound(val))); }
     iterator_pair          equal_range(const value_type & val) { return (ft::make_pair(lower_bound(val), upper_bound(val))); }

     // Allocator
     allocator_type get_allocator() const { return (allocator_type()); }

     // Random helpers
     void           show();
};

template <class Key, class T, class Compare, class Alloc, class Node_alloc>
rbtree<Key, T, Compare, Alloc, Node_alloc>::rbtree(const key_compare& comp,
         const allocator_type& valloc,
         const node_allocator_type & nalloc) : _comp(comp), _valloc(valloc), _nalloc(nalloc), _size(0) {
     _nil = create_node();
     _root = _nil;
     _header = create_node(_root, NULL, create_value(value_type()));
     color(_header) = true;
     leftmost() = _header;
     rightmost() = _header;
}

template <class Key, class T, class Compare, class Alloc, class Node_alloc>
template <class InputIterator>
rbtree<Key, T, Compare, Alloc, Node_alloc>::rbtree(InputIterator first, InputIterator last, 
        const key_compare & comp,
        const allocator_type & allocator,
        const node_allocator_type & nallocator,
        typename enable_if<!is_integral<InputIterator>::value>::type*) : _comp(comp), _valloc(allocator), _nalloc(nallocator) {
     _nil = create_node();
     _root = _nil;
     _header = create_node(_root, NULL, create_value(value_type()));
     color(_header) = true;
     leftmost() = _header;
     rightmost() = _header;
     insert(first, last);
}

template <class Key, class T, class Compare, class Alloc, class Node_alloc>
rbtree<Key, T, Compare, Alloc, Node_alloc>::rbtree(const rbtree & copy) : _comp(copy._comp), _valloc(copy._valloc), _nalloc(copy._nalloc), _size(0) {
     _nil = create_node();
     _root = _nil;
     _header = create_node(_root, NULL, create_value(value_type()));
     color(_header) = true;
     leftmost() = _header;
     rightmost() = _header;
     insert(copy.begin(), copy.end());
}

template <class Key, class T, class Compare, class Alloc, class Node_alloc>
rbtree<Key, T, Compare, Alloc, Node_alloc>::~rbtree() {
    _clear(_root);
    _nalloc.destroy(_nil);
    _nalloc.deallocate(_nil, 1);
    _valloc.destroy(_header->value);
    _valloc.deallocate(_header->value, 1);
    _nalloc.destroy(_header);
    _nalloc.deallocate(_header, 1);
}

template <class Key, class T, class Compare, class Alloc, class Node_alloc>
rbtree<Key, T, Compare, Alloc, Node_alloc>&
rbtree<Key, T, Compare, Alloc, Node_alloc>::
operator=(const rbtree & copy) {
    if (this == &copy)
        return (*this);
    insert(copy.begin(), copy.end());
    return (*this);
}

//  Helper Functions =============================
template <class Key,class T, class Compare, class Alloc, class Node_alloc>
bool   rbtree<Key, T, Compare, Alloc, Node_alloc>::_is_red(Node * nd) { return (color(nd) == true); }

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
typename rbtree<Key, T, Compare, Alloc, Node_alloc>::pair_iterator_bool
rbtree<Key, T, Compare, Alloc, Node_alloc>::
insert(const_reference val) {
    link_type   p_tmp = _header;
    link_type   curr_tmp = _root;
    link_type   searched = search(val);
    bool        comp = true;

    while (curr_tmp != _nil) {
        p_tmp = curr_tmp;
        comp = _comp(val, value(curr_tmp));
        curr_tmp = comp ? left(curr_tmp) : right(curr_tmp);
    }
    if (searched != _nil)
        return (ft::make_pair(searched, false));
    return (ft::make_pair(_insert(curr_tmp, p_tmp, val), true));
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
typename rbtree<Key, T, Compare, Alloc, Node_alloc>::iterator
rbtree<Key, T, Compare, Alloc, Node_alloc>::insert(iterator position, const value_type& val) {
    iterator ret;
    iterator searched = search(val);

    if (searched != _nil)
        return (searched);
    if (position == begin()) {
        if (_comp(val, value(position.node())))
            return (_insert(position.node(), position.node(), val));
    }
    else if (position == end()) {
        if (_comp(value(rightmost()), val))
            return (_insert(_nil, rightmost(), val));
    }
    return (insert(val).first);
}

// HELPERS SECTION
template <class Key, class T, class Compare, class Alloc, class Node_alloc>
typename rbtree<Key, T, Compare, Alloc, Node_alloc>::iterator
rbtree<Key, T, Compare, Alloc, Node_alloc>::
_insert(link_type insert_to, link_type parent, const_reference val) {
    link_type new_node;

    ++_size;
    new_node = create_node(_nil, parent, create_value(val));
    /* if (parent == _header) {
        _root = new_node;
        leftmost() = new_node;
        rightmost() = new_node;
    }
    else {
        if (_comp(val, value(parent))) {
            left(parent) = new_node;
            if (parent == leftmost())
                leftmost() = new_node;
        } else {
            right(parent) = new_node;
            if (parent == rightmost())
                rightmost() = new_node;
        }
    } */
    if (parent == _header || insert_to != _nil || _comp(val, value(parent))) {
        left(parent) = new_node;
        if (parent == _header) {
            _root = new_node;
            rightmost() = new_node;
        } else if (parent == leftmost())
            leftmost() = new_node;
    } else {
        right(parent) = new_node;
        if (parent == rightmost())
            rightmost() = new_node;
    }
    return (_insert_fixup(new_node));
}

template <class Key, class T, class Compare, class Alloc, class Node_alloc>
typename rbtree<Key, T, Compare, Alloc, Node_alloc>::iterator
rbtree<Key, T, Compare, Alloc, Node_alloc>::
_insert_fixup(link_type & node) {
     link_type  tmp;
     link_type  node_tmp;

     node_tmp = node;
     while (node_tmp != _root && color(node_tmp->parent)) {
         if (parent(node_tmp) == left(parent(node_tmp->parent))) {
             tmp = right(parent(node_tmp->parent)); // getting uncle of <n_tmp>
             if (color(tmp)) {
                 _swap_colors(parent(node_tmp->parent));
                 node_tmp = parent(node_tmp->parent);
             } else {
                 if (node_tmp == right(node->parent)) {
                     node_tmp = parent(node_tmp);
                     _rotate_left(node_tmp);
                 }
                 color(node_tmp->parent) = false;
                 color(parent(node_tmp->parent)) = true;
                 _rotate_right(parent(node_tmp->parent));
             }
         } else {
             tmp = left(parent(node_tmp->parent));
             if (color(tmp)) {
                 _swap_colors(parent(node_tmp->parent));
                 node_tmp = parent(node_tmp->parent);
             } else {
                 if (node_tmp == left(node_tmp->parent)) {
                     node_tmp = parent(node_tmp);
                     _rotate_right(node_tmp);
                 }
                 color(node_tmp->parent) = false;
                 color(parent(node_tmp->parent)) = true;
                 _rotate_left(parent(node_tmp->parent));
             }
         }
     }
     color(_root) = false;
     return (iterator(node));
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void   rbtree<Key, T, Compare, Alloc, Node_alloc>::
_rotate_right(link_type node) {
    link_type   tmp;

    tmp = left(node);
    left(node) = right(tmp);
    if (right(tmp) != _nil)
        parent(tmp->right) = node;
    parent(tmp) = parent(node);
    if (node == _root)
        _root = tmp;
    else if (node == right(node->parent))
        right(node->parent) = tmp;
    else
        left(node->parent) = tmp;
    right(tmp) = node;
    parent(node) = tmp;
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void   rbtree<Key, T, Compare, Alloc, Node_alloc>::
_rotate_left(link_type node) {
    link_type   tmp;

    tmp = right(node);
    right(node) = left(tmp);
    if (left(tmp) != _nil)
        parent(tmp->left) = node;
    parent(tmp) = parent(node);
    if (node == _root)
        _root = tmp;
    else if (node == left(node->parent))
        left(node->parent) = tmp;
    else
        right(node->parent) = tmp;
    left(tmp) = node;
    parent(node) = tmp;
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void   rbtree<Key, T, Compare, Alloc, Node_alloc>::
_swap_colors(link_type nd) {
    nd->color = !nd->color;
    nd->left->color = !nd->left->color;
    nd->right->color = !nd->right->color;
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void             rbtree<Key, T, Compare, Alloc, Node_alloc>::_transplant(link_type u, link_type v) {
    if (parent(u) == _header) 
        _root = v;
    else if (u == left(u->parent))
        left(u->parent) = v;
    else
        right(u->parent) = v;
    parent(v) = parent(u);
}
template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void             rbtree<Key, T, Compare, Alloc, Node_alloc>::_delete_fixup(link_type node) {
    link_type  brother;

    while (node != _root && color(node) == false) {
        if (node == left(node->parent)) {
            brother = right(node->parent);
            if (color(brother) == true) {
                color(brother) = false;
                color(node->parent) = true;
                _rotate_left(parent(node));
                brother = right(node->parent);
            }
            if (color(brother->left) == false && color(brother->right) == false) {
                color(brother) = true;
                node = parent(node);
            } else {
                if (color(brother->right) == false) {
                    color(brother->left) = false;
                    color(brother) = true;
                    _rotate_right(brother);
                    brother = right(node->parent);
                }
                color(brother) = color(node->parent);
                color(node->parent) = false;
                color(brother->right) = false;
                _rotate_left(parent(node));
                break;
            }
        } else {
            brother = left(node->parent);
            if (_is_red(brother)) {
                color(brother) = false;
                color(node->parent) = true;
                _rotate_right(parent(node));
                brother = left(node->parent);
            }
            if (color(brother->left) == false && color(brother->right) == false) {
                color(brother) = true;
                node = parent(node);
            } else {
                if (color(brother->left) == false) {
                    color(brother->right) = false;
                    color(brother) = true;
                    _rotate_left(brother);
                    brother = left(node->parent);
                }
                color(brother) = color(node->parent);
                color(node->parent) = false;
                color(brother->left) = false;
                _rotate_right(parent(node));
                break;
           }
        }
    }
    color(node) = false;
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void               rbtree<Key, T, Compare, Alloc, Node_alloc>::_clear_node(link_type node) {
    _valloc.destroy(node->value);
    _valloc.deallocate(node->value, 1);
    _nalloc.destroy(node);
    _nalloc.deallocate(node, 1);
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void             rbtree<Key, T, Compare, Alloc, Node_alloc>::_delete_node(link_type node) {
    link_type  y = node;
    bool       y_color = color(y);
    link_type  x;

    if (left(node) == _nil) {
        x = right(node);
        _transplant(node, right(node));
    } else if (right(node) == _nil) {
        x = left(node);
        _transplant(node, left(node));
    } else {
        y = minimum(right(node));
        y_color = color(y);
        x = right(y);
        if (parent(y) == node)
            parent(x) = y;
        else {
            _transplant(y, right(y));
            right(y) = right(node);
            parent(y->right) = y;
        }
        _transplant(node, y);
        left(y) = left(node);
        parent(y->left) = y;
        color(y) = color(node);
    }
    if (y_color == false)
        _delete_fixup(x);
    if (_size != 1) {
        leftmost() = minimum(_root);
        rightmost() = maximum(_root);
    } else {
        leftmost() = _header;
        rightmost() = _header;
    }
   _clear_node(node);
   _size--;
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
typename rbtree<Key, T, Compare, Alloc, Node_alloc>::link_type
rbtree<Key, T, Compare, Alloc, Node_alloc>::search(const value_type & k) {
    link_type   x;

    x = _root;
    while (x != _nil && value(x) != k) {
        if (_comp(k, value(x)))
            x = left(x);
        else
            x = right(x);
    }
    return (x);
}


template <class Key, class T, class Compare, class Alloc, class Node_alloc>
void       rbtree<Key, T, Compare, Alloc, Node_alloc>::show() {
    std::cout << "===========================================" << "\n";
    _show(_root, 0);
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void       rbtree<Key, T, Compare, Alloc, Node_alloc>::_show(link_type nd, int place) {
	if (nd == _nil) {
        for(int i = 5; i < place + 5; i++)
            std::cout << " ";
        std::cout << YELLOW << "NIL: " << RESET << std::endl;
		return;
    }
	place += 5;
	_show(nd->right, place);

	for(int i = 5; i < place; i++)
		std::cout << " ";

    if (color(nd) == 1) {
        std::cout << RED << nd->value->first << " " << nd->value->second << RESET<< "\n";
    } else {
        std::cout << YELLOW << nd->value->first << " " << nd->value->second << RESET<< "\n";
    }

	_show(nd->left, place);
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void   rbtree<Key, T, Compare, Alloc, Node_alloc>::_clear(Node * nd) {
    if (nd == _nil)
        return;
    _clear(left(nd));
    _clear(right(nd));
    _valloc.destroy(_valloc.address(value(nd)));
    _valloc.deallocate(_valloc.address(value(nd)), 1);
    delete nd;
    leftmost() = _header;
    rightmost() = _header;
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
typename rbtree<Key, T, Compare, Alloc, Node_alloc>::link_type
rbtree<Key, T, Compare, Alloc, Node_alloc>::minimum(link_type x) {
    while (left(x) != _nil) x = left(x);
    return (x);
}
template <class Key,class T, class Compare, class Alloc, class Node_alloc>
typename rbtree<Key, T, Compare, Alloc, Node_alloc>::link_type
rbtree<Key, T, Compare, Alloc, Node_alloc>::maximum(link_type x) {
    while (right(x) != _nil) x = right(x);
    return (x);
}
template <class Key,class T, class Compare, class Alloc, class Node_alloc>
typename rbtree<Key, T, Compare, Alloc, Node_alloc>::pointer
rbtree<Key, T, Compare, Alloc, Node_alloc>::create_value(const_reference val) {
    pointer    value;

    value = _valloc.allocate(1);
    _valloc.construct(value, val);
    return (value);
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
typename rbtree<Key, T, Compare, Alloc, Node_alloc>::link_type
rbtree<Key, T, Compare, Alloc, Node_alloc>::create_node(link_type childs, link_type parent, pointer value) {
    link_type  created;

    created = _nalloc.allocate(1);
    _nalloc.construct(created, Node(value, childs, parent));
    color(created) = value != NULL;
    return (created);
}   // HELPERS SECTION END

}   // namespace ft

#endif /* ifndef __MAP_SRCS_INCLUDES_RBTREE_HPP__ */
