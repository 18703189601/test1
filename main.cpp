/*************************************************************************
 @Author: 刘名轩
 @Created Time : 2021年01月06日 星期三 18时26分15秒
 @File Name: main.cpp
 @Description:
 ************************************************************************/
#include <iostream>
#include "seqList.hpp"
#include "linkList.hpp"
#include "doublyList.hpp"

using namespace std;
/*
 * hhhhck
 * fwiefhwiufhu
 */
int main()
{
    doublyList<int> L;
    L.push_front(3);
    L.push_front(4);
    int x = 202;
    L.insert(1, x);
    L.push_back(4);
    L.push_front(123);
    L.push_front(1234);
    L.push_back(34);
    L.push_back(23);
    L.push_back(51);
    L.push_back(94);
    L.push_back(1010);
    L.output();
    cout << "************************" << endl;
    L.output(L.length(), false);
    cout << "The length of the list is: " << L.length() << endl;
    return 0;
}
