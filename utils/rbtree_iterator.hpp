#ifndef __UTILS_RBTREE_ITERATOR_HPP__
# define __UTILS_RBTREE_ITERATOR_HPP__

# include "Node.hpp"
# include "iterator.hpp"
# include "type_traits.hpp"

namespace ft {

template<typename Value, bool IsConst>
class RBTreeIterator : public iterator<bidirectional_iterator_tag, Value> {
 public:
     typedef typename conditional<IsConst, const Value, Value>::type    value_type;
     typedef typename conditional<IsConst, const Value*, Value*>::type  pointer;
     typedef typename conditional<IsConst, const Value&, Value&>::type  reference;
     typedef random_access_iterator_tag                                 iterator_category;
     typedef ptrdiff_t                                                  difference_type;

 protected:
     typedef Node<Value>* link_type;
     link_type  _node;

 public:
     // Default things
     RBTreeIterator() : _node() { };
     RBTreeIterator(link_type type) : _node(type) { };
     virtual ~RBTreeIterator() { }
     RBTreeIterator(const RBTreeIterator<Value, IsConst> &copy) : _node(copy._node) { }

     // operators
     RBTreeIterator<Value, IsConst>&    operator=(RBTreeIterator<Value, IsConst> const & copy) {
         if (this == &copy)
             return (*this);
         _node = copy._node;
         return (*this);
     }
     operator RBTreeIterator<Value, true>() const {
         return (RBTreeIterator<Value, true>(_node));
     }

     // logical
     bool   operator==(RBTreeIterator<Value, IsConst> const & other) { return (_node == other._node); }
     bool   operator!=(RBTreeIterator<Value, IsConst> const & other) { return (_node != other._node); }

     // arithmetic
     RBTreeIterator<Value, IsConst>&   operator++() {
         if (_node->right->right != NULL) {
             _node = _node->right;
             while (_node->left->left != NULL)
                 _node = _node->left;
         } else {
             link_type p_node = _node->parent;
             while (p_node->parent &&  p_node->right == _node) {
                 _node = p_node;
                 p_node = _node->parent;
             }
             if (_node->right != p_node)
                 _node = p_node;
         }
         return (*this);
     }
     RBTreeIterator<Value, IsConst>   operator++(int) {
         RBTreeIterator<Value, IsConst> tmp(*this);

         operator++();
         return (tmp);
     }
     RBTreeIterator<Value, IsConst>&   operator--() {
         if (_node->color == true && _node->parent == NULL) { // only _header has NULL parent
             _node = _node->right;
         } else if (_node->left->left != NULL) {
             _node = _node->left;
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
     RBTreeIterator<Value, IsConst>   operator--(int) {
         RBTreeIterator<Value, IsConst> tmp(*this);

         operator--();
         return (tmp);
     }

     link_type&     node() { return (_node); }
     // other
     Value&         operator*() { return (*_node->value); }
     const Value&   operator*() const { return (*_node->value); }
     Value*         operator->() { return (_node->value); }
};

}   // namespace ft
#endif /* ifndef __UTILS_RBTREE_ITERATOR_HPP__ */
