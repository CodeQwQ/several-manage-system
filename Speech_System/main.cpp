#include "Manager.cpp"
#include "Competance.cpp"
using namespace std;
int main()
{
    Manager m;
    m.Choices();
    //  ------------------------------------------
    int choice;
    while (cin >> choice)
    {
        switch (choice)
        {
        case 1:
            m.begin_this_year();
            break;
        default:
            break;
        }
    }
    return 0;
}