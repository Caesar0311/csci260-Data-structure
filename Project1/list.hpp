#ifndef LIST_HPP
#define LIST_HPP

#include <assert.h>

template <typename E>
class Link
{
public:
    E element; // 元素值
    Link *next; // 下一个元素的指针
    Link(const E&, Link *); 
    Link();
};

template <typename E>
Link<E>:: Link(const E& elem_val, Link* next_val)
{
    element = elem_val;
    next = next_val;
}

template <typename E>
Link<E>:: Link()
{
    next = 0;
}

template <typename E>
class List
{
private:
    Link<E> *head, *tail; // 链表的头结点、尾结点，head->next是第一个元素
    int size; // 链表的结点数
    void init(); // 初始化
    void remove_all(); // 移除所有结点
public:
    List(); 
    ~List(); 
    void clear();  // 清空
    void insert(const E&, int); // 在指定位置插入元素
    void append(const E&); // 在末尾插入元素
    E remove(int); // 移除指定位置的元素
    int length() const; // 链表的长度
    const E& getValue(int) const; // 获取指定位置的元素
};

template <typename E>
void List<E>:: init()
{
    head = tail = new Link<E>;
    size = 0;
}

template <typename E>
void List<E>:: remove_all()
{
    Link<E> *temp;
    while(head != 0) // 移除所有结点，直到head为0
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename E>
List<E>:: List()
{
    init();
}

template <typename E>
List<E>:: ~List()
{
    remove_all();
}

template <typename E>
void List<E>:: clear()
{
    remove_all();
    init();
}

template <typename E>
void List<E>:: insert(const E& item, int pos)
{
    assert(pos <= size);

    Link<E> *temp = head;
    while (pos--) // 获取第pos个位置的前一个结点
    {
        temp = temp->next;
    }
    temp->next = new Link<E>(item, temp->next); // 令第pos-1位置的结点的下一个结点指向新的结点
    if(tail == temp) // 如果是最后一个结点，则更新尾结点
    {
        tail = temp->next;
    }
    ++size; // 增加结点数
}

template <typename E>
void List<E>:: append(const E& item)
{
    tail = tail->next = new Link<E>(item, 0); // 在尾结点新增结点
    ++size;
}

template <typename E>
E List<E>:: remove(int pos)
{
    assert(pos < size);

    Link<E> *temp = head;
    while (pos--) // 获取第pos个位置的前一个结点
    {
        temp = temp->next;
    }
    E ret = temp->next->element; // pos位置的元素
    Link<E> *ltmp = temp->next; // 取出pos位置的结点
    if(tail == temp->next) // 如果pos位置是尾结点，则更新尾结点到其前一个结点
    {
        tail = temp;
    }
    temp->next = temp->next->next; // 将pos位置结点变为pos+1位置的结点
    delete ltmp; // 删除该结点
    --size;
    return ret;
}

template <typename E>
int List<E>:: length() const
{
    return size;
}

template <typename E>
const E& List<E>:: getValue(int pos) const
{
    assert(pos < size);

    Link<E> *temp = head;
    while (pos--) // 获取第pos个位置的前一个结点
    {
        temp = temp->next;
    }
    return temp->next->element; // 返回第pos位置的元素
}

#endif
