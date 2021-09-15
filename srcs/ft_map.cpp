#include "../map.hpp"
#include <map>
#include <set>

#define NODES 100

int    start;
int    end;
int    num;

ft::pair<int, char> rand_pair();

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
        map.insert(ft::make_pair(i, static_cast<char>(65 + (rand() % 25))));
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

ft::pair<int, char> rand_pair() {
    ft::pair<int, char>    par;

    par = ft::make_pair(rand() % 100, static_cast<char>(65 + (rand() % 25)));
    return (par);
}

int main() {
    ft::map<int, char>  map;

    fill_map(map);
    map.erase(map.lower_bound(10), map.upper_bound(60));
    show_map(map);
    return (0);
}
