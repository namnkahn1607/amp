// 133a. Clone Graph

#include <cassert>
#include <unordered_map>
#include <vector>

#include "ampio/stdin.h"
#include "ampio/stdout.h"
#include "graph.h"

std::unordered_map<int, Node*> table;

Node* Clone(const Node* node) noexcept {
    int val = node->val;

    if (table.count(val)) {
        return table[val];
    }

    Node* clone = new Node(val);
    table[val]  = clone;

    for (auto* neighbor : node->neighbors) {
        clone->neighbors.push_back(Clone(neighbor));
    }

    return clone;
}

Node* cloneGraph(Node* node) {
    return (node == nullptr) ? nullptr : Clone(node);
}

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
    ampio::Print(Node::Compare(original, cloneGraph(original)));
    return 0;
}
