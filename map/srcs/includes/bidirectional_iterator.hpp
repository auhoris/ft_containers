#ifndef __VECTOR_SRCS_RANDOM_ACCESS_ITERATOR_HPP__
# define __VECTOR_SRCS_RANDOM_ACCESS_ITERATOR_HPP__

# include <bitset>
# include <cstddef>
# include <iterator>
# include "Node.hpp"

namespace ft {
template<typename Value>
class BidirectionalIterator : public std::iterator<std::bidirectional_iterator_tag, Value> {
 public:
     typedef std::bidirectional_iterator_tag    iterator_category;
     typedef Value                              value_type;
     typedef std::ptrdiff_t                     difference_type;
     typedef Value*                             pointer;
     typedef Value&                             reference;

 public:
     typedef Node<Value>* link_type;
     link_type  _node;

 public:
     // Default things
     BidirectionalIterator() : _node(NULL) { };
     BidirectionalIterator(link_type type) : _node(type) { };
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
         _node++;
         return (*this);
     }
     BidirectionalIterator   operator++(int) {
         BidirectionalIterator tmp(*this);

         operator++();
         return (tmp);
     }
     BidirectionalIterator&   operator--() {
         _node--;
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

}   // namespace ft

#endif /* ifndef __VECTOR_SRCS_RANDOM_ACCESS_ITERATOR_HPP__ */
