// 787a. Cheapest Flights Within K Stops

#include <limits>
#include <queue>
#include <vector>

#include "ampio/stdin.h"
#include "ampio/stdout.h"

struct Neighbor {
    int next_city;
    int price;
};

struct State {
    int city;
    int cost;
    int stop_used;

    // Lower cost yields higher priority.
    bool operator<(const State& other) const noexcept {
        return cost > other.cost;
    }
};

class Solution {
public:
    int findCheapestPrice(
        int n, std::vector<std::vector<int>>& flights, int src, int dst, int k
    ) {
        constexpr int kPosInf = std::numeric_limits<int>::max();

        std::vector<std::vector<Neighbor>> adjacency_list(n);
        for (const auto& flight : flights) {
            int from = flight[0], to = flight[1], price = flight[2];
            adjacency_list[from].push_back({to, price});
        }

        // Keeps track of least number of stops to reach each city.
        // NO base case setting for `src` as it would terminate the search loop.
        std::vector<int> best_stops_used(n, kPosInf);

        // 2-dimensional (cost and stops used) state-space container.
        // Priority are decided base on cost.
        std::priority_queue<State> min_pq;
        min_pq.push({src, 0, 0});

        // Dijkstra explores path costs in increasing order of magnitude, so the
        // first time reaching a city yields the most optimal path to that city.
        while (!min_pq.empty()) {
            auto [curr_city, curr_cost, curr_stops_used] = min_pq.top();
            min_pq.pop();

            if (curr_city == dst) {
                // First time reaching dst. Capture result.
                return curr_cost;
            }

            if (curr_stops_used >= best_stops_used[curr_city]) {
                // Already found a cheaper path that uses less stops.
                // This path is suboptimal -> Prune.
                continue;
            }

            best_stops_used[curr_city] = curr_stops_used;
            // Number of stops doesn't count towards src and dst. Use '>'.
            if (curr_stops_used > k) {
                continue;
            }

            for (auto& [next_city, price] : adjacency_list[curr_city]) {
                // NO eager pruning, as it might prune out potential optimal
                // paths that cost more but don't violate number of stops.
                min_pq.push({next_city, curr_cost + price, curr_stops_used + 1}
                );
            }
        }

        return -1;
    }
};

int main() {
    // `2 <= n <= 100`.
    // `0 <= flights.length <= (n * (n - 1) / 2)`.
    // `flights[i].length == 3`.
    // `0 <= from_i, to_i < n`.
    // `from_i != to_i`.
    // `1 <= price_i <= 1e4`.
    // There will not be multiple flights between 2 cities.
    // `0 <= src, dst, k < n`.
    // `src != dst`.
    auto n       = ampio::ReadPrim<int>();
    auto flights = ampio::ReadMatrix<int>();
    auto src     = ampio::ReadPrim<int>();
    auto dst     = ampio::ReadPrim<int>();
    auto k       = ampio::ReadPrim<int>();
    ampio::Print(Solution{}.findCheapestPrice(n, flights, src, dst, k));
    return 0;
}
