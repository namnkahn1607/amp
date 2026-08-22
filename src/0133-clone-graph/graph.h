// Graph.

#pragma once

#include <algorithm>
#include <cassert>
#include <queue>
#include <unordered_map>
#include <vector>

struct Node {
    int                val;
    std::vector<Node*> neighbors;

    Node()
        : val{0}
        , neighbors{} {}

    Node(int _val)
        : val{_val}
        , neighbors{} {}

    Node(int _val, std::vector<Node*> _neighbors)
        : val{_val}
        , neighbors{_neighbors} {}

    // Check if 2 graphs are "isomorphic" or not.
    static bool Compare(const Node* a, const Node* b) noexcept {
        assert(a != b && "Two graph nodes must be distinct");

        if (a == nullptr || b == nullptr) {
            return a == b;
        }

        std::unordered_map<int, const Node*> visited_a;
        visited_a.emplace(a->val, a);
        std::unordered_map<int, const Node*> visited_b;
        visited_b.emplace(b->val, b);

        std::queue<std::pair<const Node*, const Node*>> qu;
        qu.emplace(a, b);

        auto cmp = [](const Node* x, const Node* y) -> bool {
            return x->val < y->val;
        };
        while (!qu.empty()) {
            const auto [na, nb] = qu.front();
            assert(na != nb && "Two graph nodes must be distinct");
            qu.pop();

            if (na->val != nb->val ||
                na->neighbors.size() != nb->neighbors.size()) {
                return false;
            }

            std::vector<const Node*> neighbors_a(
                na->neighbors.begin(), na->neighbors.end()
            );
            std::vector<const Node*> neighbors_b(
                nb->neighbors.begin(), nb->neighbors.end()
            );

            std::sort(neighbors_a.begin(), neighbors_a.end(), cmp);
            std::sort(neighbors_b.begin(), neighbors_b.end(), cmp);

            for (size_t i = 0; i < neighbors_a.size(); ++i) {
                const Node* ca = neighbors_a[i];
                const Node* cb = neighbors_b[i];
                if (ca->val != cb->val) {
                    return false;
                }

                auto it_a = visited_a.find(ca->val);
                auto it_b = visited_b.find(cb->val);

                bool found_a = it_a != visited_a.end();
                bool found_b = it_b != visited_b.end();

                if (!found_a && !found_b) {
                    visited_a.emplace(ca->val, ca);
                    visited_b.emplace(cb->val, cb);
                    qu.emplace(ca, cb);
                } else if (found_a && found_b) {
                    if (it_a->second != ca || it_b->second != cb) {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        }

        return true;
    }
};
