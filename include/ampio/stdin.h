// amp's Input Parsing Library
//
// Namespace: ampio
// Contract: each Read*() consumes exactly ONE line from stdin.
// Primitives: int, long long, double, char and std::string.

#pragma once

#include <algorithm>

#include "internal/core.h"

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

}  // namespace ampio
