#include "includes/map.hpp"
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iterator>
#include <type_traits>
#include <utility>
#include <map>
#include <iostream>

#define NODES 100

int    start;
int    end;
int    num;

std::pair<int, char> rand_pair();

template<class Key, class T>
void    make_tree(ft::rbtree<Key, T> &tree) {
    int     r_num;

    for (int i = 0; i < NODES + 1; i++) {
        r_num = rand() % NODES;
        tree.insert(std::make_pair(i, static_cast<char>(65 + (rand() % 25))));
    }
}

template<class Key, class T>
void    fill_map(ft::map<Key, T> & map) {

    start = clock();
    for (int i = 0; i < NODES + 1; i++) {
        map.insert(std::make_pair(i, static_cast<char>(65 + (rand() % 25))));
    }
    end = clock();
    std::cout << "ft: " << std::endl;
    std::cout << "it took [ " << end - start << " ] ticks, or "
        << ((float)end - start)/CLOCKS_PER_SEC << "seconds.\n";
}

template<class Key, class T>
void    std_fill_map(std::map<Key, T> & map) {

    start = clock();
    for (int i = 0; i < NODES + 1; i++) {
        map.insert(std::make_pair(i, static_cast<char>(65 + (rand() % 25))));
    }
    end = clock();
    std::cout << "ft: " << std::endl;
    std::cout << "it took [ " << end - start << " ] ticks, or "
        << ((float)end - start)/CLOCKS_PER_SEC << "seconds.\n";
}

template<class Key, class T>
void    show_map(ft::map<Key, T> & map) {
    typename ft::map<Key, T>::iterator it = map.begin();

    std::cout << "[ " << std::addressof(map) << " ]" << "\n";
    for (; it != map.end(); it++) {
        std::cout << it->first << " ";
    }
    std::cout << "\n";
}

std::pair<int, char> rand_pair() {
    std::pair<int, char>    par;

    par = std::make_pair(rand() % 100, static_cast<char>(65 + (rand() % 25)));
    return (par);
}

void    show_stdmap(std::map<int, char> map) {
    std::map<int, char>::iterator   it = map.begin();
    for (; it != map.end(); it++) {
        std::cout << it->first << " " << it->second << "\t";
    }
    std::cout << "\n";
}

int main(void) {

    ft::map<int, char>  map1;
    std::map<int, char>  stdap;
    map1[1] = 'c';
    show_map(map1);

    ft::map<char,std::string> mymap;

    mymap['a']="an element";
    mymap['b']="another element";
    mymap['c']=mymap['b'];

    std::cout << "mymap['a'] is " << mymap['a'] << '\n';
    std::cout << "mymap['b'] is " << mymap['b'] << '\n';
    std::cout << "mymap['c'] is " << mymap['c'] << '\n';
    std::cout << "mymap['d'] is " << mymap['d'] << '\n';

    std::cout << "mymap now contains " << mymap.size() << " elements.\n";

    // show_map(map2);
    return 0;
}
