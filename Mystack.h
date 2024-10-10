/****************************************************************
 * File Name:       Mystack.h
 * Author:          cheny1uan
 * Mail:            cheny1uanll@gmail.com
 ****************************************************************/
#include <iostream>
using std::cerr;
using std::endl;
const int MAXSIZE = 1000;
/*
 * Class Name:       MyStack
 * Class:            栈（用链表模拟）
 * Members:          LinkNode<T> *top - 栈顶指针
 *                   LinkNode<T> - 结点类
 * Methods:          MyStack() - 构造函数
 *                  ~MyStack() - 析构函数
 *                   MyStack(const MyStack<T> &other) - 拷贝构造函数
 *                   MyStack<T> &operator=(const MyStack<T> &other) - 赋值运算符重载
 *                   void push(const T x) - 入栈
 *                   bool pop(T &x) - 出栈
 *                   bool getTop(T &x) const - 取栈顶元素
 *                   bool isEmpty() const - 判断栈是否为空
 *                   bool isFull() const - 判断栈是否已满
 *                   int getSize() const - 求栈的长度
 *                   void makeEmpty() - 清空栈
 */
template <class T>
class MyStack
{
public:
    template <class U>
    struct LinkNode
    {
        U data;
        LinkNode<U> *link;
        LinkNode(LinkNode<U> *ptr = NULL) { link = ptr; }
        LinkNode(const U &item, LinkNode<U> *ptr = NULL)
        {
            data = item;
            link = ptr;
        }
    };
    MyStack() : top(NULL) {}
    ~MyStack() { makeEmpty(); };
    MyStack(const MyStack<T> &other);
    MyStack<T> &operator=(const MyStack<T> &other);
    void push(const T x);
    bool pop(T &x);
    bool getTop(T &x) const;
    bool isEmpty() const { return top == NULL; }
    bool isFull() const { return false; }
    int getSize() const;
    void makeEmpty();

private:
    LinkNode<T> *top;
};
/*
 * Fuction Name:     makeEmpty
 * Function:         清空栈
 * Parameters:       void
 * Return:           void
 */
template <class T>
void MyStack<T>::makeEmpty()
{
    LinkNode<T> *p;
    while (top != NULL)
    {
        p = top;
        top = top->link;
        delete p;
    }
}
/*
 * Function Name:    push
 * Function:         入栈
 * Input Parameters: const T x - 数据
 */
template <class T>
void MyStack<T>::push(const T x)
{
    top = new LinkNode<T>(x, top);
    if (top == NULL)
    {
        cerr << "存储分配错误!" << endl;
        exit(1);
    }
}
/*
 * Fuction Name:     pop
 * Function:         出栈
 * Parameters:       T &x - 出栈的元素
 * Return:           bool - 成功返回true，否则返回false
 */
template <class T>
bool MyStack<T>::pop(T &x)
{
    if (isEmpty())
        return false;
    LinkNode<T> *p = top;
    x = top->data;
    top = top->link;
    delete p;
    return true;
}
/*
 * Function Name:    getTop
 * Function:         取栈顶元素
 * Input Parameters: T &x - 栈顶元素
 * Return Value:     bool - 成功返回true，否则返回false
 */
template <class T>
bool MyStack<T>::getTop(T &x) const
{
    if (isEmpty())
        return false;
    x = top->data;
    return true;
}
/*
 * Function Name:    getSize
 * Function:         求栈的长度
 * Input Parameters: 无
 * Return Value:     int - 栈的长度
 */
template <class T>
int MyStack<T>::getSize() const
{
    LinkNode<T> *p = top;
    int k = 0;
    while (p != NULL)
    {
        p = p->link;
        k++;
    }
    return k;
}
/*
 * Function Name:    MyStack
 * Function:         拷贝构造函数
 * Input Parameters: const MyStack<T> &other - 源栈
 */
template <class T>
MyStack<T>::MyStack(const MyStack<T> &other)
{
    top = NULL;
    if (!other.isEmpty())
    {
        LinkNode<T> *src = other.top;
        LinkNode<T> *dest = new LinkNode<T>(src->data);
        top = dest;
        src = src->link;
        while (src != NULL)
        {
            dest->link = new LinkNode<T>(src->data);
            dest = dest->link;
            src = src->link;
        }
    }
}
/*
 * Function Name:    operator=
 * Function:         赋值运算符重载
 * Input Parameters: const MyStack<T> &other - 源栈
 * Return Value:     MyStack<T> & - 目标栈
 */
template <class T>
MyStack<T> &MyStack<T>::operator=(const MyStack<T> &other)
{
    if (this != &other)
    {
        makeEmpty(); // 清空当前栈

        if (!other.isEmpty())
        {
            LinkNode<T> *src = other.top;
            LinkNode<T> *dest = new LinkNode<T>(src->data);
            top = dest;
            src = src->link;
            while (src != NULL)
            {
                dest->link = new LinkNode<T>(src->data);
                dest = dest->link;
                src = src->link;
            }
        }
    }
    return *this;
}