#ifndef QMC_H_
#define QMC_H_

#include <iostream>
#include <set>
using std::set;
#include <vector>
using std::vector;
#include <algorithm>
using std::for_each;

namespace qmc
{
    class term
    {
        private:
            unsigned long num;
            unsigned long mask; // mask for '-'

            unsigned int mask_amount;
            unsigned int c_mask_amount();

        public:
            bool pr_im; // if true, this term is preme implicant
            void set_prim_fl() { pr_im = false; };

            static unsigned int size;

            ////////////////////////////////////////////////////////////////////////
            term(unsigned long nu, unsigned long ma = 0, bool pr = true):
                num(nu), mask(ma), mask_amount(c_mask_amount()), pr_im(pr)
                { num = num & ~mask; };

            term(): num(0), mask(0), mask_amount(0), pr_im(true) {};

            term(const term & te):
                num(te.num), mask(te.mask), mask_amount(c_mask_amount()), pr_im(te.pr_im) {};

                // copy te.num to this.num and change this.mask to ma
            term(const term & te, unsigned long ma, bool pr = true):
                num(te.num), mask(ma), mask_amount(c_mask_amount()), pr_im(pr)
                { num = num & ~mask; };
            ////////////////////////////////////////////////////////////////////////


            bool operator<(const term & te) const;
            bool operator>(const term & te) const;
            bool operator==(const term & te) const;
            bool operator<=(const term & te) const { return !(*this > te); };
            bool operator>=(const term & te) const { return !(*this < te); };;
            bool operator!=(const term & te) const { return !(*this == te); };;


            unsigned int how_many_one() const;
            unsigned long compare(const term & te) const; // return new mask, if no, return 0

            std::ostream & out_for_ta(std::ostream & os) const; //ex. 001-1
            std::ostream & out_for_out(std::ostream & os) const; //ex. a'b'ce
    };


    class next_term
    {
        public:
            vector<term> v1;
            vector<term> v2;
            vector<term> v_;

            next_term(const set<term> & s1, const set<term> & s2);
    };

}

#endif
