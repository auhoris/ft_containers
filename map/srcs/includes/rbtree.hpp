#ifndef __MAP_SRCS_INCLUDES_RBTREE_HPP__
# define __MAP_SRCS_INCLUDES_RBTREE_HPP__

# include <iostream>
# include <cstddef>
# include <functional>
# include <iterator>
# include <memory>
# include <string>
# include <utility>
# include "bidirectional_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft {

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
     typedef Node<value_type>  Node;
     typedef Node*             link_type;

     // Accessors to Node fields =======================
     key_type const & key_of_value(const_reference val) { return (val.first); }
     reference        value(link_type nd) { return (*nd->value); }
     key_type const & key(link_type nd) { return (key_of_value(value(nd))); }
     bool&            color(link_type nd) { return (nd->color); }
     link_type&       left(link_type x) { return (x->left); }
     link_type&       right(link_type x) { return (x->right); }
     link_type&       parent(link_type x) { return (x->parent); }
     link_type&       leftmost() { return (left(_header)); }
     link_type&       leftmost() const { return (left(_header)); }
     link_type&       rightmost() { return (right(_header)); }
     link_type&       rightmost() const { return (right(_header)); }
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
     link_type  create_node(link_type childs = NULL, link_type parent = NULL, pointer value = NULL) {
         link_type  created;

         created = _nalloc.allocate(1);
         _nalloc.construct(created, Node(value, childs, parent));
         color(created) = value != NULL;
         return (created);
     }
     bool       _is_red(link_type nd);
     void       _clear(link_type nd);
     link_type  _insert(link_type nd);  // Takes <where> to insert and <what> to insert
     link_type  _insert_fixup(link_type & node) {
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
                     if (node_tmp == node_tmp->parent->right) {
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
                     if (node_tmp == node_tmp->parent->left) {
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
         return (node);
     }
     void       _rotate_right(link_type nd);
     void       _rotate_left(link_type nd);
     void       _swap_colors(link_type nd);
     Node       _deleteNode(link_type nd);
     void       _show(link_type nd, int place);

 private:   // Fields
     link_type                      _root;
     link_type                      _header;
     link_type                      _nil;    // для экономии памяти - будет являться конечным узлом
     static bool                    _inserted;
     std::less<Value>               _comp;
     std::allocator<value_type>     _valloc;
     std::allocator<Node>           _nalloc; // hz zachem
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
     ~rbtree();
     rbtree&    operator=(const rbtree & copy);

     // Random helpers
     bool     search(const_reference val);
     void           show();

     // Modifiers
     std::pair<iterator, bool>  insert(const_reference value) {
         pointer                    new_value;
         link_type                  new_node;
         std::pair<iterator, bool>  pair;

         /* if (search(value)) {
             return (std::make_pair(_root, false));
         } */
         new_value = create_value(value);
         new_node = create_node(_nil, _nil, new_value);
         pair = std::make_pair(_insert(new_node), _inserted);
         return (pair);
     }

     // Iterators
     iterator begin() { return (leftmost()); }
     const_iterator begin() const { return (leftmost()); }
     iterator end() { return (_header); }
     const_iterator end() const { return (_header); }
};

template <class Key, class T, class Compare, class Alloc, class Node_alloc>
bool rbtree<Key, T, Compare, Alloc, Node_alloc>::_inserted = false;

template <class Key, class T, class Compare, class Alloc, class Node_alloc>
rbtree<Key, T, Compare, Alloc, Node_alloc>::rbtree(const key_compare& comp,
         const allocator_type& valloc,
         const node_allocator_type & nalloc) : _comp(comp), _valloc(valloc), _nalloc(nalloc), _size(0) {
     _nil = create_node();
     _root = _nil;
     _header = create_node(_root);
     color(_header) = true;
     leftmost() = _header;
     rightmost() = _header;
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
    _nalloc.destroy(_header);
    _nalloc.deallocate(_header, 1);
}

template <class Key, class T, class Compare, class Alloc, class Node_alloc>
rbtree<Key, T, Compare, Alloc, Node_alloc>&     rbtree<Key, T, Compare, Alloc, Node_alloc>::operator=(const rbtree & copy) {
    if (this == &copy)
        return (*this);
    return (*this);
}

//  Helper Functions =============================
template <class Key,class T, class Compare, class Alloc, class Node_alloc>
bool   rbtree<Key, T, Compare, Alloc, Node_alloc>::_is_red(Node * nd) {
    return (color(nd) == true);
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
Node<T>*   rbtree<Key, T, Compare, Alloc, Node_alloc>::_insert(Node * nd) {
    link_type   tmp_parent;
    link_type   tmp_root;

    tmp_parent = _nil;
    tmp_root = _root;
    while (tmp_root != _nil) {
        tmp_parent = tmp_root;
        if (_comp(value(nd), value(tmp_root)))
            tmp_root = left(tmp_root);
        else
            tmp_root = right(tmp_root);
    }
    if (tmp_parent == _nil) {
        _root = nd;
        leftmost() = nd;
    } else if (_comp(value(nd), value(tmp_parent))) {
        left(tmp_parent) = nd;
        leftmost() = nd;
    } else {
        right(tmp_parent) = nd;
        rightmost() = nd;
    }
    parent(nd) = tmp_parent;
    return (_insert_fixup(nd));
}

/* template <class T, class Compare, class Alloc, class Node_alloc>
node<T>   rbtree<T, Compare, Alloc, Node_alloc>::_fixInsertion(node & root, node & inserted) {

} */

        /* std::cout << "nil: " << _nil << "\n";
        std::cout << "node: " << tmp << "\t";
        std::cout << "parent: " << parent(tmp) << "\t";
        std::cout << "left: " << left(tmp) << "\t";
        std::cout << "right: " << right(tmp) << "\t"; */
template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void   rbtree<Key, T, Compare, Alloc, Node_alloc>::_rotate_right(link_type node) {
    link_type   tmp;

    tmp = node->left;
    node->left = tmp->right;
    if (tmp->right != _nil)
        parent(tmp->right) = node;
    parent(tmp) = parent(node);
    if (node->parent == _nil)
        _root = tmp;
    else if (node == node->parent->right)
        node->parent->right = tmp;
    else
        node->parent->left = tmp;
    right(tmp) = node;
    parent(node) = tmp;
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void   rbtree<Key, T, Compare, Alloc, Node_alloc>::_rotate_left(link_type node) {
    link_type   tmp;

    tmp = right(node);
    right(node) = left(tmp);
    if (tmp->left != _nil) {
        std::cout << "LEFT" << "\n";
        std::cout << "node key: " << key(node) << "\t";
        std::cout << "tmp: " << tmp << "\t";
        std::cout << "_nil: " << _nil << "\t";
        std::cout << "address: " << tmp->left << "\n";
        parent(tmp->left) = node;
    }
    parent(tmp) = parent(node);
    if (node == _root)
        _root = tmp;
    else if (node == node->parent->left)
        left(node->parent) = tmp;
    else
        right(node->parent) = tmp;
    left(tmp) = node;
    parent(node) = tmp;
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void   rbtree<Key, T, Compare, Alloc, Node_alloc>::_swap_colors(link_type nd) {
    nd->color = !nd->color;
    nd->left->color = !nd->left->color;
    nd->right->color = !nd->right->color;
}
/* template <class T, class Compare, class Alloc, class Node_alloc>
node<T>   rbtree<T, Compare, Alloc, Node_alloc>::_deleteNode(node * nd) {

} */

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
bool     rbtree<Key, T, Compare, Alloc, Node_alloc>::search(const_reference val) {
    Node*   x;

    x = _root;
    while (x != _nil) {
        if (value(x) == val) {
            return (true);
        } else if (_comp(value(x), val)) {
            x = left(x);
        } else {
            x = right(x);
        }
    }
    return (false);
}

template <class Key, class T, class Compare, class Alloc, class Node_alloc>
void       rbtree<Key, T, Compare, Alloc, Node_alloc>::show() {
    _show(_root, 0);
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void       rbtree<Key, T, Compare, Alloc, Node_alloc>::_show(Node * nd, int place) {
	if (nd == _nil) {
        for(int i = 5; i < place + 5; i++)
            std::cout << " ";
        std::cout << "NIL: " << std::endl;
		return;
    }
	place += 5;
	_show(nd->right, place);

	for(int i = 5; i < place; i++)
		std::cout << " ";

	std::cout << key_of_value(value(nd)) /*<< "[ " << nd << " ]"*/ << (nd->color == 1 ? " R" : " B") <<'\n';

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
}
}   // namespace ft

#endif /* ifndef __MAP_SRCS_INCLUDES_RBTREE_HPP__ */
