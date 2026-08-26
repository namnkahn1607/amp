// 787b. Cheapest Flights Within K Stops

#include <limits>
#include <vector>

#include "ampio/stdin.h"
#include "ampio/stdout.h"

class Solution {
public:
    int findCheapestPrice(
        int n, std::vector<std::vector<int>>& flights, int src, int dst, int k
    ) {
        constexpr int kPosInf = std::numeric_limits<int>::max();

        // The "Domino effect", which makes Bellman-Ford converges faster, does
        // not only occur across passes, but also chains together within a pass.
        std::vector<int> best_cost(n, kPosInf);
        best_cost[src] = 0;

        // Bellman-Ford invariant: After pass i-th, got a SPT rooted at src at
        // which each path has at most i edges.
        for (int pass = 0; pass <= k; ++pass) {  // k + 1 passes, counting dst.
            bool relaxed = false;

            // Snapshot result from previous pass.
            std::vector<int> next_cost = best_cost;

            for (auto& flight : flights) {
                int from = flight[0], to = flight[1], price = flight[2];

                if (best_cost[from] == kPosInf) {
                    // Skip city that is currently unreachable.
                    continue;
                }

                // RULE: read from `best_cost[]`, write to `next_cost[]`.
                // This makes a pass's relaxation not chaining together,
                // therefore increasing the number of stops used for each path.
                int next_price = best_cost[from] + price;
                if (next_price < next_cost[to]) {
                    next_cost[to] = next_price;
                    relaxed       = true;
                }
            }

            if (!relaxed) {
                break;
            }

            // Commit result of current pass.
            best_cost = next_cost;
        }

        return best_cost[dst] == kPosInf ? -1 : best_cost[dst];
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
