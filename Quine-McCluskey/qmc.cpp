#include "qmc.h"
#include <math.h>

namespace qmc
{
    unsigned int term::size = 0;

////////////////////////////////////////////////////
    bool term::operator<(const term & te) const
    {
        if (mask_amount == te.mask_amount)
        {
            if (num < te.num)
                return true;
            else if (num == te.num && mask < te.mask)
                return true;
            return false;
        }
        else
        {
            if (mask_amount > te.mask_amount)
                return true;
            else
                return false;
        }
    }

    bool term::operator>(const term & te) const
    {
        if (mask_amount == te.mask_amount)
        {
            if (num > te.num)
                return true;
            else if (num == te.num && mask < te.mask)
                return true;
            return false;
        }
        else
        {
            if (mask_amount > te.mask_amount)
                return true;
            else
                return false;
        }
    }

    bool term::operator==(const term & te) const
    {
        if (num == te.num && mask == te.mask)
            return true;
        return false;
    }
////////////////////////////////////////////////////


    unsigned int term::how_many_one() const
    {
        unsigned int count = 0;
        unsigned long tmp = num;
        for (int i = term::size; i > 0; --i)
        {
            count += tmp % 2;
            tmp /= 2;
        }
        return count;
    }

    unsigned int term::c_mask_amount()
    {
        unsigned int count = 0;
        unsigned long tmp = mask;
        for (int i = term::size; i > 0; --i)
        {
            count += tmp % 2;
            tmp /= 2;
        }
        return count;
    }

    unsigned long term::compare(const term & te) const
    {
        if (mask == te.mask)
        {
            unsigned long tmp = num ^ te.num;
            int count = 0;
            for (int i = term::size; i > 0; --i)
            {
                count += tmp % 2;
                tmp /= 2;
            }

            if (count == 1)
            {
                return mask | (num ^ te.num);
            }
        }
        return 0;
    }

    std::ostream & term::out_for_ta(std::ostream & os) const
    {
        unsigned long mask_ = pow(2, term::size -1);
        for (int i = term::size; i > 0; --i)
        {
            if (mask & mask_)
            {
                os << '-';
            }
            else if (num & mask_)
            {
                os << '1';
            }
            else
            {
                os << '0';
            }

            mask_ /= 2;
        }
        return os;
    }

    std::ostream & term::out_for_out(std::ostream & os) const
    {
        return os;
    }

///////////////////////////////////////


    next_term::next_term(const set<term> & s1, const set<term> & s2)
    {
        for_each(s1.begin(), s1.end(), [&](term te){ v1.push_back(te); });
        for_each(s2.begin(), s2.end(), [&](term te){ v2.push_back(te); });

        unsigned long temp;
        for (unsigned long i = 0; i < v1.size(); ++i)
        {
            for (unsigned long j = 0; j < v2.size(); ++j)
            {
                temp = v1[i].compare(v2[j]);
                if (temp)
                {
                    v1[i].pr_im = v2[j].pr_im = false;
                    v_.push_back( term{ v1[i], temp } );
                }
            }
        }
    };
}
