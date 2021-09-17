#ifndef __SRCS_VECTOR_TEST_HPP__
#define __SRCS_VECTOR_TEST_HPP__

#include <vector>

#include "../utils/algorithm.hpp"
#include "../vector.hpp"
#include "utils.hpp"

#define ITERATIONS 100

template <class T>
void show_ft_vector(ft::vector<T> & vector) {
    ft::vector<int>::iterator it = vector.begin();

    while (it != vector.end()) {
        std::cout << *it << " ";
        it++;
    }
    std::cout << " --> ft"
              << "\n";
    std::cout << "\n";
}

template <class T>
void show_std_vector(std::vector<T> & vector) {
    std::vector<int>::iterator it = vector.begin();

    std::cout << "FT TEST: "
              << "\n";
    while (it != vector.end()) {
        std::cout << *it << " ";
        it++;
    }
    std::cout << " --> std"
              << "\n";
    std::cout << "\n";
}

ft::vector<int> ft_push_back();
std::vector<int> std_push_back();
void push_back();
void pop_back();
void assign();
void insert();
void constructor_test();
void ft_vector_tests();
void throw_test();

#endif /* ifndef __SRCS_VECTOR_TEST_HPP__ */
