/*************************************************************************
 @Author: 刘名轩
 @Created Time : 2021年01月04日 星期一 15时36分38秒
 @File Name: doublyList.hpp
 @Description: 双向循环链表
 ************************************************************************/
#ifndef _DOUBLYLIST_HPP
#define _DOUBLYLIST_HPP 

#include <iostream>
#include "linearList.h"

template<class T>
struct doublyNode
{
    T data;
    doublyNode* prior;
    doublyNode* next;

    //构造函数
    doublyNode(doublyNode<T>* ptr1 = nullptr, doublyNode<T>* ptr2 = nullptr) 
    {
        prior = ptr1;
        next = ptr2;
    }
    doublyNode(const T& da, doublyNode<T>* ptr1 = nullptr, doublyNode<T>* ptr2 = nullptr) 
        : data(da), prior(ptr1), next(ptr2) {}
};

template<class T>
class doublyList : public linearList<T>
{
    private:
        doublyNode<T>* first;
        doublyNode<T>* last;
    public:
        doublyList(); 
        doublyList(const T& x);
        doublyList(doublyList<T>& dL);//复制构造函数
        ~doublyList() { makeEmpty(); delete first; }
        //共有函数        
        void makeEmpty();
        int size() const {return 0;}
        int length() const;
        doublyNode<T>* getHead() const { return first; }
        doublyNode<T>* getRear() const { return last; }
        doublyNode<T>* search(T x) const;
        doublyNode<T>* locate(int i) const;
        bool getData(int i, T& x) const;
        void setData(int i, T& x);
        bool insert(int i, T& x);
        bool remove(int i, T& x);
        bool empty() const { return first->next == first ? true : false; }
        bool full() const { return false; }
        //void srot();
        void input(T endTag);
        void output() const;
        //重载函数
        doublyList<T>& operator=(doublyList<T>& L);
    public:
        void push_front(T x);
        void push_back(T x);
        void output(int i, bool tf = true) const;
};

template<typename T>
doublyList<T>::doublyList()
{
    first = new doublyNode<T>;
    first->prior = first;
    first->next = first;
    last = first;
}

template<typename T>
doublyList<T>::doublyList(const T& x)
{
    first = new doublyNode<T>(x);
    first->prior = first;
    first->next = first;
    last = first;
}

template<typename T>
doublyList<T>::doublyList(doublyList<T>& dL)
{
    T value;
    doublyNode<T>* srcptr = dL.getHead();
    doublyNode<T>* desptr = first = new doublyNode<T>;
    while (srcptr->next != dL.getHead()) {
        value = srcptr->next->data;
        //将新的结点前驱以及值确定好，以及链接前一个和新的结点
        desptr->next = new doublyNode<T>(value, desptr);
        srcptr = srcptr->next;
        desptr = desptr->next;
    }
    //最后处理last的下一个以及first的前一个
    last = desptr;
    last->next = first;
    first->prior = last;
}

template<typename T>
void doublyList<T>::makeEmpty()
{//将其一个一个地清除
    doublyNode<T>* ptr;
    while (first->next != first) {
        ptr = first->next;
        first->next = ptr->next;
        ptr->next->prior = first;
        delete ptr;
    }
}

template<typename T>
int doublyList<T>::length() const
{
    int count = 0;
    doublyNode<T>* ptr = first;
    while (ptr->next != first) {
        ++count;
        ptr = ptr->next; 
    }
    return count;
}

template<typename T>
doublyNode<T>* doublyList<T>::search(T x) const
{
    doublyNode<T>* ptr = first->next;
    while (ptr != first) {
        if (ptr->data == x) break;
        ptr = ptr->next;
    }
    if (ptr == first) return nullptr;
    return ptr;
}

template<typename T>
doublyNode<T>* doublyList<T>::locate(int i) const
{
    if (i < 0 || i > this->length()) return nullptr;
    doublyNode<T>* ptr = first;
    int count = 0;
    while (count != i) {
        ++count;
        ptr = ptr->next;
    }
    return ptr;
}

template<typename T>
bool doublyList<T>::getData(int i, T& x) const
{
    doublyNode<T>* ptr = locate(i);
    if (ptr == nullptr) return false;
    x = ptr->data;
    return true;
}

template<typename T>
void doublyList<T>::setData(int i, T& x)
{
    doublyNode<T>* ptr = locate(i);
    if (ptr != nullptr) {
        ptr->data = x;
    }
    return ;
}

template<typename T>
bool doublyList<T>::insert(int i, T& x)
{//在第i个数后面插入数据x
    doublyNode<T>* ptr = this->locate(i);
    if (ptr == nullptr) return false;
    //设置新结点，数据为x，前驱为ptr，后继为ptr->next
    doublyNode<T>* current = new doublyNode<T>(x, ptr, ptr->next);
    ptr->next->prior = current; //插入位置后面的前驱变为新节点
    ptr->next = current; //第i个数据后继为新结点
    return true; 
}

template<typename T>
bool doublyList<T>::remove(int i, T& x)
{
    doublyNode<T>* ptr = this->locate(i - 1);
    if (ptr->next == nullptr || i == this->length() + 1) return false;
    x = ptr->next->data;//将第i个数据取出放入x
    doublyNode<T>* current = ptr->next;//暂时保存第i个数据的指针
    ptr->next = current->next; //第i-1个数据下一个数据指向第i+1个数据
    current->next->prior = ptr; //第i+1个数据指向第i-1个
    delete current; //删除第i个节点
    return true;
}

template<typename T>
void doublyList<T>::input(T endTag)
{//头插法
    std::cout << "Enter your datas: ";
    T value;
    doublyNode<T>* ptr;
    while (value != endTag) {
        std::cin >> value;
        ptr = new doublyNode<T>(value, first, first->next);
        first->next = ptr;
    } 

    ptr = first;
    while (ptr->next != nullptr) {
        ptr = ptr->next;
    }
    last = ptr;
    last->next = first;
    first->prior = last;

}

template<typename T>
void doublyList<T>::output() const
{
    std::cout << std::endl << "The datas of the doubly list are: " << std::endl;
    T value;
    if (this->empty()) {
        std::cout << "This doubly list is empty! " << std::endl;
        return ;
    }
    doublyNode<T>* ptr = first->next;
    int i = 0;
    while (ptr != first) {
        std::cout << '#' << i + 1 << ':' << ptr->data << std::endl;
        ptr = ptr->next; 
        ++i;
    }
}

template<typename T>
doublyList<T>& doublyList<T>::operator=(doublyList<T>& dL)
{
    T value;
    doublyNode<T>* srcptr = dL.getHead();
    doublyNode<T>* desptr = first = new doublyNode<T>;
    while (srcptr->next != dL.getHead()) {
        value = srcptr->next->data;
        //将新的结点前驱以及值确定好，以及链接前一个和新的结点
        desptr->next = new doublyNode<T>(value, desptr);
        srcptr = srcptr->next;
        desptr = desptr->next;
    }
    //最后处理last的下一个以及first的前一个
    last = desptr;
    last->next = first;
    first->prior = last;
    return *this;
}

template<typename T>
void doublyList<T>::push_front(T x)
{
    doublyNode<T>* ptr = new doublyNode<T>(x, first, first->next);
    if (first->prior == first) {
        last = ptr;
        first->prior = last;
        first->next = last;
    } else {
        first->next->prior = ptr;
        first->next = ptr;
    }
    return ;
}

template<typename T>
void doublyList<T>::push_back(T x)
{
    doublyNode<T>* ptr = new doublyNode<T>(x, last, first);
    first->prior = ptr;
    last->next = ptr;
    last = ptr;
    return ;
}

template<typename T>
void doublyList<T>::output(int i, bool tf) const
{
    if (this->empty()) {
        std::cout << "This list is empty!" << std::endl;
        return ;
    }

    doublyNode<T>* ptr;
    if (i >= 0) {
        ptr = locate(i);
    } else {
        ptr = locate(this->length() + i + 1);
    }

    if (ptr == nullptr) return ;
    int len = this->length();
    
    doublyNode<T>* current = ptr;
    if (tf == true) {
        //方向：first->last
        std::cout << "从第" << i << "个数据开始正向遍历：" << std::endl;
        if (i < 0) i = i + len + 1;
        while (current->next != ptr) {
            if (current == first) {
                current = current->next;
                continue;
            } 

            if (i <= len) {
                std::cout << '#' << i << ':' << current->data << std::endl;
            } else {
                std::cout << '#' << i - len << ':' << current->data << std::endl;
            }
            current = current->next;
            ++i;
        }
        if (current != first)
            std::cout << '#' << i - len << ':' << current->data << std::endl;
    } else {
        //方向：last->first
        std::cout << "从第" << i << "个数据开始反向遍历" << std::endl;
        if (i < 0) i = len + i + 1;
        while (current->prior != ptr) {
            if (current == first) {
                current = current->prior;
                continue;
            } 
            if (i > 0) {
                std::cout << '#' << i << ':' << current->data << std::endl;
            } else {
                std::cout << '#' << i + len << ':' << current->data << std::endl;
            }
            current = current->prior;
            --i;
        }
        if (current != first)
            std::cout << '#' << i + len << ':' << current->data << std::endl;
    }
}


#endif
