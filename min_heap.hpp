#pragma once
#define DEFAULT_MINHEAP_MAX_CAPACITY 1048577
typedef struct Arc {
	int from, to;
	double distance;
} *arc;
class min_heap
{
private:
	arc* m_data;
	int m_N = 0;
	int m_M;
	void swim(int);
	void sink(int);
public:
	min_heap();
	min_heap(int);
	~min_heap();
	int compare(int, int);
	void exchange(int, int);
	void insert(arc);
	arc get_min();
	arc remove_min();
	bool isEmpty();
	int size();
	void print();
};
