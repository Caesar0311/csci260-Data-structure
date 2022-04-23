#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

class UnionFind
{
private:
    int *parent; // 该结点的根结点
    int size; // 并查集中结点个数
    
public:
    UnionFind(int); // 初始化
    ~UnionFind(); // 析构
    void setUnion(int, int); // 将两个结点合并
    bool differ(int, int); // 判断两个结点是否同根
    int find(int) const; // 寻找该结点的根结点
};


#endif