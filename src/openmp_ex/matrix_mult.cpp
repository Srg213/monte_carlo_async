#include <iostream>
#include <vector>
#include <omp.h>

// Function to multiply a matrix by a vector
std::vector<int> multiplyMatrixVector(const std::vector<std::vector<int>>& matrix, const std::vector<int>& vec) {
    if (matrix.empty() || matrix[0].size() != vec.size()) {
        throw std::invalid_argument("Matrix dimensions do not match vector size");
    }

    std::vector<int> result(matrix.size(), 0);

    #pragma omp parallel for
    for (size_t i = 0; i < matrix.size(); ++i) {
        int thread_num = omp_get_thread_num();
        #pragma omp critical
        {
            std::cout << "Thread " << thread_num << " is processing element " << i << std::endl;
        }
        for (size_t j = 0; j < vec.size(); ++j) {

            result[i] += matrix[i][j] * vec[j];
        }
    }

    return result;
}

int main() {
    const size_t matrix_size = 1000; // Define the size of the matrix and vector
    std::vector<std::vector<int>> matrix(matrix_size, std::vector<int>(matrix_size, 1)); // Initialize a large matrix with all elements set to 1
    std::vector<int> vec(matrix_size, 1); // Initialize a large vector with all elements set to 1

    std::vector<int> result = multiplyMatrixVector(matrix, vec);

    std::cout << std::endl;

    return 0;
}