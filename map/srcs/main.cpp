#include "includes/rbtree.hpp"
#include <cstdlib>
#include <ctime>
#include <functional>
#include <type_traits>
#include <utility>
#include <map>
#include <iostream>

#define NODES 35

template<class Key, class T>
void    make_tree(ft::rbtree<Key, T> &tree) {
    int     r_num;

    for (int i = 0; i < NODES + 1; i++) {
        r_num = rand() % NODES;
        // std::cout << "i = " << i << "\t" << "number = " << number << "\n";
        if (i == 1)
            continue;
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

void    show_stdmap(std::map<int, char> map) {
    std::map<int, char>::iterator   it = map.begin();
    for (; it != map.end(); it++) {
        std::cout << it->first << " " << it->second << "\t";
    }
    std::cout << "\n";
}

template<class Key, class T>
void    show_rbtree(ft::rbtree<Key, T> &rbtree) {
    std::cout << "mytree: " << "\n";
    ft::rbtree<int, std::pair<int, char> >::iterator   it = rbtree.begin();
    // it++;
    for (; it != rbtree.end(); it++) {
        std::cout << it->first << " " << it->second << "\t";
    }
    std::cout << "\n";
}

int main(void)
{
    srand(time(0));
    ft::rbtree<int, std::pair<int, char> >      test;
    std::map<int, char>                         std_map;
    std_map.insert(std::make_pair(1, static_cast<char>(65 + (rand() % 25))));
    std_map.insert(std::make_pair(3, static_cast<char>(65 + (rand() % 25))));
    std_map.insert(std::make_pair(4, static_cast<char>(65 + (rand() % 25))));
    std_map.insert(std::make_pair(5, static_cast<char>(65 + (rand() % 25))));
    std_map.insert(std::make_pair(6, static_cast<char>(65 + (rand() % 25))));
    std_map.insert(std::make_pair(7, static_cast<char>(65 + (rand() % 25))));
    std_map.insert(std::make_pair(8, static_cast<char>(65 + (rand() % 25))));
    std_map.insert(std::make_pair(9, static_cast<char>(65 + (rand() % 25))));
    std_map.insert(std::make_pair(10, static_cast<char>(65 + (rand() % 25))));
    show_stdmap(std_map);
    std::map<int, char>::iterator   it = std_map.begin();
    it++;
    it++;
    std_map.insert(it, std::make_pair(2, static_cast<char>(65 + (rand() % 25))));
    show_stdmap(std_map);
    ft::rbtree<int, std::pair<int, char> >::iterator     itm;
    make_tree(test);
    show_rbtree(test);
    itm = test.end();
    itm--;
    std::cout <<  itm->first << "\n";
    // show_rbtree(test);
    // show_rbtree(test);
    /* test.show();
    test.insert(itm, std::make_pair(2, static_cast<char>(65 + (rand() % 25))));
    std::cout << "====================================" << "\n";
    test.show(); */
    /* test.insert(std::make_pair(1, 'c'));
    test.insert(std::make_pair(0, 'a')); */
    return 0;
}
