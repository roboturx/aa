#include <iostream>
//#include <conio.h>
using namespace std;

int main()
{
    using namespace std;
    cout << "Hello World!" << endl;
    int integer1;
    int integer2=100;
    int sum;

    std::cout << "enter first integer"  ;
    std::cin >> integer1; cin.ignore();
    std::cout << "enter 2. integer"  << endl;
    std::cin >> integer2;
    sum = integer1 + integer2;
    cout <<  sum;
    return 0;
}
