#include<iostream>
#include<iomanip>
#include "graph.hpp"
using namespace std; 
graph::graph():m_V(0),m_E(0)
{
	m_vertex = nullptr;
}
graph::graph(int N) :m_V(N), m_E(0)
{
	m_vertex = new list * [m_V];
	for (int i = 0; i < m_V; i++)
	{
		m_vertex[i] = new list();
	}
}
graph::~graph()
{
	for (int i = 0; i < m_V; i++)
		delete m_vertex[i];
	delete[] m_vertex;
}

int graph::order()
{
	return m_V;
}
int graph::size()
{
	return m_E;
}

int graph::degree(int v)
{
	return m_vertex[v]->length();
}

int graph::first(int v)
{
	//std::cout << "first: before resetting list and returning first vertex in edge list." << std::endl;
	if (m_vertex[v]->length() == 0) return m_V; // return the number of vertices
	m_vertex[v]->move_to_start();
	return m_vertex[v]->get_value();
}

int graph::next(int u,int v)
{
	if (is_edge(u, v))
	{
		if (m_vertex[u]->curr_Pos() + 1 < m_vertex[u]->length())
		{
			m_vertex[u]->next();
			return m_vertex[u]->get_value();
		}
	}
	return m_V;
}

bool graph::is_edge(int u, int v)
{
	//std::cout << "is_edge: checking edge (" << u << ", " << v << ")." << std::endl;
	for (
		m_vertex[u]->move_to_start();
		m_vertex[u]->curr_Pos() < m_vertex[u]->length();
		m_vertex[u]->next()
		) {
		int w = m_vertex[u]->get_value();
		if (v == w) return true;
	}
	return false;
}

void graph::set_adjacency(int u, int v, double weight)
{
	//std::cout << "set_adjacency (" << u << ", " << v << ")." << std::endl;
	// simple graphs do not have loops (self-adjacencies)
	if (u == v) return;

	// already adjacent
	if (is_edge(u, v) && is_edge(v, u)) {
		// simple graph, so do arcs in both directions
		m_vertex[u]->remove();
		m_vertex[v]->remove();
		set_edge(u, v, weight);
		set_edge(u, u, weight);
	}
	// adjacent in one direction (just to double-check arcs go both ways for each edge added)
	else if (is_edge(u, v)) set_edge(v, u, weight);
	else if (is_edge(v, u)) set_edge(u, v, weight);
	// create a new adjacency
	else
	{
		set_edge(u, v, weight);
		set_edge(v, u, weight);
		m_E++;
	}
}

void graph::set_edge(int u, int v, double weight)
{
	//std::cout << "set_edge (" << u << ", " << v << ")." << std::endl;

	for (
		m_vertex[u]->move_to_start();
		m_vertex[u]->curr_Pos() < m_vertex[u]->length();
		m_vertex[u]->next()
		) {
		int w = m_vertex[u]->get_value();
		if (w > v) break;
	}
	m_vertex[u]->insert(v, weight);
}

void graph::del_edge(int u, int v)
{
	//std::cout << "del_edge (" << u << ", " << v << ")." << std::endl;
	if (u == v) return;

	if (is_edge(u, v)) m_vertex[u]->remove();
	if (is_edge(v, u)) m_vertex[v]->remove();
	m_E--;
}

double graph::weight(int u, int v)
{
	// implemented to have list private nodes "edge"
	if (is_edge(u, v)) // iterates in the list to position with vertex value v
		return m_vertex[u]->get_weight();
	return 0;
}

graph* graph::create_spanning_tree_from_array(int parents[])
{
	//std::cout << "create_spanning_tree_from_array." << std::endl;
	graph* T = new graph(m_V);

	// set_adjacency ensures we do not create a loop at the root
	for (int i = 0; i < m_V; i++)
		T->set_adjacency(i, parents[i], weight(i, parents[i]));

	return T;
}
graph* graph::prim()
{
	bool* visited = new bool[m_V];
	memset(visited, false, m_V);
	int* parents = new int[m_V];
	memset(parents, 0, m_V);
	min_heap* arc_heap = new min_heap();
	int start = 0;
	visited[start] = true;
	visit(start, arc_heap, visited);
	while(!arc_heap->isEmpty())
	{
		arc minArc = arc_heap->get_min();
		while (minArc!=nullptr&&visited[minArc->from] && visited[minArc->to])
		{
			arc_heap->remove_min();
			minArc = arc_heap->get_min();
			continue;
		}
		if (minArc != nullptr)
		{
			visited[minArc->from] ? parents[minArc->to] = minArc->from : parents[minArc->from] = minArc->to;
			start = visited[minArc->from] ? minArc->to : minArc->from;
			arc_heap->remove_min();
			visit(start, arc_heap, visited);
		}
	}
	return create_spanning_tree_from_array(parents);
}
void graph::visit(int u, min_heap* arc_heap, bool visited[])
{
	visited[u] = true;
	list* edgeList = m_vertex[u];
	for (edgeList->move_to_start(); edgeList->curr_Pos() < edgeList->length(); edgeList->next())
	{
		int v = edgeList->get_value(); 
		if (!visited[v])
		{
			arc edgeArc= (struct Arc*)malloc(sizeof(struct Arc));
			if (u < v)
			{
				edgeArc->from = u;
				edgeArc->to = v;
				edgeArc->distance = edgeList->get_weight();
				arc_heap->insert(edgeArc);
			}
				
			if (u > v)
			{
				edgeArc->from = v;
				edgeArc->to = u;
				edgeArc->distance = edgeList->get_weight();
				arc_heap->insert(edgeArc);
			}
		}
	}
}
void graph::print()
{
	for (int i = 0; i < m_V; i++)
	{
		std::cout << "[" << i << "]: ";
		m_vertex[i]->print();
		std::cout << std::endl;
	}
}

