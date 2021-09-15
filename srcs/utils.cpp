#include "vector_test.hpp"

void    time(int start, int end) {
    std::cout << "[ " << end - start << " ] ticks: "
        << ((float)end - start)/CLOCKS_PER_SEC << " seconds.\n";
}
