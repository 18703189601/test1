/*************************************************************************
 @Author: 刘名轩
 @Created Time : 2021年01月02日 星期六 14时13分50秒
 @File Name: seqList.hpp
 @Description:
 ************************************************************************/
#ifndef SEQLIST_HPP
#define SEQLIST_HPP

#include <iostream>
#include <cstdlib>
#include "linearList.h"

const int defaultSize = 100;

template<class T>
class seqList : public linearList<T>
{
    protected:
        T* data;            //存放的数组
        int maxSize;        //最大的可以容纳的表项的数目
        int last;           //当前已存的表项的最后位置（从0开始）
        void reSize(int newSize); //改变数组空间的大小
    public:
        seqList(int size = defaultSize);
        seqList(seqList<T>& L);
        virtual ~seqList() { delete[] data; } 
        virtual int size() const { return maxSize; }
        virtual int length() const { return last + 1; } 
        int search(T x) const;
        int locate(int i) const;
        virtual bool getData(int i, T& x) const; 
        virtual void setData(int i, T& x);
        virtual bool insert(int i, T& x);
        virtual bool remove(int i, T& x);
        virtual bool empty() const { return last == -1 ? true : false; } 
        virtual bool full() const { return last == maxSize - 1 ? true : false; }
        //virtual void sort();
        //virtual void input();
        void input();
        virtual void output() const;
        virtual seqList<T> operator=(seqList<T>& L); 
};

template<typename T>
void seqList<T>::reSize(int newSize)
{
    if (newSize < maxSize) {
        std::cerr << "无效的数组大小" << std::endl;
        return ;
    } else {
        T* newData = new T[newSize];
        if (newData == NULL) {
            std::cerr << "存储分配错误!" << std::endl;
            exit(1);
        }
        int n = last + 1;
        T* srcptr = data;
        T* desptr = newData;
        for (int i = 0; i < n; i++)
        {
            *desptr = *data;
            desptr++;
            data++;
        }
        delete[] data;
        data = newData;
        maxSize = newSize;
    }
}

template<typename T>
seqList<T>::seqList(int size)
{
    if (size > 0) {
        maxSize = size;
        last = -1;
        data = new T[maxSize];
        if (data == NULL) {
            std::cerr << "存储分配错误!" << std::endl;
            exit(1);
        }
    }
}

template<typename T>
seqList<T>::seqList(seqList<T>& L)
{
    this->maxSize = L.size();
    this->last = L.length() - 1;
    T value;
    data = new T[maxSize];
    if (data == NULL) {
        std::cerr << "储存分配错误!" << std::endl;
        exit(1);
    }
    for (int i = 1; i < L.length(); i++) {
        L.getData(i, value);
        data[i - 1] = value;
    }
}

template<typename T>
int seqList<T>::search(T x) const
{
    for (int i = 0; i < last + 1; i++) {
        if (data[i] == x) 
            return i + 1;
    }
    return 0;
}

template<typename T>
int seqList<T>::locate(int i) const
{//定位函数，函数返回表项的位置，如果不再数组范围内，则返回0
    if (i >= 1 && i <= last + 1)
        return i;
    return 0;
}

template<typename T>
bool seqList<T>::getData(int i, T& x) const
{
    if (i >= 1 && i <= last + 1) {
        x = data[i - 1];
        return true;
    } else {
        return false;
    }
}

template<typename T>
void seqList<T>::setData(int i, T& x)
{
    if (i >= i && i<= last + 1) {
        data[i - 1] = x;
    }
}

template<typename T>
bool seqList<T>::insert(int i, T& x)
{//将T插在第i(0 <= i <= last + 1)个表项之后
    if (last == maxSize - 1) return false;
    if (i < 0 || i > last + 1) return false;
    for (int j = last; j >= i; --j) {
        data[j + 1] = data[j];
    }
    data[i] = x;
    last++;
    return true;
}

template<typename T>
bool seqList<T>::remove(int i, T& x)
{//将第i(1 <= i <= last + 1)个表项remove
    if (last == -1) return false;
    if (i < 0 || i > last + 1) return false;
    x = data[i - 1];
    for (int j = i - 1; j < last; ++j) {
        data[j] = data[j + 1];
    }
    last--;
    return false;
}

template<typename T>
void seqList<T>::input()
{
    std::cout << "开始创建顺序表，输入创建的元素个数：" ;
    while (1) {
        int n;
        std::cin >> n;
        last = n - 1;
        if (last <= maxSize - 1) break;
        std::cout << "表中的元素个数不得超过" << maxSize - 1 << std::endl;
    }
    std::cout << "逐个输入各个元素" << std::endl;
    for (int i= 0; i <= last; ++i) {
        std::cin >> data[i];
        //std::cout << i + 1 << std::endl;
    }
    std::cout << std::endl << "输入完毕！" << std::endl;
}

template<typename T>
void seqList<T>::output() const
{
    std::cout << "当前顺序表的最后位置为：" << last << std::endl;
    for (int i = 0; i <= last; i++) {
        std::cout << '#' << i + 1 << ':' << data[i] << std::endl;
    }
}

template<typename T>
seqList<T> seqList<T>::operator=(seqList<T>& L)
{
    maxSize = L.size();
    last = L.length() - 1;
    T value;
    data = new T[maxSize];
    if (data == NULL) {
        std::cerr << "储存分配错误!" << std::endl;
        exit(1);
    }
    for (int i = 1; i < L.length(); i++) {
        L.getData(i, value);
        data[i - 1] = value;
    }
    return *this;
}

#endif
