#include "includes/rbtree.hpp"
#include <cstdlib>
#include <ctime>
#include <functional>
#include <type_traits>
#include <utility>
#include <map>
#include <iostream>

#define NODES 27
template<class Key, class T>
void    make_tree(ft::rbtree<Key, T> &tree) {
    for (int i = 0; i < NODES; i++) {
        tree.insert(std::make_pair(i + 1, static_cast<char>(65 + (rand() % 25))));
    }
}
typedef std::__select_2nd<int, char>    value_of_key;
int main(void)
{
    srand(time(0));
    ft::rbtree<int, std::pair<int, char> >    test;
    std::map<int, char>     std_map;
    std::pair<int, char>    one;
    std::pair<int, char>    two;
    std::pair<int, char>    tree;
    std::pair<int, char>    ret;

    one = std::make_pair(100, 'b');
    test.insert(one);
    std_map.insert(one);
    one = std::make_pair(200, 'a');
    test.insert(one);
    std_map.insert(one);
    one = std::make_pair(300, 'c');
    test.insert(one);
    std_map.insert(one);
    one = std::make_pair(400, 'c');
    test.insert(one);
    std_map.insert(one);
    one = std::make_pair(500, 'c');
    test.insert(one);
    std_map.insert(one);
    std::cout << std_map.begin()->first << std::endl;
    std::cout << (--std_map.end())->first << std::endl;
    std::cout << "my: " << test.begin()->first << std::endl;
    std::cout << "my: " << test.end()->first << std::endl;
    // make_tree(test);
    test.show();
    /* ret = test.search(std::make_pair(3, 'c'));
    std::cout << ret.first << std::endl;
    std::cout << ret.second << std::endl; */
    return 0;
}
