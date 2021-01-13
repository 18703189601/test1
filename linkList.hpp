/*************************************************************************
 @Author: 刘名轩
 @Created Time : 2021年01月03日 星期日 11时09分03秒
 @File Name: linkList.hpp
 @Description:
 ************************************************************************/
#ifndef _LINKLIST_HPP
#define _LINKLIST_HPP

#include <iostream>
#include "linearList.h"

template<class T>
struct linkNode
{
    T data;
    linkNode* link;
    
    //仅通过指针构造
    linkNode(linkNode<T>* ptr = nullptr) { link = ptr; }
    //通过数据和指针构造
    linkNode(const T& d, linkNode<T>* ptr = nullptr) : data(d), link(ptr) {} 
};

template<class T>
class linkList : public linearList<T> 
{
    private:
        linkNode<T>* first;
    public:
        //构造函数
        linkList() { first = new linkNode<T>; }
        linkList(const T& x) { first = new linkNode<T>(x); }
        linkList(linkList<T>& L);//复制构造函数
        ~linkList() { makeEmpty(); delete first; } //析构函数
        //功能函数
        void makeEmpty();            //将表置空
        int size() const { return 0; }
        int length() const;          //表的长度
        linkNode<T>* getHead() const { return first; }
        linkNode<T>* search(T x) const;
        linkNode<T>* locate(int i) const;
        bool getData(int i, T& x) const;
        void setData(int i, T& x);
        bool insert(int i, T& x);
        bool remove(int i, T& x);
        bool empty() const { return first->link == nullptr ? true : false; }
        bool full() const { return false; }
        //void srot();
        void input();
        void output() const;
        linkList<T>& operator=(linkList<T>& L);
};

template<typename T>
linkList<T>::linkList(linkList<T>& L)
{
    T value;
    linkNode<T>* srcptr = L.getHead();
    linkNode<T>* desptr = first = new linkNode<T>;
    while (srcptr->link != nullptr) {
        value = srcptr->link->data;
        desptr->link = new linkNode<T>(value);
        desptr = desptr->link;
        srcptr = srcptr->link;
    }
    desptr->link = nullptr;
}

template<typename T>
void linkList<T>::makeEmpty()
{
    linkNode<T>* ptr;
    while (first->link != nullptr) {
        ptr = first->link;
        first->link = first->link->link; //从链中抽出ptr
        delete ptr;
    }
}

template<typename T>
int linkList<T>::length() const
{
    int len = 0;
    linkNode<T>* ptr = first;
    while (ptr->link != nullptr) {
        ptr = ptr->link;
        len++;
    }
    return len;
}

template<typename T>
linkNode<T>* linkList<T>::search(T x) const
{//在表中寻找值为x的节点地址，如果找不到，返回nullptr
    linkNode<T>* ptr = first->link;
    while (ptr != nullptr) {
        if (ptr->data == x) break;
        ptr = ptr->link;
    }
    return ptr;
}

template<typename T>
linkNode<T>* linkList<T>::locate(int i) const
{
    if (i < 0) return nullptr;
    linkNode<T>* ptr = first;
    int count = 0;
    while (ptr != nullptr) {
        if (count == i) break;
        ++count;
        ptr = ptr->link;
    }
    return ptr;
}

template<typename T>
bool linkList<T>::getData(int i, T& x) const
{
    linkNode<T>* ptr = this->locate(i);
    if (ptr != nullptr) {
        x = ptr->data;
        return true;
    } else {
        return false;
    }
}

template<typename T>
void linkList<T>::setData(int i, T& x)
{
    linkNode<T>* ptr = this->locate(i);
    if (ptr != nullptr) {
        ptr->data = x;
    } 
    return ;
}

template<typename T>
bool linkList<T>::insert(int i, T& x) 
{
    linkNode<T>* ptr = this->locate(i);
    linkNode<T>* current = new linkNode<T>(x);
    if (current == nullptr) {
        std::cerr << "存储分配错误！" << std::endl;
        exit(1);
    }
    if (ptr != nullptr) {
        current->link = ptr->link;
        ptr->link = current;
        return true;
    } else {
        return false;
    }
}

template<typename T>
bool linkList<T>::remove(int i, T& x)
{
    linkNode<T>* ptr = this->locate(i - 1);
    if (ptr->link != nullptr) {
        linkNode<T>* current = ptr->link;
        ptr->link = current->link;
        x = current->data;
        delete current; 
        return true;
    } else {
        return false;
    }
}

template<typename T>
void linkList<T>::input()
{
    T value;
    linkNode<T>* ptr;
    while (std::cin >> value) {
        ptr = new linkNode<T>(value);
        if (ptr == nullptr) {
            std::cerr << "存储分配错误!" << std::endl;
            exit(1);
        } 
        ptr->link = first->link;
        first->link = ptr;
    }
}

template<typename T>
void linkList<T>::output() const
{
    T value;
    int i = 0;
    linkNode<T>* ptr = first->link;
    while (ptr != nullptr) {
        std::cout << '#' << ++i << ':' << ptr->data << std::endl;
        ptr = ptr->link;
    }
}

template<typename T>
linkList<T>& linkList<T>::operator=(linkList<T>& L)
{
    T value;
    linkNode<T>* srcptr = L.getHead();
    linkNode<T>* desptr = first = new linkNode<T>;
    while (srcptr->link != nullptr) {
        value = srcptr->link->data;
        desptr->link = new linkNode<T>(value);
        desptr = desptr->link;
        srcptr = srcptr->link;
    }
    return *this;
}

#endif
