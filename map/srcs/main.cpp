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
    int     r_num;

    for (int i = 0; i < NODES; i++) {
        r_num = rand() % NODES;
        // std::cout << "i = " << i << "\t" << "number = " << number << "\n";
        tree.insert(std::make_pair(r_num, static_cast<char>(65 + (rand() % 25))));
    }
}

std::pair<int, char> rand_pair() {
    std::pair<int, char>    par;

    par = std::make_pair(rand() % 100, static_cast<char>(65 + (rand() % 25)));
    std::cout << par.first << "\t";
    std::cout << par.second << "\n";
    return (par);
}

int main(void)
{
    srand(time(0));
    ft::rbtree<int, std::pair<int, char> >    test;
    /* std::map<int, char>     test2;
    test2.insert(std::make_pair(1, static_cast<char>(65 + (rand() % 25))));
    test2.insert(std::make_pair(2, static_cast<char>(65 + (rand() % 25))));
    test2.insert(std::make_pair(3, static_cast<char>(65 + (rand() % 25))));
    test2.insert(std::make_pair(4, static_cast<char>(65 + (rand() % 25))));
    test2.insert(std::make_pair(5, static_cast<char>(65 + (rand() % 25))));
    test2.insert(std::make_pair(6, static_cast<char>(65 + (rand() % 25))));
    test2.insert(std::make_pair(7, static_cast<char>(65 + (rand() % 25))));
    test2.insert(std::make_pair(8, static_cast<char>(65 + (rand() % 25))));
    test2.insert(std::make_pair(9, static_cast<char>(65 + (rand() % 25))));
    std::cout << test2.size() << "\n"; */
    /* test.insert(std::make_pair(1, 'c'));
    test.insert(std::make_pair(0, 'a')); */
    make_tree(test);
    ft::rbtree<int, std::pair<int, char> >::iterator    it;
    it = test.begin();
    test.insert(it, rand_pair());
    test.insert(it, rand_pair());
    test.insert(it, rand_pair());
    test.insert(it, rand_pair());
    test.insert(it, rand_pair());
    /* std::cout << test.begin()->first << "\n";
    std::cout << test.begin()->second << "\n"; */
    // std::map<int, char>     std_map;
    test.show();
    /* std::cout << test.begin()->first << "\n";
    std::cout << test.begin()->second << "\n";
    std::cout << "size: " << test.size() << "\n"; */
    return 0;
}
