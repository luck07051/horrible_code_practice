#include "QMC.h"
#include <iostream>
#include <algorithm>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main()
{
    QMC::QMC qmc {6};
    QMC::Value val;

    cout << "Enter care term: ";
    while (cin >> val)
    {
        qmc.Add_Term(val);
    }
    cin.clear();
    while ( std::getchar() != '\n' )
        continue;

    cout << "Enter dont care term: ";
    while (cin >> val)
    {
        qmc.Add_dc_Term(val);
    }
    cin.clear();
    while ( std::getchar() != '\n' )
        continue;


    qmc.Solve();


    cout << "\nstr_Term: " << endl;
    qmc.Print_Term();

    cout << "\nPrime Implicants: " << endl;
    qmc.Print_Prime_Implicants();

    return 0;
}
