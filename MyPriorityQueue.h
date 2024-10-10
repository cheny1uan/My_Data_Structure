/****************************************************************
 * File Name:       MyPQueue.h
 * Author:          cheny1uan
 * Mail:            cheny1uanll@gmail.com
 ****************************************************************/
#include <iostream>
using std::cerr;
using std::endl;
const int DefaultSize = 1000;

/*
 * Class Name:       MyPQueue
 * Class:            优先队列
 * Members:          T *pqelements - 存放队列元素的数组
 *                   int currentSize - 队列当前元素个数
 *                   int maxSize - 队列最大存储容量
 * Methods:          MyPQueue(int sz = DefaultSize) - 构造函数
 *                   ~MyPQueue() - 析构函数
 *                   bool enQueue(const T &x) - 入队
 *                   bool deQueue(T &x) - 出队
 *                   bool getFront(T &x) const - 取队头元素
 *                   bool isEmpty() const - 判断队列是否为空
 *                   bool isFull() const - 判断队列是否已满
 *                   void makeEmpty() - 清空队列
 *                   int getSize() const - 求队列长度
 *                   void adjust() - 调整队列
 */
template <class T>
class MyPQueue
{
public:
    MyPQueue(int sz = DefaultSize);
    ~MyPQueue() { delete[] pqelements; }
    bool enQueue(const T &x);
    bool deQueue(T &x);
    bool getFront(T &x) const;
    bool isEmpty() const { return currentSize == 0; }
    bool isFull() const { return currentSize == maxSize; }
    void makeEmpty() { currentSize = 0; }
    int getSize() const { return currentSize; }

protected:
    T *pqelements;
    int currentSize;
    int maxSize;
    void adjust();
};
/*
 * Function Name:    MyPQueue
 * Function:         构造函数
 * Input Parameters: int sz - 队列最大存储容量
 */
template <class T>
MyPQueue<T>::MyPQueue(int sz) : currentSize(0), maxSize(sz)
{
    pqelements = new T[maxSize];
    if (pqelements == NULL)
    {
        cerr << "存储分配错误!" << endl;
        exit(1);
    }
}
/*
 * Function Name:    adjust
 * Function:         调整队列
 * Input Parameters: 无
 * Return Value:     void
 */
template <class T>
void MyPQueue<T>::adjust()
{
    T temp = pqelements[currentSize - 1];
    int i;
    for (i = currentSize - 2; i >= 0; i--)
    {
        if (temp < pqelements[i])
            pqelements[i + 1] = pqelements[i];
        else
            break;
    }
    pqelements[i + 1] = temp;
}
/*
 * Function Name:    enQueue
 * Function:         入队
 * Input Parameters: const T &x - 数据
 * Return Value:     bool - 成功返回true，否则返回false
 */
template <class T>
bool MyPQueue<T>::enQueue(const T &x)
{
    if (isFull())
    {
        cerr << "队列已满!" << endl;
        return false;
    }
    pqelements[currentSize++] = x;
    adjust();
    return true;
}
/*
 * Function Name:    deQueue
 * Function:         出队
 * Input Parameters: T &x - 出队的元素
 * Return Value:     bool - 成功返回true，否则返回false
 */
template <class T>
bool MyPQueue<T>::deQueue(T &x)
{
    if (isEmpty())
        return false;
    x = pqelements[0];
    for (int i = 1; i < currentSize; i++)
        pqelements[i - 1] = pqelements[i];
    currentSize--;
    return true;
}
/*
 * Function Name:    getFront
 * Function:         取队头元素
 * Input Parameters: T &x - 队头元素
 * Return Value:     bool - 成功返回true，否则返回false
 */
template <class T>
bool MyPQueue<T>::getFront(T &x) const
{
    if (isEmpty())
        return false;
    x = pqelements[0];
    return true;
}