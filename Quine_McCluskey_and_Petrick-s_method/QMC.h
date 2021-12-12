#ifndef _QMC_H
#define _QMC_H

#include <string>
#include <vector>
#include <set>

namespace QMC
{
    using std::string;
    using std::vector;
    using std::set;

    typedef unsigned int Value;

    enum Mode { Auto, Manual };

    class QMC
    {
        private:
            // amount of varialbe
            unsigned int Num_var;
            //
            vector<Value> Term;
            vector<Value> dc_Term;
            //
            vector<string> str_Term;
            vector<string> Prime_Implicants;
            //
            Mode mode;


            friend inline unsigned int Count_one(vector<string>::iterator it);
            friend inline bool Sort_by_Amount_of_One(string a, string b);
            string Dec_to_Bin(Value bin) const;
            bool is_Gray(const string& a, const string& b) const;
            string Merge(const string& a, const string& b) const;

            void Init_str_Term();
            void Make_Implicants();

        public:
            QMC(unsigned int num, Mode mod = Mode::Manual) { Num_var = num; mode = mode; };
            ~QMC() {};

            // make implicant and prime implicant
            void Solve();


            // add Term, by Value, vector or set
            void Add_Term(const Value& val);
            void Add_Term(const vector<Value>& val);
            void Add_Term(const set<Value>& val);

            void Add_dc_Term(const Value& val);
            void Add_dc_Term(const vector<Value>& val);
            void Add_dc_Term(const set<Value>& val);

            // other
            void Change_Mode(Mode mode) { mode = mode; }

            // return
            vector<string> Get_Prime_Implicants() const
            { return Prime_Implicants; }
            vector<string> Get_Term() const
            { return str_Term; }

            // print
            void Print_Prime_Implicants() const;
            void Print_Term() const;
    };
    inline unsigned int Count_one(vector<string>::iterator it);
    inline bool Sort_by_Amount_of_One(string a, string b);
}

#endif
