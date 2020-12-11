#pragma once
struct edgeNode {
	int vex;
	double weight;
	edgeNode* next;
	edgeNode(int v):edgeNode(v,0,nullptr)
	{}
	edgeNode(int v,double w,edgeNode* next):vex(v),weight(w),next(next)
	{}
};

class list {
private:
	edgeNode* m_head;
	edgeNode* m_tail;
	edgeNode* m_cur;
	int m_N;
	int m_currPos;
	void init();
	void remove_all();
public:
	list();
	list(int);
	~list();

	int length();
	void move_to_start();
	int curr_Pos();
	void next();

	void append(int, double = 0);
	void insert(int, double = 0);
	int remove();

	void clear();
	int get_value();
	double get_weight();
	bool is_empty();

	int* toArray();

	void print();
};
