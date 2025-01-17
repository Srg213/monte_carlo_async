#include "utils.h"
#include <iostream>
#include <omp.h>
#include <vector>



std::vector<int> addVectors(const std::vector<int>& a, const std::vector<int>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vectors must be of the same length");
    }

    std::vector<int> result(a.size());

    #pragma omp parallel for
    for (size_t i = 0; i < a.size(); ++i) {
        // int thread_num = omp_get_thread_num();
        // std::cout << "Thread " << thread_num << " is processing element " << i << std::endl;
        result[i] = a[i] + b[i];
    }

    return result;
}


int main() {
    std::cout << "Vector addition using openmp pragma prallel for" << std::endl;
    

    // Example usage of addVectors
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::vector<int> vec2 = {6, 7, 8, 9, 10};
    std::vector<int> result = addVectors(vec1, vec2);

    std::cout << "Result of vector addition: ";
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}