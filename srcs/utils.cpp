#include "vector_test.hpp"
#include <iostream>

void time(int start, int end) {
    std::cout << "[" << GREEN << end - start << RESET << "] ticks && "
              << "[" << GREEN << ((float)end - start) / CLOCKS_PER_SEC
              << RESET << "]"
              << " sec.\n";
}

void percentage_compare(int std_ticks, int ft_ticks) {
    double per;
    if (ft_ticks > std_ticks) {
        std::cout << "FT SLOWER BY ";
        per = ((float)std_ticks / ft_ticks) * 100;
        std::cout << YELLOW "[" << 100 - per  << "%]\n" << RESET;
    } else {
        std::cout << "FT FASTER BY ";
        per = ((float)ft_ticks / std_ticks) * 100;
        std::cout << BOLDCYAN << "[" <<  100 -per  << "%]\n" << RESET;
    }
}

void checker(bool equal) {
    if (equal)
        std::cout << GREEN << "[OK]" << RESET << "\n";
    else
        std::cout << BOLDRED << "[ERROR]" << RESET << "\n";
}
