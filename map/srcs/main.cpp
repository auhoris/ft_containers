#include "includes/rbtree.hpp"
#include <cstdlib>
#include <ctime>
#include <functional>
#include <type_traits>
#include <utility>
#include <map>
#include <iostream>

#define NODES 10

template<class Key, class T>
void    make_tree(ft::rbtree<Key, T> &tree) {
    int     number;

    for (int i = 0; i < NODES; i++) {
        number = rand() % NODES;
        // std::cout << "i = " << i << "\t" << "number = " << number << "\n";
        tree.insert(std::make_pair(number, static_cast<char>(65 + (rand() % 25))));
    }
}

int main(void)
{
    srand(time(0));
    ft::rbtree<int, std::pair<int, char> >    test;
    std::map<int, char>     test2;
    /* test.insert(std::make_pair(1, 'c'));
    test.insert(std::make_pair(0, 'a')); */
    make_tree(test);
    /* std::cout << test.begin()->first << "\n";
    std::cout << test.begin()->second << "\n"; */
    // std::map<int, char>     std_map;
    // test.show();
    return 0;
}
