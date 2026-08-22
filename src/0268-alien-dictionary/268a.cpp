// 268a. Alien Dictionary

#include <array>
#include <queue>
#include <string>
#include <vector>

#include "ampio/stdin.h"
#include "ampio/stdout.h"

std::string foreignDictionary(std::vector<std::string>& words) {
    constexpr char kA          = 'a';
    constexpr int  kNumLetters = 26;

    auto Atoi = [](char ch) __attribute__((always_inline))->int {
        return ch - kA;
    };
    auto Itoa = [](int idx) __attribute__((always_inline))->char {
        return char(idx + kA);
    };

    std::array<int, kNumLetters> in_degree;
    in_degree.fill(-1);

    uint letter_count = 0;
    for (auto& word : words) {
        for (auto& ch : word) {
            const auto idx = Atoi(ch);
            if (in_degree[idx] == -1) {
                in_degree[idx] = 0;
                ++letter_count;
            }
        }
    }

    std::array<std::vector<int>, kNumLetters> adjacency_list;
    for (auto& list : adjacency_list) {
        list.reserve(kNumLetters);
    }

    for (size_t i = 0; i < words.size() - 1; ++i) {
        const std::string& word_a = words[i];
        const std::string& word_b = words[i + 1];

        const size_t len_a = word_a.length();
        const size_t len_b = word_b.length();

        const auto min_len = std::min(len_a, len_b);

        // Invalid: word B is a prefix of word A, but comes after word A.
        if (len_a > len_b && word_a.compare(0, min_len, word_b) == 0) {
            return "";
        }

        for (size_t j = 0; j < min_len; ++j) {
            if (word_a[j] != word_b[j]) {
                const auto val_a = Atoi(word_a[j]);
                const auto val_b = Atoi(word_b[j]);

                adjacency_list[val_a].push_back(val_b);
                in_degree[val_b] += 1;
                break;
            }
        }
    }

    std::string order;
    order.reserve(letter_count);

    std::queue<int> qu;
    for (int idx = 0; idx < kNumLetters; ++idx) {
        if (in_degree[idx] == 0) {
            qu.push(idx);
        }
    }

    while (!qu.empty()) {
        const auto curr_idx = qu.front();
        qu.pop();
        order.push_back(Itoa(curr_idx));

        for (const auto& next_idx : adjacency_list[curr_idx]) {
            in_degree[next_idx] -= 1;
            if (in_degree[next_idx] == 0) {
                qu.push(next_idx);
            }
        }
    }

    return (order.size() != letter_count) ? "" : order;
}

int main() {
    // `1 <= words.length <= 100`.
    // `1 <= words[i].length <= 100`.
    // `words[i]` consists of only lowercase English letters.
    auto words = ampio::ReadArray<std::string>();
    ampio::Print(foreignDictionary(words));
    return 0;
}
