#include "Manager.h"
#include "Competance.cpp"
#include <vector>
#include <algorithm>
#include <ctime>
#define NUM_OF_COMPTANT 12
//  开始界面的提示信息
void Manager::Choices()
{
    cout << "请输入您所需要的选项" << endl;
    cout << "******************************" << endl;
    cout << "******1.开始本届演讲比赛******" << endl;
    cout << "******2.查看往届比赛结果******" << endl;
    cout << "******3.清除所有比赛记录******" << endl;
    cout << "******************************" << endl;
}

//  打分函数
void givescore(vector<Competant> &promotion_group1, vector<Competant> &promotion_group2)
{
    srand((unsigned int)time(NULL));
    for (vector<Competant>::iterator i = promotion_group1.begin(); i != promotion_group1.end(); ++i)
        i->score = rand() % 41 + 60;

    for (vector<Competant>::iterator i = promotion_group2.begin(); i != promotion_group2.end(); ++i)
        i->score = rand() % 41 + 60;
}

//  自定义的排序
bool sort_greaterScore(const Competant &a, const Competant &b)
{
    return a.score >= b.score;
}

//  开始本届演讲比赛
void Manager::begin_this_year()
{
    //  先初始化选手的编号
    cout << "选手们的编号为：" << endl;
    int num = 1000;
    vector<Competant> init;
    for (int i = 1; i <= NUM_OF_COMPTANT; i++)
        init.push_back(Competant(num + i, 0));
    for_each(init.begin(), init.end(), Competant::print_Competant);
    cout << endl;

    //  给出分组的结果，前6名为一组，剩下为一组，用到捣乱算法random_shuffle,遍历算法foreach
    //  包含头文件algorithm
    // system("pause");
    cout << "分组后的出场顺序为： " << endl;
    random_shuffle(init.begin(), init.end());
    for_each(init.begin(), init.end(), Competant::print_Competant);
    cout << endl;

    //  给出第一组的信息
    vector<Competant> promotion_fir;
    promotion_fir.resize(init.size() / 2);
    copy(init.begin(), init.begin() + NUM_OF_COMPTANT / 2, promotion_fir.begin());
    cout << "第一组：" << endl;
    for_each(promotion_fir.begin(), promotion_fir.end(), Competant::print_Competant);
    cout << endl;

    //  给出第二组信息
    vector<Competant> promotion_sec;
    promotion_sec.resize(init.size() / 2);
    copy(init.begin() + NUM_OF_COMPTANT / 2, init.end(), promotion_sec.begin());
    cout << "第二组：" << endl;
    for_each(promotion_sec.begin(), promotion_sec.end(), Competant::print_Competant);
    cout << endl;

    // 给两个组打分，封装一个函数叫givescore,并输出两个组的分数
    // for_each(promotion_fir.begin(), promotion_fir.end(), givescore);
    // for_each(promotion_sec.begin(), promotion_sec.end(), givescore);
    // 以上两个方法使得每次进去都重新生成一个种子，因此数字会重复，所以改成用下面的方法
    givescore(promotion_fir, promotion_sec);
    // 输出
    cout << "第一组的成绩为：" << endl;
    for_each(promotion_fir.begin(), promotion_fir.end(), Competant::print_Competant02);
    cout << endl;
    cout << "第二组的成绩为：" << endl;
    for_each(promotion_sec.begin(), promotion_sec.end(), Competant::print_Competant02);
    cout << endl;

    //取出每个组的前三名，再进行排序输出
    sort(promotion_fir.begin(), promotion_fir.end(), sort_greaterScore);
    sort(promotion_sec.begin(), promotion_sec.end(), sort_greaterScore);
    vector<Competant> promoted_competant;
    promoted_competant.resize(promotion_fir.size());
    copy(promotion_fir.begin(), promotion_fir.begin() + promotion_fir.size() / 2, promoted_competant.begin());
    copy(promotion_sec.begin(), promotion_sec.begin() + promotion_sec.size() / 2, promoted_competant.begin() + promotion_sec.size() / 2);
    sort(promoted_competant.begin(), promoted_competant.end(), sort_greaterScore);
    //  输出：
    cout << "晋级者的编号和成绩为：" << endl;
    for_each(promoted_competant.begin(), promoted_competant.end(), Competant::print_all);
}

//  测试main
int main()
{
    Manager m;
    m.begin_this_year();
    return 0;
}