// amp's Input Parsing Library
//
// Namespace: ampio
// Contract: each API consumes exactly ONE line from stdin.
// Primitives: int, long long, double, char and std::string.

#pragma once

#include <algorithm>
#include <queue>

#include "dsa/binary_tree.h"
#include "internal/core.h"
#include "dsa/singly_linked_list.h"

namespace ampio {

// Parse and return value of primitive type `T`.
template <typename T> inline T ReadPrim() {
    return internal::Parse<T>(internal::ReadLine());
}

// Accept `"true"/"false"` (case-insensitive), `"1"/"0"`.
inline bool ReadBool() {
    std::string str = internal::ReadLine();
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    if (str == "true" || str == "1") {
        return true;
    }
    if (str == "false" || str == "0") {
        return false;
    }

    throw std::invalid_argument("[ampio] cannot parse boolean from: " + str);
}

// Parse and return value of type `std::vector<T>`.
// `T` is a primitive type.
template <typename T> inline std::vector<T> ReadArray() {
    return internal::ParseSeq<T>(internal::StripBrackets(internal::ReadLine()));
}

// Parse and return value of type `std::vector<std::vector<T>>`.
// `T` is a primitive type.
template <typename T> inline std::vector<std::vector<T>> ReadMatrix() {
    std::string outer = internal::StripBrackets(internal::ReadLine());

    std::vector<std::vector<T>> grid;
    for (const std::string& row_tok : internal::SplitTokens(outer)) {
        grid.push_back(internal::ParseSeq<T>(internal::StripBrackets(row_tok)));
    }

    return grid;
}

// Read Singly Linked List. Trailing `null` are skipped, otherwise thrown.
inline ListNode* ReadSinglyLinkedList() {
    std::string inner = internal::StripBrackets(internal::ReadLine());
    if (inner.find_first_not_of(kSpaceTabs) == std::string::npos) {
        return nullptr;
    }

    const std::vector<std::string> tokens = internal::SplitTokens(inner);
    if (tokens.empty()) {
        return nullptr;
    }

    ListNode  dummy(0);
    ListNode* curr = &dummy;

    for (const std::string& tok : tokens) {
        if (tok == "null") {
            throw std::invalid_argument(
                "[ampio] unexpected null at the middle of the linked list"
            );
        }

        curr->next = new ListNode(std::stoi(tok));
        curr       = curr->next;
    }

    return dummy.next;
}

// Read Binary Tree in BFS level-order format. `null` are skipped by default.
inline TreeNode* ReadBinaryTree() {
    std::string inner = internal::StripBrackets(internal::ReadLine());
    if (inner.find_first_not_of(kSpaceTabs) == std::string::npos) {
        return nullptr;
    }

    const std::vector<std::string> tokens = internal::SplitTokens(inner);
    if (tokens.empty() || tokens[0] == "null") {
        return nullptr;
    }

    TreeNode* root = new TreeNode(std::stoi(tokens[0]));

    std::queue<TreeNode*> qu;
    qu.push(root);

    size_t i = 1;
    while (!qu.empty() && i < tokens.size()) {
        TreeNode* node = qu.front();
        qu.pop();

        if (i < tokens.size() && tokens[i] != "null") {
            node->left = new TreeNode(std::stoi(tokens[i]));
            qu.push(node->left);
        }
        ++i;

        if (i < tokens.size() && tokens[i] != "null") {
            node->right = new TreeNode(std::stoi(tokens[i]));
            qu.push(node->right);
        }
        ++i;
    }

    return root;
}

}  // namespace ampio
