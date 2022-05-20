#pragma once
#include <string>
#include <iostream>

using namespace std;
class Competant
{
public:
    int num;
    double score;

public:
    //  构造函数 01
    Competant(int num, double score);

    Competant();

    //  给foreach的打印函数，可以输出Competant
    static void print_Competant(Competant &c);

    //  给foreach的打印函数，可以输出score
    static void print_Competant02(Competant &c);

    //  给foreach的打印函数，可以综合输出
    static void print_all(Competant &c);
};