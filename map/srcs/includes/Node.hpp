#ifndef __MAP_SRCS_INCLUDES_NODE_HPP__
# define __MAP_SRCS_INCLUDES_NODE_HPP__

#include <iostream>

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

}   // namespace ft

#endif /* ifndef __MAP_SRCS_INCLUDES_NODE_HPP__ */
