#include "qmc.h"
using qmc::term;
using qmc::next_term;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <fstream>
using std::ofstream;

#include <set>
using std::set;

#include <vector>
using std::vector;

#include <algorithm>
using std::for_each;
using std::copy;
using std::copy_if;

#include <iterator>

#include <math.h>
using std::pow;



void Set_Size();
void Input(set<term> & min, set<term> & dont, set<term> & all);
class make_table
{
    public:
        bool is_show;
        std::ostream & os;

        make_table(bool sh, std::ostream & ost): is_show(sh), os(ost) {};
        ~make_table() {};
        void Make_Table(set<term> & in, set<term> & pi);
};



int main()
{
    ofstream of("abc");

    Set_Size();

    set<term> minterm, dontcare, all;
    cout << endl;
    Input(minterm, dontcare, all);

    set<term> prime_implicants;
    make_table mt{true, of};
    mt.Make_Table(all, prime_implicants);


    cout << "prime implicants have" << endl;
    for_each(prime_implicants.begin(), prime_implicants.end(), [&](term te)
            {
                cout << '\t';
                te.out_for_ta(cout);
                cout << endl;
            } );


    return 0;
}


void Set_Size()
{
    unsigned int temp;
    unsigned int temp_size = sizeof(unsigned long) *8 -1; //
    cout << "Enter how many input(max:" << temp_size << "): ";
    while (!(cin >> temp) || temp < 0 || temp > temp_size)
    {
        cin.clear();
        while (cin.get() != '\n')
            continue;
        cout << "Error input, enter again: ";
    }
    while (cin.get() != '\n')
        continue;

    term::size = temp;
}


void Input(set<term> & min, set<term> & dont, set<term> & all)
{
    unsigned long temp;
    unsigned long max_ = pow(2, term::size) -1;
    cout << "(range: 0 ~ " << max_ << ")" << endl;
    cout << "(out the range to stop)" << endl;
    cout << "Enter minterm: " << endl;
    while (cin >> temp)
    {
        if (temp < 0 || temp > max_)
            break;
        min.insert( term{temp} );
        all.insert( term{temp} );
    }
    if (!cin)
    {
        cin.clear();
        while (cin.get() != '\n')
            continue;
    }

    cout << "Enter don't care: " << endl;
    while (cin >> temp)
    {
        if (temp < 0 || temp > max_)
            break;
        if (!min.count(temp))
        {
            dont.insert( term{temp} );
            all.insert( term{temp} );
        }
    }
    if (!cin)
    {
        cin.clear();
        while (cin.get() != '\n')
            continue;
    }
}

void make_table::Make_Table(set<term> & in, set<term> & pi)
{
    unsigned int gsize = term::size +1;
    vector< set<term> > group(gsize);

    //grouping
    for_each(in.begin(), in.end(), [&group](term te){ group[te.how_many_one()].insert(te); } );

    unsigned int times = 0;
    while (gsize > 1)
    {
        vector< set<term> > group_(gsize -1);
        //comparing
        for (unsigned long i = 0; i < gsize -1; ++i)
        {
            next_term nt { group[i], group[i+1] };
            for_each(nt.v_.begin(), nt.v_.end(), [&](const term & te) { group_[i].insert(te); } );
            group[i].clear();
            group[i+1].clear();
            for_each(nt.v1.begin(), nt.v1.end(), [&](const term & te) { group[i].insert(te);} );
            for_each(nt.v2.begin(), nt.v2.end(), [&](const term & te) { group[i+1].insert(te); } );
        }


        // show out the table
        unsigned int i_temp = 0;
        os << "\n=======================\n\n";
        for_each(group.begin(), group.end(), [&](const set<term> & grp)
                {
                    if (!grp.empty())
                    {
                        os << "Group ";
                        for (unsigned int i = 0; i <= times; ++i)
                        {
                            os << i_temp + i;
                        }
                        os << endl;
                        for_each(grp.begin(), grp.end(), [&](const term & te)
                                {
                                    os << '\t';
                                    te.out_for_ta(os);
                                    if (te.pr_im)
                                    {
                                        os << " *";
                                    }
                                    os << endl;
                                } );
                    }
                    ++i_temp;
                } );
        os << "\n=======================\n\n";
        i_temp = 0;


        //store prime implicants
        for_each(group.begin(), group.end(), [&](set<term> grp)
                {
                for_each(grp.begin(), grp.end(), [&](term te){ if (te.pr_im) pi.insert(te); } );
                } );


        //if group_ have nothing, break
        if ( !any_of(group_.begin(), group_.end(), [](set<term> grp) { return !grp.empty(); } ) )
                break;


        //prepare the next teims;
        swap(group, group_);
        --gsize;
        ++times;
    }
}
