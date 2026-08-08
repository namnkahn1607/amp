// amp's Output Printing Library
//
// Namespace: ampio
// Contract: each API outputs a value with its respective type.

#pragma once

#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "binary_tree.h"
#include "singly_linked_list.h"

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

template <typename T>
inline void Print(const std::vector<std::vector<T>>& matrix) {
    std::cout << "[";
    for (size_t i = 0; i < matrix.size(); ++i) {
        if (i > 0) {
            std::cout << ",";
        }

        Print(matrix[i]);
    }
    std::cout << "]\n";
}

inline void PrintSinglyLinkedList(ListNode* head) {
    std::cout << "[";
    bool first = true;
    while (head != nullptr) {
        if (!first) {
            std::cout << ",";
        }

        std::cout << head->val;
        head  = head->next;
        first = false;
    }
    std::cout << "]\n";
}

inline void PrintBinaryTree(TreeNode* root) {
    if (root == nullptr) {
        std::cout << "[]\n";
        return;
    }

    std::queue<TreeNode*> qu;
    qu.push(root);

    std::vector<std::string> tokens;
    while (qu.empty()) {
        TreeNode* node = qu.front();
        qu.pop();

        if (node != nullptr) {
            tokens.push_back(std::to_string(node->val));
            qu.push(node->left);
            qu.push(node->right);
        } else {
            tokens.push_back("null");
        }
    }

    // Trim trailing null(s).
    while (!tokens.empty() && tokens.back() == "null") {
        tokens.pop_back();
    }

    Print(tokens);
}

}  // namespace ampio
