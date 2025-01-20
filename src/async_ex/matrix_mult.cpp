#include <iostream>
#include <vector>
#include <future>

// Function to multiply a row of the matrix by the vector
int multiplyRowByVector(const std::vector<int>& row, const std::vector<int>& vec) {
    int result = 0;
    for (size_t j = 0; j < vec.size(); ++j) {
        result += row[j] * vec[j];
    }
    return result;
}

// Function to multiply a matrix by a vector using std::async
std::vector<int> multiplyMatrixVector_async(const std::vector<std::vector<int>>& matrix, const std::vector<int>& vec) {
    if (matrix.empty() || matrix[0].size() != vec.size()) {
        throw std::invalid_argument("Matrix dimensions do not match vector size");
    }

    std::vector<int> result(matrix.size());
    std::vector<std::future<int>> futures(matrix.size());

    // Launch asynchronous tasks for each row of the matrix
    for (size_t i = 0; i < matrix.size(); ++i) {
        futures[i] = std::async(std::launch::async, multiplyRowByVector, std::ref(matrix[i]), std::ref(vec));
    }

    // Retrieve the results from the asynchronous tasks
    for (size_t i = 0; i < matrix.size(); ++i) {
        result[i] = futures[i].get();
    }

    return result;
}

int main() {
    const size_t matrix_size = 1000; // Define the size of the matrix and vector
    std::vector<std::vector<int>> matrix(matrix_size, std::vector<int>(matrix_size, 1)); // Initialize a large matrix with all elements set to 1
    std::vector<int> vec(matrix_size, 1); // Initialize a large vector with all elements set to 1

    std::vector<int> result = multiplyMatrixVector_async(matrix, vec);

    std::cout << "Result of matrix-vector multiplication: ";
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}