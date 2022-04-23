#include "graph.hpp"

Edge:: Edge() { v = w = -1; }

Edge:: Edge(int v, double w): v(v), w(w) {}

int Edge:: vertex() const
{
    return v;
}

double Edge:: weight() const
{
    return w;
}

Graph:: Graph(int numVert)
{
    init(numVert); // 初始化有numVert个点的图所需要的资源
}

Graph:: ~Graph()
{
    for(int i = 0; i < numVertex; ++i)
        delete [] vertex[i];
    delete [] vertex;
}

void Graph:: init(int n)
{
    numVertex = n;
    numEdge = 0;
    vertex = (List<Edge>**) new List<Edge>*[numVertex];
    for (int i = 0; i < numVertex; ++i)
    {
        vertex[i] = new List<Edge>();
    }
}

const int Graph:: n() const
{
    return numVertex;
}

const int Graph:: e() const
{
    return numEdge;
}

bool Graph:: isEdge(int v1, int v2)
{
    if(v1 > numVertex || v2 > numVertex) return false;
    for (int i = 0; i < vertex[v1]->length(); ++i) // 遍历v1的邻接点，看看有没有v2
    {
        if (vertex[v1]->getValue(i).vertex() == v2)
        {
            return true;
        }
    }
    return false; // 如果都没有，就返回false
}

int Graph:: findEdge(int v1, int v2)
{
    if(v1 > numVertex || v2 > numVertex) return false;
    for (int i = 0; i < vertex[v1]->length(); ++i)
    {
        if (vertex[v1]->getValue(i).vertex() == v2)
        {
            return i; // 返回v2在v1的邻接表中的位置
        }
    }
    return -1;
}

double Graph:: weight(int v1, int v2)
{
    if(v1 > numVertex || v2 > numVertex) return -1;

    for (int i = 0; i < vertex[v1]->length(); ++i)
    {
        if (vertex[v1]->getValue(i).vertex() == v2)
        {
            return vertex[v1]->getValue(i).weight();
        }
    }
    return -1; // 没有该边都返回-1
}

void Graph:: setEdge(int v1, int v2, double w, bool asc)
{
    if(v1 > numVertex || v2 > numVertex || w < 0) return;

    int pos = findEdge(v1, v2); // 先找到v2在v1的位置
    if (pos != -1) // 如果v1 v2是邻居（pos非-1，表明v2在v1的邻接表中）
    {
        vertex[v1]->remove(pos); // 那么就移除旧的边
    }     

    if (!asc) // 正常情况，即直接插入到邻接表末尾
    {
        vertex[v1]->append(Edge(v2, w)); // 增加新边
    }
    else //有序
    {
        int i;
        for (i = 0; i < vertex[v1]->length(); ++i)
        {
            if (vertex[v1]->getValue(i).vertex() > v2)
            {
                break;
            }
        }
        vertex[v1]->insert(Edge(v2, w), i);
    }
    ++numEdge;
}

Graph* Graph:: kruskal() 
{
    // kruskal算法需要用到的结构，(v1, v2, w)，v1和v2是一条边的两个顶点，w是这条边的权重
    class KruskalElement
    {
    public:
        int from, to;
        double weight;
        KruskalElement() {}
        KruskalElement(int from, int to, double weight): from(from), to(to), weight(weight) {}
        bool operator < (const KruskalElement& ke) const // 重载<，按照权重从小到大排
        {
            return weight < ke.weight;
        }
    };
    
    // 将图转化为等价的KruskalElement数组
    KruskalElement *ke = new KruskalElement[numEdge];
    int keNum = 0;
    for (int i = 0; i < numVertex; ++i) // 遍历每个顶点
    {
        int len = vertex[i]->length(); // 获取第i个顶点的邻接点的个数
        for (int j = 0; j < len; ++j)
        {
            Edge edge = vertex[i]->getValue(j); // 获取第i个顶点的第j个邻边
            // printf("from=%d to=%d w=%f\n", i, edge.vertex(), edge.weight());
            // 将该边加入ke数组
            ke[keNum].from = i;
            ke[keNum].to = edge.vertex();
            ke[keNum++].weight = edge.weight();
        }
    }
    UnionFind ufs(numVertex); // 并查集
    MinHeap<KruskalElement> heap(ke, numEdge, numEdge); // 最小堆
    Graph* mst = new Graph(numVertex); // 最小生成树
    double mstValue = 0.0; // mst的值
    int numMST = numVertex - 1; // 最小生成树只有n-1条边
    while (numMST > 0) // 还有要找的边
    {
        KruskalElement temp = heap.removeFirst(); // 取出最小的边
        int u = temp.from, v = temp.to;
        if (ufs.differ(u, v)) // ufs.find(u) != ufs.find(v) 根不同
        {
            // printf("u=%d v=%d w=%f\n", u, v, temp.weight);
            ufs.setUnion(u, v); // 设为同根
            mstValue += temp.weight; // mst加上这条边
            mst->setEdge(u, v, temp.weight, true); // 加入mst的边集中
            mst->setEdge(v, u, temp.weight, true); // 并按升序加入，方便打印格式化
            numMST--; // 找到了一条边
        }
    }
    printf("MST VALUE = %.1f\n", mstValue); // 输出最小生成树的权重总和
    return mst;
}

void Graph:: print()
{
    for (int i = 0; i < numVertex; ++i)
    {
        printf("[%2d]: ", i);
        for (int j = 0; j < vertex[i]->length(); ++j)
        {
            printf("%d(%.1f), ", vertex[i]->getValue(j).vertex(), vertex[i]->getValue(j).weight());
        }
        printf("\n");
    }
}