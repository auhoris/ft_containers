#ifndef __STACK_SRCS_INCLUDES_STACK_HPP__
# define __STACK_SRCS_INCLUDES_STACK_HPP__

# include "../../../vector/srcs/includes/vector.hpp"


namespace ft {
template <class T, class Container = vector<T> >
class stack {
 public:
     typedef T          value_type;
     typedef Container  container_type;
     typedef size_t     size_type;
 protected:
     vector<T>  c;
 public:
     // Default things
     explicit stack (const container_type& ctnr = container_type()) : c(ctnr) { }

     // members
     bool empty() const { return (c.empty()); }
     size_type size() const { return (c.size()); }
     value_type& top() { return (c.back()); }
     const value_type& top() const { return (c.back()); };
     void push(const value_type& val) { c.push_back(val); }
     void pop() { c.pop_back() ;}

};

template <class T, class Container>
bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return (lhs.c == rhs.c);
}

template <class T, class Container>
bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return (lhs.c != rhs.c);
}

template <class T, class Container>
bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return (lhs.c < rhs.c);
}

template <class T, class Container>
bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return (lhs.c <= rhs.c);
}

template <class T, class Container>
bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return (lhs.c > rhs.c);
}

template <class T, class Container>
bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
    return (lhs.c >= rhs.c);
}

}   // namespace ft

#endif /* ifndef __STACK_SRCS_INCLUDES_STACK_HPP__ */
