#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include <assert.h>

template <typename E> 
class MinHeap
{
private:
    E *tree; // 二叉堆的树状结构
    int n; // 堆中结点个数
    int maxSize; // 最大结点数
    void down(int); // 下沉
    void up(int); // 上升
    void swap(E&, E&); // 交换两个元素
public:
    MinHeap(E*, int, int); // 初始化
    ~MinHeap(); // 析构
    int size() const; // 堆中结点个数
    bool isLeaf(int) const; // 是否是叶子
    int leftChild(int) const; // 左孩子
    int rightChild(int) const; // 右孩子
    int parent(int) const; // 父结点
    void buildMinHeap(); // 建堆
    void insert(const E&); // 插入结点
    E removeFirst(); // 获取并删除堆顶的元素
    E top(); // 获取堆顶的元素
};

template <typename E> 
void MinHeap<E>:: down(int pos)
{
    while (!isLeaf(pos))
    {
        int t = leftChild(pos), rc = rightChild(pos); 
        if (rc < n && tree[rc] < tree[t]) // 如果存在右孩子，且右孩子的值比左孩子要小
        {
            t = rc; // 那么取右孩子的值，因为要比较子结点中最小的值
        }
        if (tree[pos] < tree[t]) // 如果比子结点中的最小值还要小，说明不能再下沉了
        {
            break;
        }
        swap(tree[pos], tree[t]); // 否则，说明该值不满足最小堆的要求，应该下沉
        pos = t; // 从下沉的位置继续
    }
}

template <typename E> 
void MinHeap<E>:: up(int pos) 
{
    while (pos > 0 && tree[pos] < tree[parent(pos)]) // pos不在堆顶，且pos的值小于其父结点的值，那么将pos位置的值提升
    {
        swap(tree[pos], tree[parent(pos)]);
        pos = parent(pos);
    }
}

template <typename E>
void MinHeap<E>:: swap(E& a, E& b)
{
    E t = b;
    b = a;
    a = t;
}

template <typename E> 
MinHeap<E>:: MinHeap(E* e, int num, int maxNum)
{
    tree = e;
    n = num;
    maxSize = maxNum;
    buildMinHeap(); // 初始化建堆
}

template <typename E> 
MinHeap<E>:: ~MinHeap()
{
    n = maxSize = 0;
    delete [] tree;
}

template <typename E> 
int MinHeap<E>:: size() const
{
    return n;
}

template <typename E> 
bool MinHeap<E>:: isLeaf(int pos) const
{
    return pos >= n/2 && pos < n;
}

template <typename E> 
int MinHeap<E>:: leftChild(int pos) const
{
    return 2*pos + 1;
}

template <typename E> 
int MinHeap<E>:: rightChild(int pos) const
{
    return 2*pos + 2;
}

template <typename E> 
int MinHeap<E>:: parent(int pos) const
{
    return (pos - 1) / 2;
}

template <typename E> 
void MinHeap<E>:: buildMinHeap()
{
    for (int i = n/2-1; i >= 0; --i) // 通过下沉建堆，复杂度为O(n)
    {
        down(i);
    }
}

template <typename E> 
void MinHeap<E>:: insert(const E& elem)
{
    if (n >= maxSize) return;
    tree[n++] = elem; // 在末尾添加元素
    up(n-1); // 并不断提升该结点到正确的位置
}

template <typename E> 
E MinHeap<E>:: removeFirst()
{
    assert(n > 0);

    swap(tree[0], tree[--n]); // 将堆顶元素与最后一个元素交换
    if (n != 0)
    {
        down(0); // 然后将堆顶元素下沉到正确的位置
    }
    return tree[n]; // 返回原先的堆顶元素
}

template <typename E> 
E MinHeap<E>:: top()
{
    return tree[0];
}


#endif