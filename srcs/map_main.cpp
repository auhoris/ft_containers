#include <iostream>
#include <map>
#include <set>

#include "../map.hpp"
#include "map_test.hpp"

#define NODES 100

template <class Key, class T>
void make_tree(ft::rbtree<Key, T> &tree) {
    int r_num;

    for (int i = 0; i < NODES + 1; i++) {
        r_num = rand() % NODES;
        tree.insert(std::make_pair(i, static_cast<char>(65 + (rand() % 25))));
    }
}

template <class Key, class T>
void fill_map(ft::map<Key, T> &map) {
    int start;
    int end;

    start = clock();
    for (int i = 0; i < NODES + 1; i++) {
        map.insert(ft::make_pair(i, static_cast<char>(65 + (rand() % 25))));
    }
    end = clock();
    std::cout << "ft: " << std::endl;
    std::cout << "it took [ " << end - start << " ] ticks, or "
              << ((float)end - start) / CLOCKS_PER_SEC << "seconds.\n";
}

int main() {
    insert_test();
    std::cout << "\n\n";
    constructor_tests();
    std::cout << "\n\n";
    erase_test();
    std::cout << "\n\n";
    find_test();
    std::cout << "\n\n";
    lower_upper_bound();
    std::cout << "\n";
    mixup();
    return (0);
}
