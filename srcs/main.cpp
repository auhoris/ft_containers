#include "../vector.hpp"
#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

void    test() {
    for (int i = 0; i < 5; i++) {
        std::cout << "bla" << "\n";
    }
}

int main(void) {
    /* int             arr1[5] = {1, 2, 3, 4, 5};
    ft::vector<int> v1(arr1, arr1 + 5);
    ft::vector<int>::iterator it;

    it = v1.erase(v1.begin());
    std::cout << "->" << (v1.size() == 4) << "\n";
    std::cout << "->" << (v1.capacity() >= 4) << "\n";
    for (size_t i = 0; i < 4; i++)
        std::cout  << "v1[i]: " << v1[i] << " arr1[i +1]: " << arr1[i + 1] << "\t";
    std::cout << "->" << (*it == 2) << "\n";
    std::cout << "\n";

    it = v1.erase(v1.end() - 1);
    std::cout << "->" << (v1.size() == 3) << "\n";
    std::cout << "->" << (v1.capacity() >= 3) << "\n";
    for (size_t i = 0; i < 3; i++)
        std::cout  << "v1[i]: " << v1[i] << " arr1[i +1]: " << arr1[i + 1] << "\t";
    std::cout << "\n";
    std::cout << "->" << (it == v1.end()) << "\n";

    it = v1.erase(v1.end() - 2);
    std::cout << "->" << (v1.size() == 2) << "\n";
    std::cout << "->" << (v1.capacity() >= 2) << "\n";
    std::cout << "->" << (v1[0] == 2) << "\n";
    std::cout << "->" << (v1[1] == 4) << "\n";
    std::cout << "->" << (*it == 4) << "\n";

    v1.assign(arr1, arr1 + 5);
    v1.show_data();
    it = v1.erase(v1.begin() + 1, v1.begin() + 3);
    v1.show_data();
    std::cout << "size->" << (v1.size() == 3) << "\n";
    std::cout << "capacity->" << (v1.capacity() >= 3) << "\n";
    std::cout << "v1[0]->" << (v1[0] == 1) << "\n";
    std::cout << "v1[1]->" << (v1[1] == 4) << "\n";
    std::cout << "v1[2]->" << (v1[2] == 5) << "\n";
    std::cout << "*it->" << (*it == 4) << "\n";

    it = v1.erase(v1.begin() + 1, v1.end());
    std::cout << "size->" << (v1.size() == 1) << "\n";
    std::cout << "capacity->" << (v1.capacity() >= 1) << "\n";
    std::cout << "v1[0]->" << (v1[0] == 1) << "\n";
    std::cout << "it == v1.end->" << (it == v1.end()) << "\n"; */

    /* ft::vector<int> v1;
    ft::vector<int>::iterator it;

    it = v1.insert(v1.end(), 1);
    std::cout << "->" << (v1.size() == 1) << "\n";
    std::cout << "->" << (v1.capacity() >= 1) << "\n";
    std::cout << "->" << (v1[0] == 1) << "\n";
    std::cout << "->" << (*it == 1) << "\n";

    it = v1.insert(v1.end(), 2);
    std::cout << "->" << (v1.size() == 2) << "\n";
    std::cout << "->" << (v1.capacity() >= 2) << "\n";
    std::cout << "->" << (v1[0] == 1) << "\n";
    std::cout << "->" << (v1[1] == 2) << "\n";
    std::cout << "->" << (*it == 2) << "\n";

    it = v1.insert(v1.begin(), 0);
    std::cout << "->" << (v1.size() == 3) << "\n";
    std::cout << "->" << (v1.capacity() >= 3) << "\n";
    std::cout << "->" << (v1[0] == 0) << "\n";
    std::cout << "->" << (v1[1] == 1) << "\n";
    std::cout << "->" << (v1[2] == 2) << "\n";
    std::cout << "->" << (*it == 0) << "\n";

    int             arr1[5] = {1, 2, 3, 4, 5};
    v1.insert(v1.begin() + 1, arr1 + 1, arr1 + 4);
    v1.show_data();
    std::cout << "size->" << (v1.size() == 6) << "\n";
    std::cout << "capacity->" << (v1.capacity() >= 6) << "\n";
    std::cout << "v1[0]->" << (v1[0] == 0) << "\n";
    std::cout << "v1[1]->" << (v1[1] == 2) << "\n";
    std::cout << "v1[2]->" << (v1[2] == 3) << "\n";
    std::cout << "v1[3]->" << (v1[3] == 4) << "\n";
    std::cout << "v1[4]->" << (v1[4] == 1) << "\n";
    std::cout << "v1[5]->" << (v1[5] == 2) << "\n";

    v1.insert(v1.begin() + 2, (size_t)3, (int)-1);
    std::cout << "size->" << (v1.size() == 9) << "\n";
    std::cout << "capacity->" << (v1.capacity() >= 9) << "\n";
    std::cout << "v1[0]->" << (v1[0] == 0) << "\n";
    std::cout << "v1[1]->" << (v1[1] == 2) << "\n";
    std::cout << "v1[2]->" << (v1[2] == -1) << "\n";
    std::cout << "v1[3]->" << (v1[3] == -1) << "\n";
    std::cout << "v1[4]->" << (v1[4] == -1) << "\n";
    std::cout << "v1[5]->" << (v1[5] == 3) << "\n";
    std::cout << "v1[6]->" << (v1[6] == 4) << "\n";
    std::cout << "v1[7]->" << (v1[7] == 1) << "\n";
    std::cout << "v1[8]->" << (v1[8] == 2) << "\n"; */

    // size_t n = 10;
    // test.rend
    // vec2.show_data();
    // std::vector<int> vec1("sd", n);
    // test(0);
    // ft::vector<int> vec1(vec.begin(), vec.end());
    // vec.show_data();
    // std::cout << std::__is_input_iterator<std::vector<int>::iterator>::value << "\n";
    // int             arr1[5] = {1, 2, 3, 4, 5};
    /* std::vector<int> v1(arr1, arr1 + 5);

    std::cout << ft::is_iterator<ft::vector<int>::iterator::iterator_category>::value << "\n"; */
    // std::cout << ft::is_same<ft::random_access_iterator_tag, ft::vector<int>::iterator::iterator_category>::value << "\n";
    // std::vector<int>::iterator it = v1.end();
    // std::cout << ft::is_integral<int>::value << "\n";
    /* std::cout << "->" << (v1_it[-1] == 1) << "\n";
    std::cout << "->" << (v1_it[-2] == 2) << "\n";
    std::cout << "->" << (v1_it[-3] == 3) << "\n";
    std::cout << "->" << (v1_it[-4] == 4) << "\n";
    std::cout << "->" << (v1_it[-5] == 5) << "\n";

    std::cout << "->" << (v1_it == v1.rend()) << "\n";
    std::cout << "->" << (v1_it != v1.rbegin()) << "\n";
    std::cout << "|->" << (v1_it != v1.begin()) << "\n";
    std::cout << "->" << (v1_it != v1.end()) << "\n";

    std::cout << "->" << (v1_it >= v1.rend()) << "\n";
    std::cout << "->" << (v1_it >= v1.rend()) << "\n";
    std::cout << "->" << (v1_it <= v1.rend()) << "\n";
    std::cout << "->" << (v1_it <= v1.rend()) << "\n";
    std::cout << "->" << (v1_it > v1.rbegin()) << "\n";

    v1_it--;
    for (size_t i = 0; i < v1.size(); i++)
        std::cout << "->" << (*(v1_it - i) == arr1[i]) << "\n"; */
    ft::vector<int> vec(10, 10);
    ft::vector<int>::const_iterator   beg = vec.begin();
    ft::vector<int>::iterator   end;

    return 0;
}
