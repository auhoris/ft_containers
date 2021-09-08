#include "includes/rbtree.hpp"
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iterator>
#include <type_traits>
#include <utility>
#include <map>
#include <iostream>

#define NODES 20

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
    ft::rbtree<int, std::pair<int, char> >      test2;
    ft::rbtree<int, std::pair<int, char> >::iterator it;
    ft::rbtree<int, std::pair<int, char> >::reverse_iterator   rev_it;
    /* std::map<int, char>                         std_map;
    std_map.insert(std::make_pair(1, static_cast<char>(65 + (rand() % 25))));
    std_map.insert(std::make_pair(3, static_cast<char>(65 + (rand() % 25))));
    std_map.insert(std::make_pair(4, static_cast<char>(65 + (rand() % 25))));
    std_map.insert(std::make_pair(5, static_cast<char>(65 + (rand() % 25))));
    std_map.insert(std::make_pair(6, static_cast<char>(65 + (rand() % 25))));
    std_map.insert(std::make_pair(7, static_cast<char>(65 + (rand() % 25))));
    std_map.insert(std::make_pair(8, static_cast<char>(65 + (rand() % 25))));
    std_map.insert(std::make_pair(9, static_cast<char>(65 + (rand() % 25))));
    std_map.insert(std::make_pair(10, static_cast<char>(65 + (rand() % 25))));
    std::cout << std_map.max_size() << "\n"; */
    it = test.begin();
    /* std::cout << test.empty() << "\n";
    std::cout << test.max_size() << "\n"; */
    /* std::map<int, char>::iterator   mapit = std_map.end();
    while (mapit != std_map.begin()) {
        std::cout << mapit->first << mapit->second << "\n";
        mapit--;
    } */
    // std::cout << test.begin()->first << "\n";
    // std::cout << test.empty() << "\n";
    make_tree(test);
    test.show();
    rev_it = test.rbegin();
    while (rev_it != test.rend()) {
        std::cout << rev_it->first  << " ";
        rev_it++;
    }
    // std::cout << rev_it->first;
    std::cout << "\n";
    /* it = test.end();
    int i = 0;
    while (it != test.begin()) {
        std::cout << it->first << " " << it->second << "\n";
        it--;
        i++;
    }
    std::cout << it->first << " " << it->second << "\n"; */
    /* std::cout << rev_it->first << "\n";
    std::cout << rev_it->second << "\n"; */
    /* test.show();
    it = test.begin();
    std::advance(it, 1);
    test.insert(it, std::make_pair(2, 'c'));
    test.show(); */
    /* make_tree(test2);
    test2.show();
    test2.insert(test.begin(), test.end());
    test2.show(); */
    // test.insert(itm, std::make_pair(2, static_cast<char>(65 + (rand() % 25))));
    /* test.insert(std::make_pair(1, 'c'));
    test.insert(std::make_pair(0, 'a')); */
    return 0;
}
