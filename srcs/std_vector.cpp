#include "vector_test.hpp"
#include <vector>

std::vector<int>    std_push_back() {
    std::vector<int> vector;
    int    start;
    int    end;

    std::cout << "[ " << ITERATIONS << " ]\t";
    start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        vector.push_back(i);
    }
    end = clock();
    std::cout << "\nstd: ";
    time(start, end);
    return (vector);
}
