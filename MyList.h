/****************************************************************
 * File Name:       MyList.h
 * Author:          cheny1uan
 * Mail:            cheny1uanll@gmail.com
 ****************************************************************/

#include <iostream>
#include <cstdlib>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

/*
 *Struct Name: LinkNode
 *Struct:      链表结点
 *Members:     T data - 数据
 *            LinkNode<T> *link - 指向下一结点的指针
 *Methonds:    LinkNode() - 构造函数
 *            LinkNode(const T &item, LinkNode<T> *ptr = NULL) - 构造函数
 */
template <class T>
struct LinkNode
{
    T data;            // 数据域
    LinkNode<T> *link; // 链指针域

    LinkNode(LinkNode<T> *ptr = NULL)
    {
        link = ptr;
    } // 仅初始化指针成员的构造函数

    LinkNode(const T &item, LinkNode<T> *ptr = NULL)
    {
        data = item;
        link = ptr;
    } // 初始化数据与指针成员的构造函数
};
/*
 *Class Name: List
 *Class:      单链表
 *Members:    LinkNode<T> *first - 链表的头指针
 *Methods:    List() - 构造函数
 *           List(const T &x) - 构造函数
 *           List(List<T> &L) - 复制构造函数
 *           ~List() - 析构函数
 *           void MakeEmpty() - 置空操作
 *           int Length() const - 求表长
 *           LinkNode<T> *getHead() const - 获取附加头节点地址
 *           void setHead(LinkNode<T> *ptr) - 设置附加头节点地址
 *           LinkNode<T> *Search(T x) - 搜索含数据x的地址
 *           LinkNode<T> *Locate(int i) - 搜索第i个元素的地址
 *           T *getData(int i) - 取第i个元素的值
 *           void setData(int i, const T &x) - 用x修改第i个元素的值
 *           bool Insert(int i, const T &x) - 在第i个元素后插入x
 *           bool Remove(int i, T &x) - 删除第i个元素,并用x返回其值
 *           bool IsEmpty() const - 判断是否为空表,空返回true
 *           bool IsFull() const - 判断是否为满表,不满返回false
 *           void Sort(bool option=true) - 排序
 *           void input(T endTag) - 输入
 *           void output() - 输出
 *           List<T> &operator=(List<T> &L) - 赋值运算符重载
 */
template <class T>
class List
{
public:
    List() { first = new LinkNode<T>; }
    List(const T &x) { first = new LinkNode<T>(x); }
    List(List<T> &L);
    ~List() { MakeEmpty(); }
    void MakeEmpty();
    int Length() const;
    LinkNode<T> *getHead() const { return first; }
    void setHead(LinkNode<T> *ptr) { first = ptr; }
    LinkNode<T> *Search(T x);
    LinkNode<T> *Locate(int i);
    T *getData(int i);
    void setData(int i, const T &x);
    bool Insert(int i, const T &x);
    bool Remove(int i, T &x);
    bool IsEmpty() const { return first->link == NULL ? true : false; }
    bool IsFull() const { return false; }
    void Sort(bool option = true);
    void input(T endTag);
    void output();
    List<T> &operator=(List<T> &L);

private:
    LinkNode<T> *first;
};
/*
 *Function Name: List
 *Function:      复制构造函数
 *Input:         List<T> &L - 源链表
 *Return:        void
 */
template <class T>
List<T>::List(List<T> &L)
{
    T value;
    LinkNode<T> *srcptr = L.getHead();              // srcptr指向被复制链表的首节点
    LinkNode<T> *destptr = first = new LinkNode<T>; // destptr指向新链表的首节点
    while (srcptr->link != NULL)
    {
        value = srcptr->link->data;
        destptr->link = new LinkNode<T>(value);
        destptr = destptr->link;
        srcptr = srcptr->link;
    }
    destptr->link = NULL;
}
/*
 *Function Name: MakeEmpty
 *Function:      置空操作
 *Input:         void
 *Return:        void
 */
template <class T>
void List<T>::MakeEmpty()
{
    LinkNode<T> *q;
    while (first->link != NULL) // 当链不空时，删除链中所有结点
    {
        q = first->link;
        first->link = q->link; // 保存被删节点，从链上摘下该结点
        delete q;
    }
}
/*
 *Function Name: Length
 *Function:      求表长
 *Input:         void
 *Return:        int - 表长
 */
template <class T>
int List<T>::Length() const
{
    LinkNode<T> *p = first->link; // p指向首节点
    int count = 0;
    while (p != NULL)
    {
        p = p->link;
        count++;
    }
    return count;
}
/*
 *Function Name: Search
 *Function:      搜索含数据x的地址
 *Input:         T x - 数据
 *Return:        LinkNode<T> * - 数据x的地址
 */
template <class T>
LinkNode<T> *List<T>::Search(T x)
{
    LinkNode<T> *current = first->link; // current指向首节点
    while (current != NULL && current->data != x)
    {
        if (current->data == x)
            return current;
        else
            current = current->link;
    }
    return current;
}
/*
 *Function Name: Locate
 *Function:      搜索第i个元素的地址
 *Input:         int i - 第i个元素
 *Return:        LinkNode<T> * - 第i个元素的地址
 */
template <class T>
LinkNode<T> *List<T>::Locate(int i)
{
    if (i < 0) // i不合理
        return NULL;
    LinkNode<T> *current = first;
    int k = 0;
    while (current != NULL && k < i)
    {
        current = current->link;
        k++;
    }
    return current;
}
/*
 *Function Name: getData
 *Function:      取第i个元素的值
 *Input:         int i - 第i个元素
 *Return:        T * - 第i个元素的值
 */
template <class T>
T *List<T>::getData(int i)
{
    if (i <= 0)
        return NULL;
    LinkNode<T> *current = Locate(i);
    if (current == NULL)
        return NULL;
    else
        return &current->data;
}
/*
 *Function Name: setData
 *Function:      用x修改第i个元素的值
 *Input:         int i - 第i个元素
 *               const T &x - 数据x
 *Return:        void
 */
template <class T>
void List<T>::setData(int i, const T &x)
{
    if (i <= 0)
        return;
    LinkNode<T> *current = Locate(i);
    if (current != NULL)
        current->data = x;
}
/*
 *Function Name: Insert
 *Function:      在第i个元素后插入x
 *Input:         int i - 第i个元素
 *               const T &x - 数据x
 *Return:        bool - 成功返回true，否则返回false
 */
template <class T>
bool List<T>::Insert(int i, const T &x)
{
    LinkNode<T> *current = Locate(i);
    if (current == NULL)
    {
        return false;
    }
    LinkNode<T> *newNode = new LinkNode<T>(x);
    if (newNode == NULL)
    {
        cerr << "存储分配错误！" << endl;
        exit(1);
    }
    newNode->link = current->link;
    current->link = newNode;
    return true;
}
/*
 *Function Name: Remove
 *Function:      删除第i个元素,并用x返回其值
 *Input:         int i - 第i个元素
 *               T &x - 数据x
 *Return:        bool - 成功返回true，否则返回false
 */
template <class T>
bool List<T>::Remove(int i, T &x)
{
    LinkNode<T> *current = Locate(i - 1);
    if (current == NULL || current->link == NULL)
    {
        return false;
    }
    LinkNode<T> *del = current->link;
    current->link = del->link;
    x = del->data;
    delete del;
    return true;
}
/*
 *Function Name: output
 *Function:      输出
 *Input:         void
 *Return:        void
 */
template <class T>
void List<T>::output()
{
    LinkNode<T> *current = first->link;
    while (current != NULL)
    {
        cout << current->data << " ";
        current = current->link;
    }
    cout << endl;
}
/*
 *Function Name: input
 *Function:      输入
 *Input:         T endTag - 输入结束的标志
 *Return:        void
 */
template <class T>
void List<T>::input(T endTag)
{
    // endTag是输入结束的标志
    LinkNode<T> *newNode, *last;
    T value;
    first = new LinkNode<T>; // 创建头结点
    if (first == NULL)
    {
        cerr << "存储分配错误！" << endl;
        exit(1);
    }
    cin >> value;
    last = first;
    while (value != endTag)
    {
        newNode = new LinkNode<T>(value);
        if (newNode == NULL)
        {
            cerr << "存储分配错误！" << endl;
            exit(1);
        }
        last->link = newNode;
        last = newNode;
        cin >> value;
    }
    last->link = NULL; // 该句实际可忽略
}
/*
 *Function Name: Sort
 *Function:      排序
 *Input:         void
 *Return:        void
 */
template <class T>
void List<T>::Sort(bool option)
{
    // option为true表示升序，否则表示降序
    // 使用自底向上的归并排序
    if (option == true)
    {
        LinkNode<T> *p, *q, *r, *s;
        p = first->link;
        first->link = NULL;
        while (p != NULL)
        {
            q = p;
            p = p->link;
            for (r = first, s = first->link; s != NULL && s->data < q->data; r = s, s = s->link)
                ;
            r->link = q;
            q->link = s;
        }
    }
    else
    {
        LinkNode<T> *p, *q, *r, *s;
        p = first->link;
        first->link = NULL;
        while (p != NULL)
        {
            q = p;
            p = p->link;
            for (r = first, s = first->link; s != NULL && s->data > q->data; r = s, s = s->link)
                ;
            r->link = q;
            q->link = s;
        }
    }
}
/*
 *Function Name: operator=
 *Function:      赋值运算符重载
 *Input:         List<T> &L - 源链表
 *Return:        List<T> & - 目标链表
 */
template <class T>
List<T> &List<T>::operator=(List<T> &L)
{
    T value;
    LinkNode<T> *srcptr = L.getHead();              // srcptr指向被复制链表的首节点
    LinkNode<T> *destptr = first = new LinkNode<T>; // destptr指向当前链表的首节点

    while (srcptr->link != NULL)
    {

        value = srcptr->link->data;
        destptr->link = new LinkNode<T>(value);
        destptr = destptr->link;
        srcptr = srcptr->link;
    }
    destptr->link = NULL;
    return *this;
}