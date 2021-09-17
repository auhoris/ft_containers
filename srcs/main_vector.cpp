#include <vector>

#include "vector_test.hpp"

int main(void) {
    ft::vector<int> ft_vec = ft_push_back();
    std::vector<int> std_vec = std_push_back();

    bool equal = ft::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin());
    if (equal)
        std::cout << GREEN << "[OK]" << RESET << "\n";
    else
        std::cout << RED << "[ERROR]" << RESET << "\n";
    return 0;
}
