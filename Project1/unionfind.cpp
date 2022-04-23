#include "unionfind.hpp"

UnionFind:: UnionFind(int n)
{
    size = n;
    parent = new int[n];
    for (int i = 0; i < n; ++i)
    {
        parent[i] = i;
    }
}

UnionFind:: ~UnionFind()
{
    size = 0;
    delete [] parent;
}

int UnionFind:: find(int curr) const
{
    if (curr != parent[curr])  // 如果当前结点不是根节点（根节点的parent应该是它本身）
    {
        // 那么从当前结点的parent结点继续往上找，并将它的parent的根节点赋值给它的parent，做路径压缩
        parent[curr] = find(parent[curr]); 
    }
    return parent[curr]; // 返回当前结点的parent
    // 路径压缩：当找到根结点时，find会返回根结点的值，并且会随着parent[curr] = find(parent[curr]);这样一个赋值语句，
    // 一级一级地将当前结点直接指向它的根节点。这样，下次find的时候，就不需要一直向上回溯寻找根结点，而是仅需要通过parent[curr]
    // 就能直接找到它的根结点，大大提高了效率。实际上，路径压缩就是把一棵高度>2的树摊开，变成一棵高度为2的树，这棵树除根结点外
    // 所有结点的直接parent都是根结点。
}

void UnionFind:: setUnion(int u, int v)
{
    if (u >= size || v >= size) return;
    parent[find(u)] = find(v); // 合并，即将u结点的parent指向v结点的parent，两结点现在在同一棵树上
    // 这里可以做一个优化，启发式合并（按秩合并），看需求添加
}

bool UnionFind:: differ(int u, int v)
{
    if (u >= size || v >= size) return true;
    return find(u) != find(v);
}