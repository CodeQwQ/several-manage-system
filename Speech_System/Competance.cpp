#pragma once
#include "Competance.h"

//  构造函数 01
Competant::Competant(int num, double score)
{
    this->num = num;
    this->score = score;
}

//  构造函数 02
Competant::Competant()
{
}

//  给foreach的打印函数，可以输出Competant
void Competant::print_Competant(Competant &c)
{
    cout << c.num << " ";
}

//  给foreach的打印函数，可以输出score
void Competant::print_Competant02(Competant &c)
{
    cout << c.score << " ";
}

//  给foreach的打印函数，可以综合输出
void Competant::print_all(Competant &c)
{
    cout << c.num << "的分数为: " << c.score << endl;
}