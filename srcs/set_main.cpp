#include "../set.hpp"

template<class T>
void    show_set(ft::set<T> set) {
    typename ft::set<T>::iterator    it = set.begin();

    while (it != set.end()) {
        std::cout << *it << " ";
        it++;
    }
    std::cout << "\n";
}

int main(void)
{
    ft::set<int>    set;

    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.insert(4);
    set.insert(5);
    set.insert(7);
    set.insert(8);
    set.insert(9);
    set.insert(10);
    set.insert(11);
    ft::set<int>::iterator  it = set.begin();
    show_set(set);
    ft::set<int>    set2(set.lower_bound(2), set.upper_bound(9));
    set2.erase(set2.lower_bound(4), set2.upper_bound(7));
    show_set(set2);
    return 0;
}
