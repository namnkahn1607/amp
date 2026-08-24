// 207a. Course Schedule

#include <queue>
#include <vector>

#include "ampio/stdin.h"
#include "ampio/stdout.h"

bool canFinish(int num_courses, std::vector<std::vector<int>>& prerequisites) {
    std::vector<std::vector<int>> adjacency_list(num_courses);

    std::vector<int> in_degree(num_courses, 0);
    for (auto& preq : prerequisites) {
        int a = preq[0], b = preq[1];
        ++in_degree[a];
        adjacency_list[b].push_back(a);
    }

    std::queue<int> qu;
    for (int i = 0; i < num_courses; ++i) {
        if (in_degree[i] == 0) {
            qu.push(i);
        }
    }

    int finished = 0;
    while (!qu.empty()) {
        auto course = qu.front();
        qu.pop();
        ++finished;

        for (auto& next : adjacency_list[course]) {
            in_degree[next] -= 1;
            if (in_degree[next] == 0) {
                qu.push(next);
            }
        }
    }

    return finished == num_courses;
}

int main() {
    // `1 <= num_courses <= 2000`.
    // `0 <= prerequisites.length <= 5000`.
    // `prerequisites[i].length == 2`.
    // `0 <= a_i, b_i < num_courses`.
    // All the pairs `prerequisites[i]` are unique.
    auto num_courses   = ampio::ReadPrim<int>();
    auto prerequisites = ampio::ReadMatrix<int>();
    ampio::Print(canFinish(num_courses, prerequisites));
    return 0;
}
