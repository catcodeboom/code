#pragma once
#include "unionfindset.hpp"
#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using std::cout;
using std::endl;
using std::priority_queue;
using std::unordered_map;
using std::unordered_set;
using std::vector;
struct Edge;
struct Node {                    // 顶点
    char value = 0;
    int in = 0;                  // 入度
    int out = 0;                 // 出度
    unordered_set<Edge *> edges; // 边集
    unordered_set<Node *> nodes; // 点集
    Node(char val) :
        value(val) {
    }
};
struct Edge {
    int weight = 0; // Ȩֵ
    Node *from = nullptr;
    Node *to = nullptr;
    Edge(int w = 0, Node *f = nullptr, Node *t = nullptr) :
        weight(w), from(f), to(t) {
    }
};
struct Graph {
    unordered_set<Node *> nodes;
    unordered_set<Edge *> edges;
};
class graphAlgorithm {
public:
    static std::list<Node *> dfs(Node *start) { // 深度
        std::list<Node *> ans;
        std::list<Node *> st;
        unordered_set<Node *> hashset;
        st.push_back(start);
        ans.push_back(start);
        hashset.insert(start);
        while (!st.empty()) {
            Node *top = st.back();
            st.pop_back();
            for (Node *node : top->nodes) {
                if (!hashset.count(node)) {
                    ans.push_back(node);
                    hashset.insert(node);
                    st.push_back(top);
                    st.push_back(node);
                    break;
                }
            }
        }
        return ans;
    }
    static std::list<Node *> bfs(Node *start) { // 广度(宽度)
        std::list<Node *> ans;
        std::list<Node *> queue;
        unordered_set<Node *> hashset;
        ans.push_back(start);
        queue.push_back(start);
        hashset.insert(start);
        while (!queue.empty()) {
            Node *front = queue.front();
            queue.pop_front();
            for (Node *node : front->nodes) {
                if (!hashset.count(node)) {
                    ans.push_back(node);
                    hashset.insert(node);
                    queue.push_back(node);
                }
            }
        }
        return ans;
    }
    static std::list<Node *> TopologicalSorting(const Graph &g) { // 拓扑排序
        std::list<Node *> ans;
        unordered_map<Node *, int> inmap;                         // 节点入度
        unordered_set<Node *> zeroset;                            // 记录入度为0的节点
        for (Node *node : g.nodes) {
            if (node->in == 0) {
                zeroset.insert(node);
                ans.push_back(node);
            }
            inmap[node] = node->in;
        }
        while (!zeroset.empty()) {
            unordered_set<Node *> nextzero;
            for (Node *node : zeroset) {
                for (Edge *e : node->edges) {
                    Node *to = e->to;
                    if (!--inmap[to]) {
                        nextzero.insert(to);
                        ans.push_back(to);
                    }
                }
            }
            zeroset = std::move(nextzero);
        }
        return ans;
    }
    static std::list<Edge *> Kruskal(const Graph &g) { // Kruskal算法最小生成树
        auto compedge = [](Edge *left, Edge *right) {
            return left->weight > right->weight;       // 小堆
        };
        std::list<Edge *> ans;
        priority_queue<Edge *, std::vector<Edge *>, decltype(compedge)> heap(g.edges.begin(), g.edges.end(), compedge);
        UnionFindSet<Node *> ufs(g.nodes.begin(), g.nodes.end());
        while (!heap.empty()) {
            auto e = heap.top();
            heap.pop();
            if (!ufs.IsSameSet(e->from, e->to)) {
                ans.push_back(e);
                ufs.Union(e->from, e->to);
            }
        }
        return ans;
    }
    static std::list<Edge *> Prim(const Graph &g) { // Prim算法最小生成树
        auto compedge = [](Edge *left, Edge *right) {
            return left->weight > right->weight;    // 小堆
        };
        Node *start = *g.nodes.begin();             // 任取一点
        std::list<Edge *> ans;
        unordered_set<Node *> nodeset;              // 已经遍历过的点
        nodeset.insert(start);
        int nodesize = g.nodes.size();
        priority_queue<Edge *, std::vector<Edge *>, decltype(compedge)> heap(compedge);
        while (nodeset.size() != nodesize) {
            for (Edge *e : start->edges) {
                heap.push(e);
            }
            while (!heap.empty()) {
                Edge *e = heap.top();
                heap.pop();
                if (!nodeset.count(e->to)) {
                    ans.push_back(e);
                    start = e->to;
                    nodeset.insert(e->to);
                    break;
                }
            }
        }
        return ans;
    }
};
static Node *start = nullptr; // 用于测试def和bds
class Solution {
public:
    static Graph UseVectorGraph(const vector<vector<int>> &matrix) {
        //[0]表示from点,[1]表示to点,[2]表示权值
        Graph ans;
        unordered_map<char, Node *> hashmap; // 记录点
        for (auto &nums : matrix) {
            char from = nums[0], to = nums[1];
            int weight = nums[2];
            if (!hashmap.count(from)) {
                hashmap[from] = new Node(from);
                ans.nodes.insert(hashmap[from]);
            }
            if (!hashmap.count(to)) {
                hashmap[to] = new Node(to);
                ans.nodes.insert(hashmap[to]);
            }
            Edge *e = new Edge(0, hashmap[from], hashmap[to]);
            ans.edges.insert(e);
            hashmap[from]->edges.insert(e);
            hashmap[from]->nodes.insert(hashmap[to]);
            hashmap[from]->out++;
            hashmap[to]->in++;
        }
        return ans;
    }
    static Graph CreateGraph() {
        vector<vector<int>> matrix = {{'B', 'A', 0}, {'B', 'C', 0}, {'B', 'F', 0}, {'A', 'C', 0}, {'C', 'G', 0}, {'F', 'G', 0}};
        Graph g = UseVectorGraph(matrix);
        for (Node *node : g.nodes) {
            if (node->value == 'B') {
                start = node;
                break;
            }
        }
        return g;
    }
    static Graph graphForMinimumSpanningTree() {
        std::vector<std::vector<int>> g = {{'A', 'B', 2}, {'A', 'C', 1}, {'A', 'D', 5}, {'B', 'D', 5}, {'D', 'C', 3}, {'B', 'E', 4}, {'C', 'E', 3}, {'D', 'E', 2}};
        Graph ans;
        unordered_map<int, Node *> nodemap;
        for (auto &data : g) {
            for (int i = 0; i < 2; i++) {
                if (!nodemap.count(data[i])) {
                    nodemap[data[i]] = new Node(data[i]);
                    ans.nodes.insert(nodemap[data[i]]);
                }
            }
            Node *from = nodemap[data[0]], *to = nodemap[data[1]];
            Edge *efrom = new Edge(data[2]);
            Edge *eto = new Edge(data[2]);
            efrom->from = from, efrom->to = to;
            eto->from = to, eto->to = from;
            from->edges.insert(efrom);
            from->nodes.insert(to);
            from->in++, from->out++;
            to->edges.insert(eto);
            to->in++, to->out++;
            to->nodes.insert(from);
            ans.edges.insert(efrom);
            ans.edges.insert(eto);
        }
        return ans;
    }
    static void DisplayNodes(const std::list<Node *> &nodes) {
        for (auto node : nodes) {
            cout << node->value << ' ';
        }
        cout << endl;
        fflush(stdout);
    }
    static void TestKruskalAndPrim() {
        auto ret = Solution::graphForMinimumSpanningTree();
        auto edges = graphAlgorithm::Prim(ret);
        for (auto e : edges) {
            cout << "权值:" << e->weight << endl;
            cout << "from点:" << e->from->value << " || "
                 << "to点" << e->to->value << endl;
            cout << "========================" << endl;
        }
        cout << endl;
        edges = graphAlgorithm::Kruskal(ret);
        for (auto e : edges) {
            cout << "权值:" << e->weight << endl;
            cout << "from点:" << e->from->value << " || "
                 << "to点" << e->to->value << endl;
            cout << "========================" << endl;
        }
        cout << endl;
    }
};