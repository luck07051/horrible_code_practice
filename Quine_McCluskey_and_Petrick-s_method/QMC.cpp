#include "QMC.h"
#include <iostream>
#include <algorithm>
#include <iterator>

namespace QMC
{
    void QMC::Solve()
    {
        Init_str_Term();
        Make_Implicants();
    }

    string QMC::Dec_to_Bin(Value bin) const
    {
        string str(Num_var, '0');
        int dex = Num_var;

        while (bin)
        {
            --dex;
            if (bin % 2)
            {
                str[dex] = '1';
            }
            bin /= 2;
        }

        return str;
    }

    bool QMC::is_Gray(const string& a, const string& b) const
    {
        bool gray = false;
        auto it_a = a.begin();
        auto it_b = b.begin();

        while (it_a != a.end())
        {
            if ( *it_a != *it_b )
            {
                if (gray)
                {
                    return false;
                }
                else
                {
                    gray = true;
                }
            }
            ++it_a;
            ++it_b;
        }
        return gray;
    }

    string QMC::Merge(const string& a, const string& b) const
    {
        string ans = a;
        *(std::mismatch(ans.begin(), ans.end(), b.begin()).first) = '-';
        return ans;
    }

    void QMC::Init_str_Term()
    {
        // let Term unique
        set<Value> s_term(Term.begin(), Term.end());
        set<Value> s_dc_term(dc_Term.begin(), dc_Term.end());
        set<Value> s_dc;

        // let dc_Term not have same element of Term
        std::set_difference(s_dc_term.begin(), s_dc_term.end(), s_term.begin(), s_term.end()
                , std::inserter(s_dc, s_dc.end()));

        //reset Term
        Term.clear();
        dc_Term.clear();
        Term.assign(s_term.begin(), s_term.end());
        dc_Term.assign(s_dc.begin(), s_dc.end());


        // set str_Term
        auto insert = [&](Value val)
        {
            str_Term.insert(str_Term.end(), Dec_to_Bin(val));
        };
        std::for_each(s_term.begin(), s_term.end(), insert);
        std::for_each(s_dc.begin(), s_dc.end(), insert);

        std::sort(str_Term.begin(), str_Term.end(), Sort_by_Amount_of_One);
    }

    inline unsigned int Count_one(vector<string>::iterator it)
    {
        return std::count(it->begin(), it->end(), '1');
    }

    void QMC::Make_Implicants()
    {
        Prime_Implicants.clear();
        set<string> merge(str_Term.begin(), str_Term.end());
        vector<string>::iterator term, n_begin, n_end, n_tmp;
        unsigned int num_one;

        // |-------|--------|-----
        // 1       2        3    amount of one
        //  ^       ^        ^
        // term    n_begin  n_end
        //


        while( !merge.empty() )
        {
            vector<string> current(merge.begin(), merge. end());
            std::sort(current.begin(), current.end(), Sort_by_Amount_of_One);
            merge.clear();

            set<string> have_gray, tmp;

            term = current.begin();
            num_one = Count_one(term);

            // let n_begin be Count_one(term) +1
            n_begin = term;
            while ( n_begin != current.end() && Count_one(n_begin) == num_one )
            {
                ++n_begin;
            }
            n_end = n_begin;

            while( n_end != current.end() )
            {
                // let n_end be Count_one(n_begin) +1
                while ( n_end != current.end() && Count_one(n_end) == num_one +1 )
                {
                    ++n_end;
                }

                // ex Count_one(term) == 1 and Count_one(n_begin) == 3
                // that will into the block
                if (n_begin == n_end)
                {
                    term = n_begin;
                    num_one = Count_one(term);
                    while ( n_begin != current.end() && Count_one(n_begin) == num_one )
                    {
                        ++n_begin;
                    }
                    n_end = n_begin;
                    continue;
                }

                while (term != n_begin)
                {
                    n_tmp = n_begin;
                    while (n_tmp != n_end)
                    {
                        if (is_Gray(*term, *n_tmp))
                        {
                            have_gray.insert(*term);
                            have_gray.insert(*n_tmp);
                            merge.insert(Merge(*term, *n_tmp));
                        }
                        ++n_tmp;
                    }
                    ++term;
                }

                // update
                num_one = Count_one(term);
                n_begin = n_end;
            }

            // insert to Prime_Implicants
            tmp.insert(current.begin(), current.end());
            std::set_difference(tmp.begin(), tmp.end(), have_gray.begin(), have_gray.end()
                    , std::inserter(Prime_Implicants, Prime_Implicants.end()));
        }

        std::sort(Prime_Implicants.begin(), Prime_Implicants.end(), Sort_by_Amount_of_One);
    }


    inline bool Sort_by_Amount_of_One(string a, string b)
    {
        return std::count(a.begin(), a.end(), '1') < std::count(b.begin(), b.end(), '1');
    }



    void QMC::Add_Term(const Value& val)
    {
        Term.push_back(val);
        if (mode == Mode::Auto)
            Solve();
    }
    void QMC::Add_Term(const vector<Value>& val)
    {
        Term.insert(Term.end(), val.begin(), val.end());
        if (mode == Mode::Auto)
            Solve();
    }
    void QMC::Add_Term(const set<Value>& val)
    {
        Term.insert(Term.end(), val.begin(), val.end());
        if (mode == Mode::Auto)
            Solve();
    }

    void QMC::Add_dc_Term(const Value& val)
    {
        dc_Term.push_back(val);
        if (mode == Mode::Auto)
            Solve();
    }
    void QMC::Add_dc_Term(const vector<Value>& val)
    {
        dc_Term.insert(dc_Term.end(), val.begin(), val.end());
        if (mode == Mode::Auto)
            Solve();
    }
    void QMC::Add_dc_Term(const set<Value>& val)
    {
        dc_Term.insert(dc_Term.end(), val.begin(), val.end());
        if (mode == Mode::Auto)
            Solve();
    }

    void QMC::Print_Term() const
    {
        std::ostream_iterator<string> out(std::cout, "\n");
        std::copy(str_Term.begin(), str_Term.end(), out);
    }
    void QMC::Print_Prime_Implicants() const
    {
        std::ostream_iterator<string> out(std::cout, "\n");
        std::copy(Prime_Implicants.begin(), Prime_Implicants.end(), out);
    }

}
