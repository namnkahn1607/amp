// 133b. Clone Graph
// NOTE: The BFS approach is mostly identical to this one: replace
// std::stack<> with std::queue<>.

#include <stack>
#include <unordered_map>

#include "ampio/stdin.h"
#include "ampio/stdout.h"
#include "graph.h"

struct Frame {
    Node* cloned_parent;
    Node* original_child;
};

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        std::stack<Frame> callstack;
        callstack.push({nullptr, node});

        std::unordered_map<int, Node*> table;

        while (!callstack.empty()) {
            auto [cloned_parent, original_child] = callstack.top();
            callstack.pop();

            int val = original_child->val;
            if (table.count(val)) {
                if (cloned_parent != nullptr) {
                    cloned_parent->neighbors.push_back(table[val]);
                }
                continue;
            }

            Node* cloned_child = new Node(val);
            if (cloned_parent != nullptr) {
                cloned_parent->neighbors.push_back(cloned_child);
            }
            table[val] = cloned_child;

            for (auto* neighbor : original_child->neighbors) {
                callstack.push({cloned_child, neighbor});
            }
        }

        return table[node->val];
    }
};

int main() {
    // `0 <= The number of nodes in the graph <= 100`.
    // `1 <= Node.val <= 100`.
    // There are no duplicate edges and no self-loops in the graph.
    auto adj_list = ampio::ReadMatrix<int>();

    const size_t       kNumNodes = adj_list.size();
    std::vector<Node*> nodes(kNumNodes + 1);
    for (size_t i = 1; i <= kNumNodes; ++i) {
        nodes[i] = new Node(i);
    }

    for (size_t i = 0; i < kNumNodes; ++i) {
        int   curr      = i + 1;
        Node* curr_node = nodes[curr];
        for (auto& next : adj_list[i]) {
            curr_node->neighbors.push_back(nodes[next]);
        }
    }

    Node* original = nodes[1];
    ampio::Print(Node::Compare(original, Solution{}.cloneGraph(original)));
    return 0;
}
