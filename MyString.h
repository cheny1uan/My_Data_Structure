#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstring>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

using std::istream;
using std::ostream;

#define DefaultSize 128 // 默认字符串长度

/*
 * Class Name:       MyString
 * Class:            处理字符串的类
 * Members:          int present_Length - 当前字符串长度
 *                   int max_Length - 最大字符串长度
 *                   char* ch - 字符串指针
 * Methods:          MyString(const int size = DefaultSize) - 构造函数
 *                   MyString(const char* init) - 构造函数
 *                   MyString(const MyString &obj) - 复制构造函数
 *                   ~MyString() - 析构函数
 *                   int length() const - 返回字符串长度
 *                   MyString operator()(int pos, int length) - 返回指定位置和长度的子串
 *                   bool operator==(const MyString &obj) - 判断两个字符串是否相等
 *                   bool operator!=(const MyString &obj) - 判断两个字符串是否不相等
 *                   MyString &operator=(const MyString &obj) - 赋值字符串
 *                   MyString &operator=(const char *ch) - 赋值字符串
 *                   MyString &operator+=(const MyString &obj) - 连接字符串
 *                   char operator[](int num) const - 返回指定位置的字符
 *                   int QuickFind(MyString &pat, int pos) - 快速查找字符串
 */

class MyString

{
    friend istream &operator>>(istream &, MyString &Str);
    friend ostream &operator<<(ostream &, const MyString &Str);

private:
    int present_Length;
    int max_Length;
    char *ch;

public:
    MyString(const int size = DefaultSize);    // 构造函数
    MyString(const char *init);                // 构造函数
    MyString(const MyString &obj);             // 复制构造函数
    ~MyString();                               // 析构函数
    int length() const;                        // 返回字符串长度
    MyString operator()(int pos, int length);  // 返回指定位置和长度的子串
    bool operator==(const MyString &obj);      // 判断两个字符串是否相等
    bool operator!=(const MyString &obj);      // 判断两个字符串是否不相等
    MyString &operator=(const MyString &obj);  // 赋值字符串
    MyString &operator=(const char *ch);       // 赋值字符串
    MyString &operator+=(const MyString &obj); // 连接字符串
    char operator[](int num) const;            // 返回指定位置的字符
    int QuickFind(MyString &pat, int pos);     // 快速查找字符串
};
/*
 * Function Name:    MyString (Constructor)
 * Function:         初始化字符串
 * Input Parameters: const int size - 字符串长度
 */
MyString::MyString(const int size)
{
    max_Length = size;
    ch = new char[size + 1];
    if (ch == NULL)
        cerr << "空间分配错误!" << endl;
    present_Length = 0;
    ch[0] = '\0';
}
/*
 * Function Name:    MyString (Constructor)
 * Function:         初始化字符串
 * Input Parameters: const char* init - 字符串指针
 */
MyString::MyString(const char *init)
{
    int length = strlen(init);
    max_Length = length > DefaultSize ? length : DefaultSize;
    ch = new char[max_Length + 1];
    if (ch == NULL)
        cerr << "空间分配错误!" << endl;
    present_Length = length;
    strcpy(ch, init);
}
/*
 * Function Name:    MyString (Copy Constructor)
 * Function:         复制构造函数
 * Input Parameters: const MyString& obj - 字符串对象
 */
MyString::MyString(const MyString &obj)
{
    int length = obj.present_Length;
    max_Length = length > DefaultSize ? length : DefaultSize;
    ch = new char[max_Length + 1];
    if (ch == NULL)
        cerr << "空间分配错误!" << endl;
    present_Length = length;
    strcpy(ch, obj.ch);
}
/*
 * Function Name:    ~MyString (Destructor)
 * Function:         析构函数
 */
MyString::~MyString()
{
    delete[] ch;
}
/*
 * Function Name:    length
 * Function:         返回字符串长度
 * Return Value:     int - 字符串长度
 */
int MyString::length() const
{
    return present_Length;
}
/*
 * Function Name:    operator()
 * Function:         重载()运算符，返回指定位置和长度的子串
 * Input Parameters: int pos - 子串的起始位置
 *                   int length - 子串的长度
 * Return Value:     MyString - 子串对象
 */
MyString MyString::operator()(int pos, int length)
{
    MyString s;
    if (pos >= 0 && pos < present_Length && length > 0 && pos + length - 1 < present_Length)
    {
        for (int i = 0; i < length; i++)
        {
            s.ch[i] = ch[pos + i];
        }
        s.ch[length] = '\0';
    }
    return s;
}
/*
 * Function Name:    operator==
 * Function:         重载==运算符，判断两个字符串是否相等
 * Input Parameters: const MyString& obj - 字符串对象
 * Return Value:     bool - 相等返回true，否则返回false
 */
bool MyString::operator==(const MyString &obj)
{
    return strcmp(ch, obj.ch) == 0;
}
/*
 * Function Name:    operator!=
 * Function:         重载!=运算符，判断两个字符串是否不相等
 * Input Parameters: const MyString& obj - 字符串对象
 * Return Value:     bool - 不相等返回true，否则返回false
 */
bool MyString::operator!=(const MyString &obj)
{
    return strcmp(ch, obj.ch) != 0;
}
/*
 * Function Name:    operator=
 * Function:         重载=运算符，赋值字符串
 * Input Parameters: const MyString& obj - 字符串对象
 * Return Value:     MyString& - 字符串对象
 */
MyString &MyString::operator=(const MyString &obj)
{
    if (this != &obj)
    {
        delete[] ch;
        ch = new char[obj.max_Length + 1];
        if (ch == NULL)
            cerr << "空间分配错误!" << endl;
        max_Length = obj.max_Length;
        present_Length = obj.present_Length;
        strcpy(ch, obj.ch);
    }
    return *this;
}
/*
 * Function Name:    operator=
 * Function:         重载=运算符，赋值字符串
 * Input Parameters: const char* init - 字符串指针
 * Return Value:     MyString& - 字符串对象
 */
MyString &MyString::operator=(const char *init)
{
    int length = strlen(init);
    max_Length = length > DefaultSize ? length : DefaultSize;
    ch = new char[max_Length + 1];
    if (ch == NULL)
        cerr << "空间分配错误!" << endl;
    present_Length = length;
    strcpy(ch, init);
    return *this;
}
/*
 * Function Name:    operator+=
 * Function:         重载+=运算符，连接字符串
 * Input Parameters: const MyString& obj - 字符串对象
 * Return Value:     MyString& - 字符串对象
 */
MyString &MyString::operator+=(const MyString &obj)
{
    char *temp = ch;
    int length = present_Length + obj.present_Length;
    max_Length = max_Length > length ? max_Length : length;
    ch = new char[max_Length + 1];
    if (ch == NULL)
    {
        cerr << "空间分配错误!" << endl;
        exit(1);
    }
    strcpy(ch, temp);
    strcat(ch, obj.ch);
    present_Length = length;
    delete[] temp;
    return *this;
}
/*
 * Function Name:    operator[]
 * Function:         重载[]运算符，返回指定位置的字符
 * Input Parameters: int num - 字符位置
 * Return Value:     char - 字符
 */
char MyString::operator[](int num) const
{
    if (num < 0 || num >= present_Length)
    {
        cerr << "out of range!\n";
        exit(1);
    }
    return ch[num];
}
/*
 * Function Name:    QuickFind
 * Function:         快速查找字符串
 * Input Parameters: MyString& pat - 字符串对象
 *                   int pos - 查找的起始位置
 * Return Value:     int - 查找成功返回位置，否则返回-1
 */
int MyString::QuickFind(MyString &pat, int pos)
{
    int pLength = pat.length();
    int *next = new int[pLength];
    next[0] = -1;
    int j = 0, k = -1;
    while (j < pLength - 1)
    {
        if (k == -1 || ch[j] == ch[k])
        {
            j++;
            k++;
            next[j] = k;
        }
        else
        {
            k = next[k];
        }
    }
    int tPos = 0;
    int pPos = 0;
    while (tPos < present_Length && pPos < pLength)
    {
        if (pPos == -1 || ch[tPos] == ch[pPos])
        {
            tPos++;
            pPos++;
        }
        else
        {
            pPos = next[pPos];
        }
    }
    delete[] next;
    if (pPos < pLength)
    {
        return -1;
    }
    else
    {
        return tPos - pLength;
    }
}
/*
 * Function Name:    operator>>
 * Function:         重载>>运算符，输入字符串
 * Input Parameters: istream& cin - 输入流
 *                   MyString& Str - 字符串对象
 * Return Value:     istream& - 输入流
 */
istream &operator>>(istream &cin, MyString &Str)
{
    char temp[DefaultSize]; // 定义一个临时缓冲区
    cin >> temp;            // 从标准输入读取字符串到缓冲区

    // 重新分配内存
    Str.present_Length = strlen(temp); // 计算输入的字符串长度
    Str.max_Length = Str.present_Length > DefaultSize ? Str.present_Length : DefaultSize;

    delete[] Str.ch;                       // 释放之前的内存
    Str.ch = new char[Str.max_Length + 1]; // 分配新的内存

    if (Str.ch == NULL)
    {
        cerr << "空间分配错误!" << endl;
        exit(1);
    }

    strcpy(Str.ch, temp); // 将缓冲区的内容复制到Str.ch中
    return cin;
}
/*
 * Function Name:    operator<<
 * Function:         重载<<运算符，输出字符串
 * Input Parameters: ostream& cout - 输出流
 *                   const MyString& Str - 字符串对象
 * Return Value:     ostream& - 输出流
 */
ostream &operator<<(ostream &cout, const MyString &Str)
{
    cout << Str.ch;
    return cout;
}
