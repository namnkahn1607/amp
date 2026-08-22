// Internal helpers of amp's Input Parsing Library.

#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace ampio {

constexpr const char* kSpaceTabs = " \t";

namespace internal {

constexpr const char* kWhiteSpaces = " \t\r\n";

constexpr const char kComma = ',';
constexpr const char kQuote = '"';

constexpr const char kOpenParenthesis  = '(';
constexpr const char kCloseParenthesis = ')';

constexpr const char kOpenBracket  = '[';
constexpr const char kCloseBracket = ']';

// Read ONE full line from stdin. Skipping blank lines.
inline std::string ReadLine() {
    std::string line;
    while (std::getline(std::cin, line)) {
        // Trim leading whitespaces.
        const size_t start = line.find_first_not_of(kWhiteSpaces);
        if (start == std::string::npos) {
            continue;
        }

        const size_t end = line.find_last_not_of(kWhiteSpaces);
        return line.substr(start, end - start + 1);
    }

    return "";
}

// Split a flat bracket content: `[a,b,c] -> {"a","b","c"}`.
// NOTE: only strips ONE depth.
inline std::vector<std::string> SplitTokens(const std::string& content) {
    std::vector<std::string> tokens;

    int         depth    = 0;
    bool        in_quote = false;
    std::string curr;

    for (char c : content) {
        if (c == kQuote) {
            in_quote = !in_quote;
            curr += c;
            continue;
        }

        if (in_quote) {
            curr += c;
            continue;
        }

        if (c == kOpenParenthesis || c == kOpenBracket) {
            ++depth;
            curr += c;

        } else if (c == kCloseParenthesis || c == kCloseBracket) {
            --depth;
            curr += c;

        } else if (c == kComma && depth == 0) {
            // This is the end of the token.
            std::string tok = curr;

            const size_t start = tok.find_first_not_of(kSpaceTabs);
            const size_t end   = tok.find_last_not_of(kSpaceTabs);
            if (start != std::string::npos) {
                tokens.push_back(tok.substr(start, end - start + 1));
            }

            curr.clear();

        } else {
            curr += c;
        }
    }

    // Processing last token.
    const size_t start = curr.find_first_not_of(kSpaceTabs);
    const size_t end   = curr.find_last_not_of(kSpaceTabs);
    if (start != std::string::npos) {
        tokens.push_back(curr.substr(start, end - start + 1));
    }

    return tokens;
}

// Strip outer brackets: `"[1,2,3]" -> "1,2,3"`.
// Assume that brackets exist; throw on malformed input.
inline std::string StripBrackets(const std::string& line) {
    const size_t open  = line.find(kOpenBracket);
    const size_t close = line.rfind(kCloseBracket);
    if (open == std::string::npos || close == std::string::npos ||
        open >= close) {
        throw std::invalid_argument(
            "[ampio] expected \"[...]\", got \"" + line + "\""
        );
    }

    return line.substr(open + 1, close - open - 1);
}

// StripQuotes strips surrounding quotes of a string token: `"hello" -> hello`.
inline std::string StripQuotes(const std::string& str) {
    if (str.size() >= 2 && str.front() == kQuote && str.back() == kQuote) {
        return str.substr(1, str.size() - 2);
    }

    return str;
}

template <typename T> T Parse(const std::string& tok);

template <> inline int Parse<int>(const std::string& tok) {
    return std::stoi(tok);
}

template <> inline long long Parse<long long>(const std::string& tok) {
    return std::stoll(tok);
}

template <> inline double Parse<double>(const std::string& tok) {
    return std::stod(tok);
}

// Accept `a` or `"a"`.
template <> inline char Parse<char>(const std::string& tok) {
    std::string str = StripQuotes(tok);
    if (str.empty()) {
        throw std::invalid_argument("[ampio] empty char input");
    }

    return str[0];
}

// Accept `hello` or `"hello"`.
template <> inline std::string Parse<std::string>(const std::string& tok) {
    return StripQuotes(tok);
}

template <typename T> inline std::vector<T> ParseSeq(const std::string& inner) {
    std::vector<T> out;
    if (inner.find_first_not_of(kSpaceTabs) == std::string::npos) {
        return out;
    }

    for (const std::string& tok : SplitTokens(inner)) {
        out.push_back(Parse<T>(tok));
    }

    return out;
}

}  // namespace internal

}  // namespace ampio
