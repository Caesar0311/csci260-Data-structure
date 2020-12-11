#pragma once
#include "list.hpp"
#include "min_heap.hpp"
class graph {
private:
	list** m_vertex;
	int m_V = 0;
	int m_E = 0;
	void set_edge(int, int, double);
public:
	graph();
	graph(int);
	~graph();
	int order();
	int size();
	int degree(int);
	int first(int);
	int next(int, int);
	bool is_edge(int, int);
	void set_adjacency(int, int, double = 0);
	void del_edge(int, int);
	double weight(int, int);
	graph* create_spanning_tree_from_array(int[]);
	graph* prim();
	void visit(int, min_heap*, bool[]);
	void print();
};