#pragma once
#include "Code07_unionFindSet.h"
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
// 图的相关算法
template <typename T>
struct Edge;
template <typename T>
struct Node {
    int in = 0;
    int out = 0;                   // 出度和入度
    unordered_set<Node<T>*> nodes; // 相连的顶点
    unordered_set<Edge<T>*> edges; // 相连的边
    T val = T();
};
template <class T>
struct Edge {
    Node<T>* from = nullptr;
    Node<T>* to = nullptr;
    int weight = 0; // 权值
    Edge(Node<T>* f = nullptr, Node<T>* t = nullptr, int w = 0) {
        from = f;
        to = t;
        weight = w;
    }
};
template <class T>
struct Graph {
    unordered_map<T, Node<T>*> nodes;
    unordered_set<Edge<T>*> edges;
};
class Code06_graph {
private:
    static Graph<int> ConstructGraph() {
        vector<vector<int>> matrix = {{1, 2, 2}, {1, 3, 5}, {2, 4, 6}, {3, 5, 8}, {2, 5, 10}, {3, 4, 9}, {5, 6, 3}, {4, 6, 4}};
        Graph<int> g;
        for (auto& message : matrix) {
            int from = message[0];
            int to = message[1];
            int weight = message[2];
            Node<int>*fnode = nullptr, *tnode = nullptr;
            if (g.nodes.count(from) == 0) {
                fnode = new Node<int>;
                fnode->val = from;
                g.nodes[from] = fnode;
            } else {
                fnode = g.nodes[from];
            }
            if (g.nodes.count(to) == 0) {
                tnode = new Node<int>;
                tnode->val = to;
                g.nodes[to] = tnode;
            } else {
                tnode = g.nodes[to];
            }
            fnode->out++;
            tnode->in++;
            fnode->nodes.insert(tnode);
            Edge<int>* e = new Edge<int>(fnode, tnode, weight);
            g.edges.insert(e);
            fnode->edges.insert(e);
        }
        return g;
    }
    static void GraphDfs(Node<int>* start) {
        unordered_set<Node<int>*> hashSet; // 记录已经遍历过的点
        stack<Node<int>*> Stack;
        cout << start->val << ' ';
        Stack.push(start);
        hashSet.insert(start);
        while (!Stack.empty()) {
            // cout << "Stack size=" << Stack.size() << endl;
            Node<int>* node = Stack.top();
            Stack.pop();
            for (auto n : node->nodes) {
                if (hashSet.count(n) == 0) {
                    cout << n->val << ' ';
                    hashSet.insert(n);
                    Stack.push(node);
                    Stack.push(n);
                    break;
                }
            }
        }
        cout << endl;
    }
    static void GraphBfs(Node<int>* start) {
        queue<Node<int>*> Queue;
        unordered_set<Node<int>*> hashSet;
        hashSet.insert(start);
        Queue.push(start);
        while (!Queue.empty()) {
            auto node = Queue.front();
            Queue.pop();
            cout << node->val << ' ';
            for (auto n : node->nodes) {
                if (hashSet.count(n) == 0) {
                    hashSet.insert(n);
                    Queue.push(n);
                }
            }
        }
        cout << endl;
    }
    static void TopologicalSorting(const Graph<int>& g) {
        unordered_map<Node<int>*, int> hashMap; // 存储点和它的入度
        unordered_set<Node<int>*> zeroSet;      // 存储入度为0的点
        for (auto [val, node] : g.nodes) {
            if (node->in == 0) {
                cout << val << ' ';
                zeroSet.insert(node);
            } else {
                hashMap[node] = node->in;
            }
        }
        while (!zeroSet.empty()) {
            unordered_set<Node<int>*> nextZeroSet;
            for (auto node : zeroSet) {
                for (auto n : node->nodes) {
                    if (!--n->in) {
                        cout << n->val << ' ';
                        nextZeroSet.insert(n);
                    }
                }
            }
            zeroSet = move(nextZeroSet);
        }
    }
    static vector<Edge<int>*> Kruskal(const Graph<int>& g) {
        auto EdgeComp = [](const Edge<int>* left, const Edge<int>* right) {
            return left->weight > right->weight;
        };
        //-----------------------------------------------------
        // Kruskal算法求最小生成树,需要使用并查集
        vector<Edge<int>*> ans;
        vector<Node<int>*> nodes;
        for (auto [val, node] : g.nodes) {
            nodes.push_back(node);
        }
        priority_queue<Edge<int>*, vector<Edge<int>*>, decltype(EdgeComp)> heap(g.edges.begin(), g.edges.end(), EdgeComp);
        UnionFindSet<Node<int>*> ufs(nodes.begin(), nodes.end());
        while (!heap.empty()) {
            auto edge = heap.top();
            heap.pop();
            if (!ufs.IsSameSet(edge->from, edge->to)) {
                ans.push_back(edge);
                ufs.Union(edge->from, edge->to);
            }
        }
        return ans;
    }

public:
    static void Run() {
        auto VerifyKruskal = [](vector<Edge<int>*>& ans) {
            cout << "通过Kruskal算法选出来的边为:" << endl;
            for (auto edge : ans) {
                cout << edge->from->val << "->" << edge->to->val << "(权值:" << edge->weight << ")" << endl;
            }
        };
        //--------------------------------------------------
        Graph<int> g = ConstructGraph();
        // cout << "深度优先遍历的结果为:";
        // GraphDfs(g.nodes.find(1)->second);
        // cout << endl;

        // cout << "宽度优先遍历的结果为:";
        // GraphBfs(g.nodes.find(1)->second);
        // cout << endl;

        // cout << "拓扑排序的结果为:";
        // TopologicalSorting(g);
        // cout << endl;

        auto kru = Kruskal(g);
        VerifyKruskal(kru);
    }
};