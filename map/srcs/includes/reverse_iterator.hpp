#ifndef __VECTOR_SRCS_INCLUDES_REVERSE_ITERATOR_HPP__
# define __VECTOR_SRCS_INCLUDES_REVERSE_ITERATOR_HPP__

# include "Node.hpp"
// #include "bidirectional_iterator.hpp"
#include <iterator>
// # include "bidirectional_iterator.hpp"
// # include <iterator>

namespace ft {

template<typename Value>
class ReverseIterator : public std::iterator<std::bidirectional_iterator_tag, Value> {
 public:
     typedef std::bidirectional_iterator_tag    iterator_category;
     typedef Value                              value_type;
     typedef std::ptrdiff_t                     difference_type;
     typedef Value*                             pointer;
     typedef Value&                             reference;

 protected:
     typedef Node<Value>* link_type;
     link_type  _node;

 public:
     // Default things
     ReverseIterator() : _node(NULL) { };
     ReverseIterator(link_type type) : _node(type) { };
     virtual ~ReverseIterator() { }
     ReverseIterator(const ReverseIterator &copy) : _node(copy._node) { }

     // operators
     ReverseIterator&    operator=(ReverseIterator const & copy) {
         if (this == &copy)
             return (*this);
         _node = copy._node;
         return (*this);
     }

     // logical
     bool   operator==(ReverseIterator const & other) { return (_node == other._node); }
     bool   operator!=(ReverseIterator const & other) { return (_node != other._node); }

     // arithmetic
     ReverseIterator&   operator++() {
         if (_node->left->left != NULL) {
             _node = _node->left;
             while (_node->right->right != NULL)
                 _node = _node->right;
         } else {
             link_type p_node = _node->parent;
             while (p_node->left == _node) {
                 _node = p_node;
                 p_node = _node->parent;
             }
             _node = p_node;
         }
         return (*this);
     }
     ReverseIterator   operator++(int) {
         ReverseIterator tmp(*this);

         operator++();
         return (tmp);
     }
     ReverseIterator&   operator--() {
         if (_node->color == true && _node->parent == NULL) { // only _header has NULL parent
             _node = _node->left;
         } else if (_node->right->right != NULL) {
             _node = _node->right;
             while (_node->left->left != NULL)
                 _node = _node->left;
         } else {
             link_type p_node = _node->parent;
             while (_node == p_node->right) {
                 _node = p_node;
                 p_node = _node->parent;
             }
             _node = p_node;
         }
         return (*this);
     }
     ReverseIterator   operator--(int) {
         ReverseIterator tmp(*this);

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
#endif /* ifndef __VECTOR_SRCS_INCLUDES_REVERSE_ITERATOR_HPP__ */
