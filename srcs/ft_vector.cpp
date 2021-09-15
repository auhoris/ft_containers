#include "vector_test.hpp"

ft::vector<int>    ft_push_back() {
    ft::vector<int> vector;
    int    start;
    int    end;

    std::cout << "[ " << ITERATIONS << " ]\t";
    start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        vector.push_back(i);
    }
    end = clock();
    std::cout << "\nft: ";
    time(start, end);
    return (vector);
}
