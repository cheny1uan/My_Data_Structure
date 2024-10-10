/****************************************************************
 * File Name:       MyQueue.h
 * Author:          cheny1uan
 * Mail:            cheny1uanll@gmail.com
 ****************************************************************/
#include <iostream>
using namespace std;
const int MaxSize = 100;
/*
 * Class Name:       MyQueue
 * Class:            队列的基类
 * Members:          T *elements - 存放队列元素的数组
 *                   int front - 队头指针
 *                   int rear - 队尾指针
 *                   int maxSize - 队列最大存储容量
 * Methods:          MyQueue() - 构造函数
 *                   virtual bool enQueue(const T &x) = 0 - 入队
 *                   virtual bool deQueue(T &x) = 0 - 出队
 *                   virtual bool getFront(T &x) const = 0 - 取队头元素
 *                   virtual bool isEmpty() const = 0 - 判断队列是否为空
 *                   virtual bool isFull() const = 0 - 判断队列是否已满
 *                   virtual int getSize() const = 0 - 求队列长度
 */
template <typename T>
class MyQueue
{
public:
    MyQueue() {};
    virtual bool enQueue(const T &x) = 0;
    virtual bool deQueue(T &x) = 0;
    virtual bool getFront(T &x) const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual int getSize() const = 0;
};
/*
 * Class Name:       SeqQueue
 * Class:            顺序队列(基于数组的存储实现)
 * Members:          T *elements - 存放队列元素的数组
 *                   int front - 队头指针
 *                   int rear - 队尾指针
 *                   int maxSize - 队列最大存储容量
 * Methods:          SeqQueue(int sz = MaxSize) - 构造函数
 *                   ~SeqQueue() - 析构函数
 *                   bool enQueue(const T &x) - 入队
 *                   bool deQueue(T &x) - 出队
 *                   bool getFront(T &x) const - 取队头元素
 *                   bool isEmpty() const - 判断队列是否为空
 *                   bool isFull() const - 判断队列是否已满
 *                   int getSize() const - 求队列长度
 *                   void makeEmpty() - 清空队列
 */
template <class T>
class SeqQueue : public MyQueue<T>
{
public:
    SeqQueue(int sz = MaxSize);
    ~SeqQueue() { delete[] elements; }
    bool enQueue(const T &x);
    bool deQueue(T &x);
    bool getFront(T &x) const;
    bool isEmpty() const { return front == rear; }
    bool isFull() const { return (rear + 1) % maxSize == front; }
    int getSize() const { return (rear - front + maxSize) % maxSize; }
    void makeEmpty() { front = rear = 0; }

private:
    T *elements;     // 存放队列元素的数组
    int front, rear; // 队头指针和队尾指针
    int maxSize;     // 队列最大存储容量
};
/*
 *Function Name:    SeqQueue
 *Function:         构造函数
 *Input Parameters: int sz - 队列最大存储容量
 *return Value:     void
 */
template <class T>
SeqQueue<T>::SeqQueue(int sz) : front(0), rear(0), maxSize(sz)
{
    elements = new T[maxSize];
    if (elements == NULL)
    {
        cerr << "存储分配错误!" << endl;
        exit(1);
    }
}
/*
 * Function Name:    enQueue
 * Function:         入队
 * Input Parameters: const T &x - 数据
 * Return Value:     bool - 成功返回true，否则返回false
 */

template <class T>
bool SeqQueue<T>::enQueue(const T &x)
{
    if (isFull())
    {
        cerr << "队列已满!" << endl;
        return false;
    }
    elements[rear] = x;
    rear = (rear + 1) % maxSize;
    return true;
}
/*
 * Function Name:    deQueue
 * Function:         出队
 * Input Parameters: T &x - 出队的元素
 * Return Value:     bool - 成功返回true，否则返回false
 */
template <class T>
bool SeqQueue<T>::deQueue(T &x)
{
    if (isEmpty())
        return false;
    x = elements[front];
    front = (front + 1) % maxSize;
    return true;
}
/*
 * Function Name:    getFront
 * Function:         取队头元素
 * Input Parameters: T &x - 队头元素
 * Return Value:     bool - 成功返回true，否则返回false
 */
template <class T>
bool SeqQueue<T>::getFront(T &x) const
{
    if (isEmpty())
        return false;
    x = elements[front];
    return true;
}
/*
 * Struct Name:      LinkNode
 * Struct:           链队列结点
 * Members:          T data - 数据
 *                   LinkNode<T> *link - 指向下一个结点的指针
 * Methods:          LinkNode(LinkNode<T> *ptr = NULL) - 构造函数
 *                   LinkNode(const T &item, LinkNode<T> *ptr = NULL) - 构造函数
 */
template <class T>
struct LinkNode
{
    T data;
    LinkNode<T> *link;
    LinkNode(LinkNode<T> *ptr = NULL) { link = ptr; }
    LinkNode(const T &item, LinkNode<T> *ptr = NULL)
    {
        data = item;
        link = ptr;
    }
};
/*
 * Class Name:       LinkQueue
 * Class:            链队列(基于链表的存储实现)
 * Members:          LinkNode<T> *front, *rear - 队头指针和队尾指针
 * Methods:          LinkQueue() - 构造函数
 *                   ~LinkQueue() - 析构函数
 *                   bool enQueue(const T &x) - 入队
 *                   bool deQueue(T &x) - 出队
 *                   bool getFront(T &x) const - 取队头元素
 *                   bool isEmpty() const - 判断队列是否为空
 *                   bool isFull() const - 判断队列是否已满
 *                   int getSize() const - 求队列长度
 *                   void makeEmpty() - 清空队列
 */
template <class T>
class LinkQueue : public MyQueue<T>
{
public:
    LinkQueue() : rear(NULL), front(NULL) {}
    ~LinkQueue() { makeEmpty(); }
    bool enQueue(const T &x);
    bool deQueue(T &x);
    bool getFront(T &x) const;
    bool isEmpty() const { return front == NULL; }
    bool isFull() const { return false; }
    int getSize() const;
    void makeEmpty();

private:
    LinkNode<T> *front, *rear;
};
/*
 * Function Name:    makeEmpty
 * Function:         清空队列
 * Input Parameters: 无
 * Return Value:     void
 */
template <class T>
void LinkQueue<T>::makeEmpty()
{
    LinkNode<T> *p;
    while (front != NULL)
    {
        p = front;
        front = front->link;
        delete p;
    }
}
/*
 * Function Name:    enQueue
 * Function:         入队
 * Input Parameters: const T &x - 数据
 * Return Value:     bool - 成功返回true，否则返回false
 */
template <class T>
bool LinkQueue<T>::enQueue(const T &x)
{
    if (front == NULL)
    {
        front = rear = new LinkNode<T>(x);
        if (front == NULL)
        {
            cerr << "存储分配错误!" << endl;
            exit(1);
        }
        return true;
    }
    rear->link = new LinkNode<T>(x);
    if (rear->link == NULL)
    {
        cerr << "存储分配错误!" << endl;
        exit(1);
    }
    rear = rear->link;
    return true;
}
/*
 * Function Name:    deQueue
 * Function:         出队
 * Input Parameters: T &x - 出队的元素
 * Return Value:     bool - 成功返回true，否则返回false
 */
template <class T>
bool LinkQueue<T>::deQueue(T &x)
{
    if (isEmpty())
        return false;
    LinkNode<T> *p = front;
    x = front->data;
    front = front->link;
    delete p;
    return true;
}
/*
 * Function Name:    getFront
 * Function:         取队头元素
 * Input Parameters: T &x - 队头元素
 * Return Value:     bool - 成功返回true，否则返回false
 */
template <class T>
bool LinkQueue<T>::getFront(T &x) const
{
    if (isEmpty())
        return false;
    x = front->data;
    return true;
}
/*
 * Function Name:    getSize
 * Function:         求队列的长度
 * Input Parameters: void
 * Return Value:     int - 队列的长度
 */
template <class T>
int LinkQueue<T>::getSize() const
{
    LinkNode<T> *p = front;
    int k = 0;
    while (p != NULL)
    {
        p = p->link;
        k++;
    }
    return k;
}
