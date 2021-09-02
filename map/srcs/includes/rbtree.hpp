#ifndef __MAP_SRCS_INCLUDES_RBTREE_HPP__
# define __MAP_SRCS_INCLUDES_RBTREE_HPP__

# include <iostream>
# include <cstddef>
# include <functional>
#include <iterator>
# include <memory>
#include <string>
# include <utility>
# include "bidirectional_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft {

template<class Value> // value is pair
struct Node {
    // ====================================================
    typedef Value      value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    // ====================================================
    pointer                 value;
    Node*                   left;
    Node*                   right;
    bool                    color;  // true=red ; false=black
    // node*   parent;  maybe later

    Node(pointer value, Node* node = NULL) : value(value), left(node), right(node), color(true) {}
};

template <class Key,
         class Value,
         class Compare = std::less<Value>,
         class Alloc = std::allocator<Value>,
         class Node_alloc = std::allocator<Node<Value> > >
class rbtree {

 public:    // Main Typedefs
     typedef Key                                key_type;
     typedef Value                              value_type;
     typedef Compare                            key_compare;
     typedef Alloc                              allocator_type;
     typedef Node_alloc                         node_allocator_type;
     typedef value_type&                        reference;
     typedef const value_type&                  const_reference;
     typedef value_type*                        pointer;
     typedef const value_type*                  const_pointer;
     typedef BidirectionalIterator<Value>       iterator;
     typedef BidirectionalIterator<const Value> const_iterator;
     typedef ReverseIterator<Value>             reverse_iterator;
     typedef ReverseIterator<const Value>       const_reverse_iterator;
     typedef std::ptrdiff_t                     difference_type;
     typedef std::size_t                        size_type;

 private:   // Functions section
     // Node typedefs
     typedef Node<value_type>  node;
     typedef node*             link_type;

     // Accessors to Node fields =======================
     key_type const & key_of_value(const_reference val) { return (val.first); }
     reference        value(link_type nd) { return (*nd->value); }
     key_type const & key(link_type nd) { return (key_of_value(value(nd))); }
     bool&            color(link_type nd) { return (nd->color); }
     link_type&       left(link_type x) { return (x->left); }
     link_type&       right(link_type x) { return (x->right); }
     link_type        minimum(link_type x) {
         while (left(x) != _nil) x = left(x);
         return (x);
     }
     link_type        maximum(link_type x) {
         while (right(x) != _nil) x = right(x);
         return (x);
     }


     // Utils ==========================================
     pointer        create_value(const_reference val) {
         pointer    value;

         value = _valloc.allocate(1);
         _valloc.construct(value, val);
         return (value);
     }
     link_type  create_node(link_type point_to = NULL, pointer value = NULL) {
         link_type  created;

         created = _nalloc.allocate(1);
         _nalloc.construct(created, node(value, point_to));
         color(created) = value == NULL ? false : true;
         return (created);
     }
     bool   _is_red(node * nd);
     void   _clear(node * nd);
     node*  _insert(node * nd, const_reference value);  // Takes <where> to insert and <what> to insert
     // node   _fixInsertion(node & root, node & inserted);
     void   _rotate_right(node *& nd);
     void   _rotate_left(node *& nd);
     void   _swap_colors(node * nd);
     node   _deleteNode(node * nd);
     void   _show(node * nd, int place);

 private:   // Fields
     link_type                      _root;
     link_type                      _nil;    // для экономии памяти - будет являться конечным узлом
     std::pair<iterator, bool>      _inserted;
     std::less<Value>               _comp;
     std::allocator<value_type>     _valloc;
     std::allocator<node>           _nalloc; // hz zachem
     size_type                      _size;

 public:    // Member funcs
     // Default things
     explicit rbtree(const key_compare& comp = key_compare(),
             const allocator_type& allocator = allocator_type(),
             const node_allocator_type & nallocator = node_allocator_type());
     template <class InputIterator>
     rbtree(InputIterator first, InputIterator last, 
             const key_compare & comp = key_compare(),
             const allocator_type & allocator = allocator_type(),
             const node_allocator_type & nallocator = node_allocator_type());
     rbtree(const rbtree & copy);
     ~rbtree(); // Implement later
     rbtree&    operator=(const rbtree & copy);

     // Random helpers
     value_type     search(const_reference value);
     void       show();

     // Modifiers
     void       insert(const_reference value);

     // Iterators
     iterator begin() { return (std::addressof(value(minimum(_root)))); }
     const_iterator begin() const { return (std::addressof(value(minimum(_root))));}
     iterator end() { return (std::addressof(value(_nil))); }
     const_iterator end() const { return (std::addressof(value(_nil))); }
};

template <class Key, class T, class Compare, class Alloc, class Node_alloc>
rbtree<Key, T, Compare, Alloc, Node_alloc>::rbtree(const key_compare& comp,
         const allocator_type& valloc,
         const node_allocator_type & nalloc) : _comp(comp), _valloc(valloc), _nalloc(nalloc), _size(0) {
     _nil = create_node();
     _root = _nil;
}

/* template <class Key, class T, class Compare, class Alloc, class Node_alloc>
template <class InputIterator>
rbtree<Key, T, Compare, Alloc, Node_alloc>::rbtree(InputIterator first, InputIterator last,
        const key_compare & comp,
        const allocator_type & allocator,
        const node_allocator_type & nallocator) :
    _root(NULL),
    _comp(comp),
    _value_alloc(allocator),
    _node_alloc(nallocator),
    _size(0) {
    (void)first;
    (void)last;
    _nil = _node_alloc.allocate(1);
    _node_alloc.construct(_nil, node(NULL));
    _nil->color = false;
    //Implenet later
}

template <class Key, class T, class Compare, class Alloc, class Node_alloc>
rbtree<Key, T, Compare, Alloc, Node_alloc>::rbtree(const rbtree & copy) :
    _root(NULL),
    _comp(copy._comp),
    _value_alloc(copy._value_alloc),
    _node_alloc(copy._node_alloc),
    _size(0) {
    _nil = _node_alloc.allocate(1);
    _node_alloc.construct(_nil, node(NULL));
    _nil->color = false;
    //Implenet later
} */
template <class Key, class T, class Compare, class Alloc, class Node_alloc>
rbtree<Key, T, Compare, Alloc, Node_alloc>::~rbtree() {
    _clear(_root);
    _nalloc.destroy(_nil);
    _nalloc.deallocate(_nil, 1);
}

template <class Key, class T, class Compare, class Alloc, class Node_alloc>
rbtree<Key, T, Compare, Alloc, Node_alloc>&     rbtree<Key, T, Compare, Alloc, Node_alloc>::operator=(const rbtree & copy) {
    if (this == &copy)
        return (*this);
    return (*this);
}

//  Helper Functions =============================
template <class Key,class T, class Compare, class Alloc, class Node_alloc>
bool   rbtree<Key, T, Compare, Alloc, Node_alloc>::_is_red(node * nd) {
    return (color(nd) == true);
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
Node<T>*   rbtree<Key, T, Compare, Alloc, Node_alloc>::_insert(node * nd, const_reference val) {
    if (nd == _nil) {
        link_type   new_nd;

        new_nd = create_node(_nil, create_value(val));
        _inserted = std::make_pair(iterator(std::addressof(value(new_nd))), true);
        return (new_nd);
    }
    if (_is_red(left(nd)) && _is_red(right(nd)))
        _swap_colors(nd);
    if (value(nd) == val) {
        _inserted = std::make_pair(iterator(std::addressof(value(nd))), false);
        return (nd);
    }
    else if (_comp(val, value(nd)))
        left(nd) = _insert(left(nd), val);
    else
        right(nd) = _insert(right(nd), val);
    if (_is_red(right(nd)) && !_is_red(left(nd)))
        _rotate_left(nd);
    if (_is_red(left(nd)) && _is_red(left(left(nd))))
        _rotate_right(nd);
    return (nd);
}

/* template <class T, class Compare, class Alloc, class Node_alloc>
node<T>   rbtree<T, Compare, Alloc, Node_alloc>::_fixInsertion(node & root, node & inserted) {

} */

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void   rbtree<Key, T, Compare, Alloc, Node_alloc>::_rotate_right(node *& nd) {
    node*   tmp;

    tmp = nd->left;
    nd->left = tmp->right;
    tmp->right = nd;
    tmp->color = nd->color;
    nd->color = true;
    nd = tmp;
}
template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void   rbtree<Key, T, Compare, Alloc, Node_alloc>::_rotate_left(node *& nd) {
    node*   tmp;

    tmp = nd->right;
    nd->right = tmp->left;
    tmp->left = nd;
    tmp->color = nd->color;
    nd->color = true;
    nd = tmp;
}
template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void   rbtree<Key, T, Compare, Alloc, Node_alloc>::_swap_colors(node * nd) {
    nd->color = !nd->color;
    nd->left->color = !nd->left->color;
    nd->right->color = !nd->right->color;
}
/* template <class T, class Compare, class Alloc, class Node_alloc>
node<T>   rbtree<T, Compare, Alloc, Node_alloc>::_deleteNode(node * nd) {

} */

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void       rbtree<Key, T, Compare, Alloc, Node_alloc>::insert(const_reference value) {
    _root = _insert(_root, value);
    _root->color = false;
}
template <class Key,class T, class Compare, class Alloc, class Node_alloc>
T     rbtree<Key, T, Compare, Alloc, Node_alloc>::search(const_reference value) {
    node*   x;

    x = _root;
    while (x != NULL) {
        if (*(x->value) == value) {
            return (*(x->value));
        } else if (*(x->value) < value) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return (std::make_pair(123, 'j'));
}
template <class Key, class T, class Compare, class Alloc, class Node_alloc>
void       rbtree<Key, T, Compare, Alloc, Node_alloc>::show() {
    _show(_root, 0);
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void       rbtree<Key, T, Compare, Alloc, Node_alloc>::_show(node * nd, int place) {
	if (nd == _nil) {
        for(int i = 5; i < place + 5; i++)
            std::cout << " ";
        std::cout << "NIL: " << _nil << std::endl;
		return;
    }
	place += 5;
	_show(nd->left, place);

	for(int i = 5; i < place; i++)
		std::cout << " ";

	std::cout << key_of_value(value(nd)) << (nd->color == 1 ? " R" : " B") <<'\n';

	_show(nd->right, place);
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void   rbtree<Key, T, Compare, Alloc, Node_alloc>::_clear(node * nd) {
    if (nd == _nil)
        return;
    _clear(left(nd));
    _clear(right(nd));
    _valloc.destroy(_valloc.address(value(nd)));
    _valloc.deallocate(_valloc.address(value(nd)), 1);
    delete nd;
}
}   // namespace ft

#endif /* ifndef __MAP_SRCS_INCLUDES_RBTREE_HPP__ */
