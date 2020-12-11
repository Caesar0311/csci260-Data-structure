#include<iostream>
#include<iomanip>
#include "list.hpp"

void list::init()
{
	m_cur = m_head = m_tail = new edgeNode(-1);
}
list::list():m_N(0), m_currPos(0)
{
	init();
}
list::list(int v) : m_N(0), m_currPos(0)
{
	init();
	append(v);
}
list::~list()
{
	clear();
	delete m_head;
}

int list::length() { return m_N; }

void list::move_to_start()
{
	m_currPos = 0;
	m_cur = m_head;
}

int list::curr_Pos() { return m_currPos; }

void list::next() 
{
	if (m_cur != m_tail)
	{
		m_currPos++;
		m_cur = m_cur->next;
	}
}

int list::get_value()
{
	if (!m_cur->next)
	{
		std::cerr << "Error: there is no value in the current position." << std::endl;
		exit(1);
	}
	return m_cur->next->vex;
}

double list::get_weight()
{
	if (!m_cur->next)
	{
		std::cerr << "Error: there is no weight in the current position." << std::endl;
		exit(1);
	}
	return m_cur->next->weight;
}

void list::append(int v, double w)
{
	m_tail = m_tail->next = new edgeNode(v, w, nullptr);
	m_N++;
}

void list::insert(int v, double w)
{
	m_cur->next = new edgeNode(v, w, m_cur->next);
	if (m_tail == m_cur)
		m_tail = m_cur->next;
	m_N++;
}

int list::remove()
{
	if (!m_cur->next)
	{
		std::cerr << "Error: no element to remove at current position" << std::endl;
		exit(1);
	}
	edgeNode* temp = m_cur;
	int v = temp->vex;
	if (m_tail == m_cur->next) m_tail = m_cur;
	m_cur->next = m_cur->next->next;
	delete temp;
	m_N--;
	return v;
}

void list::remove_all()
{
	while (m_head != nullptr)
	{
		m_cur = m_head;
		m_head = m_head->next;
		delete m_cur;
	}
}

void list::clear()
{
	remove_all();
	init();
}

bool list::is_empty()
{
	if (m_N == 0) return true;
	return false;
}

int* list::toArray()
{
	int* temp = new int[m_N];
	int i = 0;
	for (move_to_start(); curr_Pos() < length(); next())
	{
		int v = get_value();
		temp[i] = v;
		i++;
	}
	return temp;
}

void list::print()
{
	for (move_to_start(); curr_Pos() < length(); next())
	{
		std::cout << get_value();
		std::cout << "(" << get_weight() << "), ";
	}
}