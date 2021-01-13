/*************************************************************************
 @Author: 刘名轩
 @Created Time : 2021年01月02日 星期六 13时02分46秒
 @File Name: linearList.h
 @Description:
 ************************************************************************/
#ifndef LINEARLIST_H
#define LINEARLIST_H

template<class T>
class linearList
{
    public:
        linearList() {};                   //构造函数
        ~linearList() {};                  //析构函数
        virtual int size() const = 0;   //求表的最大体积
        virtual int length() const = 0; //求表长度
        //virtual int search(T& x) const = 0; //在表中寻找定值x
        //virtual int locate(int i) const = 0;//在表中定位第i个元素的位置
        virtual bool getData(int i, T& x) const = 0; //取第i个表项的值，返回x
        virtual void setData(int i, T& x) = 0; //修改第i个表项的值为x
        virtual bool insert(int i, T& x) = 0;  //在第i个表项的后面插入x
        virtual bool remove(int i, T& x) = 0;  //删除第i个表项，通过x返回
        virtual bool empty() const = 0;        //判断表是否为空
        virtual bool full() const = 0;         //判断表是否满
        //virtual void sort() = 0;               //排序
        //virtual void input() = 0;              //输入
        virtual void output() const = 0;       //输出
        //virtual linearList<T>& operator=(linearList<T>& L) = 0; // 复制构造函数
};

#endif
