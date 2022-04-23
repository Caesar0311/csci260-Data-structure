#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "list.hpp"
#include "unionfind.hpp"
#include "minheap.hpp"
#include <assert.h>
#include <stdio.h>

class Edge
{
private:
    int v;
    double w;
public:
    Edge();
    Edge(int, double);
    int vertex() const;
    double weight() const;
};

class Graph
{
private:
    List<Edge> **vertex;
    int numVertex, numEdge;
public:
    Graph(int); //含参构造函数
    ~Graph(); //析构函数
    void init(int); //初始化图
    const int n() const; //点的个数
    const int e() const; //边的条数
    bool isEdge(int, int); //是否有边
    int findEdge(int, int); //若为非负数，则是v2在v1的邻接链表中的位置，若为-1，则说明没找到边
    double weight(int, int); //权值
    void setEdge(int, int, double, bool=false); //设置边，最后一个参数是asc，若为真，则该边将会以升序插入到邻接表中（即遇到第一个编号大于它的点时会停下，并插入到该位置）
    Graph* kruskal(); // kruskal最小生成树算法，输入为图，输出为该图的最小生成树，有个副产物是输出最小生成树的权重总和
    void print(); // 打印图，按照题目的格式
};

#endif