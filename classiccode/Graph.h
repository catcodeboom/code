#pragma once
#include"unionfindset.hpp"
#include<unordered_map>
#include<iostream>
#include<unordered_set>
#include<list>
#include<queue>
using std::unordered_map;
using std::unordered_set;
using std::priority_queue;
using std::cout;
using std::endl;
struct Edge;
struct Node {//顶点
	char value = 0;
	int in = 0;//入度
	int out = 0;//出度
	unordered_set<Edge*> edges;//从该顶点出发的边
	unordered_set<Node*> nodes;//该顶点与哪些顶点直接相连
	Node(char val) :value(val) {}
};
struct Edge {
	int weight = 0;//权值
	Node* from = nullptr;
	Node* to = nullptr;
	Edge(int w = 0) :weight(w) {}
};
struct Graph {
	unordered_set<Node*> nodes;
	unordered_set<Edge*> edges;
	~Graph() {
		//对new出来的顶点和边进行delete
		for (Node* n : nodes) {
			delete n;
		}
		for (Edge* e : edges) {
			delete e;
		}
		//最后调用unordered_set的析构函数
	}
};
class graphAlgorithm {
public:
	static std::list<Node*> dfs(Node* start) {//深度优先遍历
		std::list<Node*> ans;
		std::list<Node*> st;//栈
		unordered_set<Node*> hashset;
		st.push_back(start);
		ans.push_back(start);
		hashset.insert(start);
		while (!st.empty()) {
			Node* top = st.back();
			st.pop_back();
			for (Node* node : top->nodes) {
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
	static std::list<Node*> bfs(Node* start) {//广度优先(宽度优先遍历)
		std::list<Node*> ans;
		std::list<Node*> queue;//队列
		unordered_set<Node*> hashset;
		ans.push_back(start);
		queue.push_back(start);
		hashset.insert(start);
		while (!queue.empty()) {
			Node* front = queue.front();
			queue.pop_front();
			for (Node* node : front->nodes) {
				if (!hashset.count(node)) {
					ans.push_back(node);
					hashset.insert(node);
					queue.push_back(node);
				}
			}
		}
		return ans;
	}
	static std::list<Node*> TopologicalSorting(const Graph& g) {//拓扑排序
		std::list<Node*> ans;
		unordered_map<Node*, int> inmap;//记录节点的入度
		unordered_set<Node*> zeroset;//记录当前一轮入度为0的点
		for (Node* node : g.nodes) {
			if (node->in == 0) {
				zeroset.insert(node);
				ans.push_back(node);
			}
			inmap[node] = node->in;
		}
		while (!zeroset.empty()) {//表示节点都已经擦除
			unordered_set<Node*> nextzero;//记录新一轮入度为0的节点
			for (Node* node : zeroset) {
				for (Edge* e : node->edges) {
					Node* to = e->to;
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
	static std::list<Edge*> Kruskal(const Graph& g) {//Kruskal算法生成最小生成树
		auto compedge = [](Edge* left, Edge* right) {
			return left->weight > right->weight;//小堆
		};
		std::list<Edge*> ans;
		priority_queue<Edge*, std::vector<Edge*>, decltype(compedge)> heap(g.edges.begin(), g.edges.end(), compedge);
		UnionFindSet<Node*> ufs(g.nodes.begin(), g.nodes.end());
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
	static std::list<Edge*> Prim(const Graph& g) {//Prim算法生成最小生成树
		auto compedge = [](Edge* left, Edge* right) {
			return left->weight > right->weight;//小堆
		};
		Node* start = *g.nodes.begin();//任选一个起点
		std::list<Edge*> ans;
		unordered_set<Node*> nodeset;//记录已经选过的点
		nodeset.insert(start);
		int nodesize = g.nodes.size();
		priority_queue<Edge*, std::vector<Edge*>, decltype(compedge)> heap(compedge);
		while (nodeset.size() != nodesize) {
			for (Edge* e : start->edges) {
				heap.push(e);
			}
			while (!heap.empty()) {
				Edge* e = heap.top();
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
static Node* start = nullptr;//用于测试
class Solution {
public:
	//生成的图见graph.png
	static Graph CreateGraph() {
		Graph ans;
		Node* A = new Node('A');
		Node* B = new Node('B');
		Node* C = new Node('C');
		Node* F = new Node('F');
		Node* G = new Node('G');
		start = B;
		ans.nodes.insert(A);
		ans.nodes.insert(B);
		ans.nodes.insert(C);
		ans.nodes.insert(F);
		ans.nodes.insert(G);
		Edge* ba = new Edge;
		ba->from = B;
		ba->to = A;
		ans.edges.insert(ba);
		Edge* bc = new Edge;
		bc->from = B;
		bc->to = C;
		ans.edges.insert(bc);
		Edge* bf = new Edge;
		bf->from = B;
		bf->to = F;
		ans.edges.insert(bf);
		Edge* ac = new Edge;
		ac->from = A;
		ac->to = C;
		ans.edges.insert(ac);
		Edge* cg = new Edge;
		cg->from = C;
		cg->to = G;
		ans.edges.insert(cg);
		Edge* fg = new Edge;
		fg->from = F;
		fg->to = G;
		ans.edges.insert(fg);
		B->edges.insert(ba);
		B->edges.insert(bc);
		B->edges.insert(bf);
		A->edges.insert(ac);
		F->edges.insert(fg);
		C->edges.insert(cg);
		B->nodes.insert(A);
		B->nodes.insert(C);
		B->nodes.insert(F);
		A->nodes.insert(C);
		F->nodes.insert(G);
		C->nodes.insert(G);
		B->out = 3;
		A->in = 1;
		A->out = 1;
		C->in = 2;
		C->out = 1;
		F->in = 1;
		F->out = 1;
		G->in = 2;
		return ans;
	}
	static Graph graphForMinimumSpanningTree() {
		std::vector<std::vector<int>> g = { {'A','B',2},{'A','C',1},{'A','D',5},{'B','D',5},{'D','C',3},{'B','E',4},{'C','E',3},{'D','E',2} };
		Graph ans;
		unordered_map<int, Node*> nodemap;
		for (auto& data : g) {
			for (int i = 0; i < 2; i++) {
				if (!nodemap.count(data[i])) {
					nodemap[data[i]] = new Node(data[i]);
					ans.nodes.insert(nodemap[data[i]]);
				}
			}
			Node* from = nodemap[data[0]], * to = nodemap[data[1]];
			Edge* efrom = new Edge(data[2]);
			Edge* eto = new Edge(data[2]);
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
	static void DisplayNodes(const std::list<Node*>& nodes) {
		for (auto node : nodes) {
			cout << node->value << ' ';
		}
		cout << endl;
	}
	static void TestKruskalAndPrim() {
		auto ret = Solution::graphForMinimumSpanningTree();
		auto edges = graphAlgorithm::Prim(ret);
		for (auto e : edges) {
			cout << "权值:" << e->weight << endl;
			cout << "from点:" << e->from->value << " || " << "to点" << e->to->value << endl;
			cout << "========================" << endl;
		}
		cout << endl;

		edges = graphAlgorithm::Kruskal(ret);
		for (auto e : edges) {
			cout << "权值:" << e->weight << endl;
			cout << "from点:" << e->from->value << " || " << "to点" << e->to->value << endl;
			cout << "========================" << endl;
		}
		cout << endl;
	}
};