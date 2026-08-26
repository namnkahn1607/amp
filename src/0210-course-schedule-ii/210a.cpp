// 210a. Course Schedule II

#include <queue>
#include <vector>

#include "ampio/stdin.h"
#include "ampio/stdout.h"

class Solution {
public:
    std::vector<int> findOrder(
        int num_courses, std::vector<std::vector<int>>& prerequisites
    ) {
        std::vector<std::vector<int>> adjacency_list(num_courses);

        std::vector<int> in_degree(num_courses, 0);
        for (auto& preq : prerequisites) {
            int a = preq[0], b = preq[1];
            ++in_degree[a];
            adjacency_list[b].push_back(a);
        }

        std::vector<int> order;
        order.reserve(num_courses);

        std::queue<int> qu;
        for (int c = 0; c < num_courses; ++c) {
            if (in_degree[c] == 0) {
                qu.push(c);
            }
        }

        while (!qu.empty()) {
            auto course = qu.front();
            qu.pop();
            order.push_back(course);

            for (auto& next : adjacency_list[course]) {
                --in_degree[next];
                if (in_degree[next] == 0) {
                    qu.push(next);
                }
            }
        }

        return (order.size() == static_cast<size_t>(num_courses))
                   ? order
                   : std::vector<int>{};
    }
};

int main() {
    // `1 <= num_courses <= 2000`.
    // `0 <= prerequisites.length <= num_courses * (num_courses - 1)`.
    // `prerequisites[i].length == 2`.
    // `0 <= a_i, b_i < num_courses`.
    // `a_i != b_i`.
    // All the pairs `[a_i, b_i]` are distinct.
    auto num_courses   = ampio::ReadPrim<int>();
    auto prerequisites = ampio::ReadMatrix<int>();
    ampio::Print(Solution{}.findOrder(num_courses, prerequisites));
    return 0;
}
