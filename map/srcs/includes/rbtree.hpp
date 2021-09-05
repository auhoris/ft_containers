#ifndef __MAP_SRCS_INCLUDES_RBTREE_HPP__
# define __MAP_SRCS_INCLUDES_RBTREE_HPP__

# include <iostream>
# include <cstddef>
# include <functional>
# include <iterator>
# include <memory>
# include <string>
# include <utility>
# include "Node.hpp"
// # include "bidirectional_iterator.hpp"
// # include "reverse_iterator.hpp"

namespace ft {

template<typename T>
class BidirectionalIterator;

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
     typedef std::ptrdiff_t                     difference_type;
     typedef std::size_t                        size_type;

 private:   // Fields
     // Node typedefs
     typedef Node<value_type>  Node;
     typedef Node*             link_type;

     link_type                      _root;
     link_type                      _header;
     link_type                      _nil;    // для экономии памяти - будет являться конечным узлом
     std::less<Value>               _comp;
     std::allocator<value_type>     _valloc;
     std::allocator<Node>           _nalloc; // hz zachem
     size_type                      _size;

 public: // Iterators classes
     template<typename T>
     class BidirectionalIterator : public std::iterator<std::bidirectional_iterator_tag, Value> {
         friend class rbtree<Key, Value>;
      protected:
          link_type  _node;
 
      public:
          // Default things
          BidirectionalIterator() : _node(NULL) { }
          BidirectionalIterator(link_type type) : _node(type) { }
          virtual ~BidirectionalIterator() { }
          BidirectionalIterator(const BidirectionalIterator &copy) : _node(copy._node) { }
 
          // operators
          BidirectionalIterator&    operator=(BidirectionalIterator const & copy) {
              if (this == &copy)
                  return (*this);
              _node = copy._node;
              return (*this);
          }
          // logical
          bool   operator==(BidirectionalIterator const & other) { return (_node == other._node); }
          bool   operator!=(BidirectionalIterator const & other) { return (_node != other._node); }
          // arithmetic
          BidirectionalIterator&   operator++() {
              if (_node->right->right != NULL) {
                  _node = _node->right;
                  while (_node->left->left != NULL)
                      _node = _node->left;
              } else {
                  link_type p_node = _node->parent;
                  while (p_node->right == _node) {
                      _node = p_node;
                      p_node = _node->parent;
                  }
                  _node = p_node;
              }
              return (*this);
          }
          BidirectionalIterator   operator++(int) {
              BidirectionalIterator tmp(*this);
 
              operator++();
              return (tmp);
          }
          BidirectionalIterator&   operator--() {
              if (_node->left->left != NULL) {
                  _node = _node->right;
                  while (_node->right->right != NULL)
                      _node = _node->right;
              } else {
                  link_type p_node = _node->parent;
                  while (_node == p_node->left) {
                      _node = p_node;
                      p_node = _node->parent;
                  }
                  _node = p_node;
              }
              return (*this);
          }
          BidirectionalIterator   operator--(int) {
              BidirectionalIterator tmp(*this);
 
              operator--();
              return (tmp);
          }
          // other
          Value&         operator*() { return (*_node->value); }
          const Value&   operator*() const { return (*_node->value); }
          Value*         operator->() { return (_node->value); }
     };

     typedef BidirectionalIterator<Value>       iterator;
     typedef BidirectionalIterator<const Value> const_iterator;
     /* typedef ReverseIterator<Value>             reverse_iterator;
     typedef ReverseIterator<const Value>       const_reverse_iterator; */

 private:   // Functions section
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
     link_type        minimum(link_type x);
     link_type        maximum(link_type x);
     // Utils ==========================================
     pointer        create_value(const_reference val);
     link_type  create_node(link_type childs = NULL, link_type parent = NULL, pointer value = NULL);
     bool       _is_red(link_type nd);
     void       _clear(link_type nd);
     iterator   _insert(link_type insert_to, link_type node, const_reference val);  // Takes <where> to insert and <what> to insert
     iterator   _insert_fixup(link_type & node);
     void       _rotate_right(link_type nd);
     void       _rotate_left(link_type nd);
     void       _swap_colors(link_type nd);
     Node       _deleteNode(link_type nd);
     void       _show(link_type nd, int place);

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
     link_type      search(const_reference val);
     void           show();

     // Modifiers
     typedef std::pair<iterator, bool> pair_iterator_bool;
     pair_iterator_bool     insert(const_reference val);
     iterator               insert(iterator position, const value_type& val);

     // Iterators
     iterator begin() { return (leftmost()); }
     const_iterator begin() const { return (leftmost()); }
     iterator end() { return (_header); }
     const_iterator end() const { return (_header); }
     size_type  size() { return (_size); }
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
rbtree<Key, T, Compare, Alloc, Node_alloc>&
rbtree<Key, T, Compare, Alloc, Node_alloc>::
operator=(const rbtree & copy) {
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
        return (std::make_pair(searched, false));
    return (std::make_pair(_insert(curr_tmp, p_tmp, val), true));
}

//^^^^^^^^^^^^
/* pointer    new_value;
link_type  new_node;
iterator   searched;

searched = search(val);
if (searched != _nil)
    return (std::make_pair(iterator(searched), false));
_size++;
new_value = create_value(val);
new_node = create_node(_nil, _nil, new_value);
return (std::make_pair(_insert(_root, new_node), true)); */

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
typename rbtree<Key, T, Compare, Alloc, Node_alloc>::iterator
rbtree<Key, T, Compare, Alloc, Node_alloc>::insert(iterator position, const value_type& val) {
    iterator ret;
    iterator searched = search(val);

    if (searched != _nil) {
        std::cout << "HERE" << "\n";
        return (searched);
    }
    (void)position;
    // ret = _insert(position._node, position._node, val);
    return (insert(val).first);
}

template <class Key, class T, class Compare, class Alloc, class Node_alloc>
typename rbtree<Key, T, Compare, Alloc, Node_alloc>::iterator
rbtree<Key, T, Compare, Alloc, Node_alloc>::
_insert(link_type insert_to, link_type parent, const_reference val) {
    link_type new_node;

    (void)insert_to;
    ++_size;
    new_node = create_node(_nil, parent, create_value(val));
    if (parent == _header) {
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
    }
    /* if (parent == _header || insert_to != _nil || _comp(val, value(parent))) {
        left(parent) = new_node;
        if (parent == _header) {
            _root = new_node;
        } else if (parent == leftmost())
            leftmost() = new_node;
    } else {
        right(parent) = new_node;
        if (parent == rightmost())
            rightmost() = new_node;
    } */
    return (_insert_fixup(new_node));
}
//^^^^^^^^^^^^^^^^^^^^^^
/* link_type   tmp_parent;
link_type   tmp_root;

tmp_root = insert_to;
tmp_parent = tmp_root == _root ? _nil : parent(tmp_root);
while (tmp_root != _nil) {
    tmp_parent = tmp_root;
    if (_comp(value(node), value(tmp_root)))
        tmp_root = left(tmp_root);
    else
        tmp_root = right(tmp_root);
}
if (tmp_parent == _nil) {
    _root = node;
    leftmost() = node;
} else if (_comp(value(node), value(tmp_parent))) {
    left(tmp_parent) = node;
    leftmost() = node;
} else {
    right(tmp_parent) = node;
    rightmost() = node;
}
parent(node) = tmp_parent;
return (iterator(_insert_fixup(node))); */


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
typename rbtree<Key, T, Compare, Alloc, Node_alloc>::link_type
rbtree<Key, T, Compare, Alloc, Node_alloc>::search(const_reference val) {
    link_type   x;

    x = _root;
    while (x != _nil && key(x) != key_of_value(val)) {
        if (_comp(val, value(x)))
            x = left(x);
        else
            x = right(x);
    }
    return (x);
}

template <class Key, class T, class Compare, class Alloc, class Node_alloc>
void       rbtree<Key, T, Compare, Alloc, Node_alloc>::show() {
    _show(_root, 0);
}

template <class Key,class T, class Compare, class Alloc, class Node_alloc>
void       rbtree<Key, T, Compare, Alloc, Node_alloc>::_show(link_type nd, int place) {
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

	std::cout << nd->value->first << " "<< nd->value->second << (nd->color == 1 ? " R" : " B") <<'\n';

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
}

}   // namespace ft

#endif /* ifndef __MAP_SRCS_INCLUDES_RBTREE_HPP__ */