// amp's Output Printing Library
//
// Namespace: ampio
// Contract: each Print() outputs a value with its respective type.

#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace ampio {

template <typename T> inline void Print(const T& val) {
    std::cout << val << "\n";
}

template <typename T> inline void Print(const std::vector<T>& array) {
    std::cout << "[";
    for (size_t i = 0; i < array.size(); ++i) {
        if (i > 0) {
            std::cout << ",";
        }

        std::cout << array[i];
    }
    std::cout << "]\n";
}

template <> inline void Print(const std::vector<bool>& array) {
    std::cout << "[";
    for (size_t i = 0; i < array.size(); ++i) {
        if (i > 0) {
            std::cout << ",";
        }

        std::cout << (array[i] ? "true" : "false");
    }
    std::cout << "]\n";
}

template <> inline void Print(const std::vector<std::string>& array) {
    std::cout << "[";
    for (size_t i = 0; i < array.size(); ++i) {
        if (i > 0) {
            std::cout << ",";
        }

        std::cout << "\"" << array[i] << "\"";
    }
    std::cout << "]\n";
}

template <typename T> void Print(const std::vector<std::vector<T>>& matrix) {
    std::cout << "[";
    for (size_t i = 0; i < matrix.size(); ++i) {
        if (i > 0) {
            std::cout << ",";
        }

        Print(matrix[i]);
    }
    std::cout << "]\n";
}

}  // namespace ampio
