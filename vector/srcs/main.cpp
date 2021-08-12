#include "includes/vector.hpp"
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#define DEBUG
#define TEST_SIZE 7
int main(void)
{

    srand(time(0));
    /* srand(time(0));
    std::vector<int>    vec(20);
    vec.push_back(1);
    vec.push_back(2);
    std::cout << vec.size() << " " << vec.capacity() << std::endl;
    std::cout << vec.end() - vec.begin() << std::endl;
    std::vector<int>    second(vec);

    std::cout << second.size() << " " << second.capacity() << std::endl;
    std::cout << second.end() - second.begin() << std::endl;
    std::cout << second.max_size() << std::endl; */

    //================

    /* ft::vector<int>    vec(20);

    std::cout << vec.size() << " " << vec.capacity() << std::endl;
    std::cout << vec.end() - vec.begin() << std::endl; */
    /* std::vector<int>    vec;
    for (int i = 0; i < TEST_SIZE; i++) {
        vec.push_back(rand() % 100);
    }
    ft::vector<int>     my_vec(vec.begin(), vec.end());
    size_t i = 0;
    for (auto it : my_vec) {
        std::cout << vec[i] << " ";
        std::cout << it << std::endl;
        i++;
    } */
    //=========================== Definetly good test
    int    start;
    int    end;
    int    num;

    start = clock();
    ft::vector<int>     my_vec;
    for (int i = 0; i < TEST_SIZE; i++) {
        num = rand() % 100;
        std::cout << num << " ";
        my_vec.push_back(num);
    }
    std::cout << std::endl;
    end = clock();
#ifdef DEBUG
    /* std::cout << "\nmy: " << std::endl;
    std::cout << "it took [ " << end - start << " ] ticks, or "
        << ((float)end - start)/CLOCKS_PER_SEC << "seconds.\n"; */
#endif
    my_vec.show_data();
    /* std::cout << "size in main: " << my_vec.size() << std::endl;
    std::cout << "capacity in main: " << my_vec.capacity() << std::endl; */
    // std::cout << my_vec.front() << " " << my_vec.back() << std::endl;
    ft::vector<int>     vec(my_vec);

    std::cout << "vec: " << std::endl;
    vec.show_data();

    /* start = clock();
    std::vector<int>     std_vec;
    for (int i = 0; i < TEST_SIZE; i++) {
        num = rand() % 100;
        std_vec.push_back(num);
    }
    end = clock();
    std::cout << "\nstandart: " << std::endl;
    std::cout << "it took [ " << end - start << " ] ticks, or "
        << ((float)end - start)/CLOCKS_PER_SEC << "seconds.\n"; */

    return 0;
}
