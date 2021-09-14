#include "includes/rbtree.hpp"
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iterator>
#include <type_traits>
#include <utility>
#include <map>
#include <iostream>

#define NODES 25

template<class Key, class T>
void    make_tree(ft::rbtree<Key, T> &tree) {
    int     r_num;

    for (int i = 0; i < NODES + 1; i++) {
        r_num = rand() % NODES;
        // std::cout << "i = " << i << "\t" << "number = " << number << "\n";
        // if (i == 1)
        //     continue;
        tree.insert(std::make_pair(i, static_cast<char>(65 + (rand() % 25))));
    }
}

std::pair<int, char> rand_pair() {
    std::pair<int, char>    par;

    par = std::make_pair(rand() % 100, static_cast<char>(65 + (rand() % 25)));
    // std::cout << par.first << "\t";
    // std::cout << par.second << "\n";
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
    ft::rbtree<int, std::pair<int, char> >::iterator   tmp;
    int i = 0;

    while (it != rbtree.end()) {
        tmp = it;
        it++;
        std::cout << "[" << i << "]"<< tmp->first << " ";
        rbtree.erase(tmp);
        i++;
    }
    std::cout << "\n";
}

int main(void)
{
    srand(time(0));
    ft::rbtree<int, std::pair<int, char> >      test;

    make_tree(test);
    test.show();
    test.clear();
    test.show();
    // ft::rbtree<int, std::pair<int, char> >::iterator    it = test.begin();
    // test.show();
    // test.erase(6);
    // test.show();
    // it = test.begin();
    // test.erase(it);
    // test.show();
    // rev_it = test.rbegin();
    // while (rev_it != test.rend()) {
    //     std::cout << rev_it->first  << " ";
    //     rev_it++;
    // }
    // std::cout << "\n";
    return 0;
}
