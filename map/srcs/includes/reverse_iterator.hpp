#ifndef __VECTOR_SRCS_INCLUDES_REVERSE_ITERATOR_HPP__
# define __VECTOR_SRCS_INCLUDES_REVERSE_ITERATOR_HPP__

# include "bidirectional_iterator.hpp"
# include <iterator>

namespace ft {
template<typename T>
class ReverseIterator : public std::reverse_iterator<BidirectionalIterator<T> > {
 public:
     typedef std::reverse_iterator<BidirectionalIterator<T> > iterator_category;
     typedef T value_type;
     typedef std::ptrdiff_t difference_type;
     typedef T* pointer;
     typedef T& reference;
     typedef Node<T>* link_type;

 private:
     link_type  _node;

 public:
     // Default
     ReverseIterator() : _node(NULL) { }
     ReverseIterator(pointer type) : _node(type) {}
     virtual ~ReverseIterator() { }
     ReverseIterator(const ReverseIterator &other) :  _node(other._node) {}

     // operators
     ReverseIterator&   operator=(ReverseIterator const & other) {
         if (this == &other)
             return (*this);
         this->_node = other._node;
         return (*this);
     }

     // arithmetic
     ReverseIterator&   operator--() {
         if (this->_node->right->right != NULL) {
             this->node = this->_node->right;
             while (this->_node->left->left != NULL)
                 this->_node = this->_node->left;
         } else {
             link_type p_node = this->_node->parent;
             while (p_node->right == this->_node) {
                 this->_node = p_node;
                 p_node = this->_node->parent;
             }
             this->_node = p_node;
         }
         return (*this);
     }
     ReverseIterator   operator--(int) {
         ReverseIterator tmp(*this);

         operator--();
         return (tmp);
     }
     ReverseIterator&   operator++() {
         if (this->_node->left->left != NULL) {
             this->_node = this->_node->right;
             while (this->_node->right->right != NULL)
                 this->_node = this->_node->right;
         } else {
             link_type p_node = this->_node->parent;
             while (this->_node == p_node->left) {
                 this->_node = p_node;
                 p_node = this->_node->parent;
             }
             this->_node = p_node;
         }
         return (*this);
     }
     ReverseIterator   operator++(int) {
         ReverseIterator tmp(*this);

         operator--();
         return (tmp);
     }
};

} // namespace ft
#endif /* ifndef __VECTOR_SRCS_INCLUDES_REVERSE_ITERATOR_HPP__ */
