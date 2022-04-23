#include <iostream>
#include <stdio.h>
#include "unionfind.hpp"
#include "minheap.hpp"
#include "list.hpp"
#include "graph.hpp"



// Graph* inputGraph()
// {
//     int n = scanf("%d", &n);
//     Graph *g = new Graph(n);
//     int v, u, w;
//     while (scanf("[%d]: %d(%f)", &v, &u, &w) != EOF)
//     {
//         g->setEdge(v, u, w);
//         while (getchar() == ',')
//         {
//             scanf("%d(%f)", &u, &w);
//             g->setEdge(v, u, w);
//         }
//     }
//     g->print();
//     return g;
// }

// 初始化图
Graph* setGraph()
{
    int vnum = 16;
    Graph *g = new Graph(vnum);
    g->setEdge(0, 1, 0.1);
    g->setEdge(0, 4, 3.2);
    g->setEdge(0, 12, 1.5);
    g->setEdge(1, 0, 0.1);
    g->setEdge(1, 2, 0.5);
    g->setEdge(1, 4, 0.2);
    g->setEdge(2, 1, 0.5);
    g->setEdge(2, 3, 0.2);
    g->setEdge(2, 5, 3.2);
    g->setEdge(3, 2, 0.2);
    g->setEdge(3, 5, 0.5);
    g->setEdge(3, 15, 3.2);
    g->setEdge(4, 0, 3.2);
    g->setEdge(4, 1, 0.2);
    g->setEdge(4, 5, 3.2);
    g->setEdge(4, 6, 0.5);
    g->setEdge(5, 2, 3.2);
    g->setEdge(5, 3, 0.5);
    g->setEdge(5, 4, 3.2);
    g->setEdge(5, 7, 3.2);
    g->setEdge(6, 4, 0.5);
    g->setEdge(6, 7, 0.2);
    g->setEdge(6, 8, 0.5);
    g->setEdge(7, 5, 3.2);
    g->setEdge(7, 6, 0.2);
    g->setEdge(7, 9, 0.2);
    g->setEdge(8, 6, 0.5);
    g->setEdge(8, 9, 3.2);
    g->setEdge(8, 10, 0.5);
    g->setEdge(9, 7, 0.2);
    g->setEdge(9, 8, 3.2);
    g->setEdge(9, 11, 0.5);
    g->setEdge(10, 8, 0.5);
    g->setEdge(10, 11, 0.2);
    g->setEdge(10, 12, 0.2);
    g->setEdge(10, 13, 3.2);
    g->setEdge(11, 9, 0.5);
    g->setEdge(11, 10, 0.2);
    g->setEdge(11, 14, 0.2);
    g->setEdge(11, 15, 3.2);
    g->setEdge(12, 0, 1.5);
    g->setEdge(12, 10, 0.2);
    g->setEdge(12, 13, 3.2);
    g->setEdge(13, 10, 3.2);
    g->setEdge(13, 12, 3.2);
    g->setEdge(13, 14, 3.2);
    g->setEdge(14, 11, 0.2);
    g->setEdge(14, 13, 3.2);
    g->setEdge(14, 15, 0.5);
    g->setEdge(15, 3, 3.2);
    g->setEdge(15, 11, 3.2);
    g->setEdge(15, 14, 0.5);
    return g;
}



int main() 
{
    setGraph()->kruskal()->print(); // 生成指定图的最小生成树并打印
    return 0;
}