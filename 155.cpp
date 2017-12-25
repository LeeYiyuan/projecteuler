/*
    To generate a size n network, we consider the ways to combine a size i
    network with a size j network in both parallel and series with i >= j, i + j =
    n and i, j != n. This way we consider every size n network at least once,
    and for each n we collect the distinct overall capacitances. Notice that
    there is some dynamic programming involved, as the possible overall
    capacitances for smaller network sizes is cached and retrieved when
    determining the possible overall capacitances for the current network size.

    Also in principle, we can use any fixed capacitance and don't have to stick
    to 60 micro Farads. So we denote our fixed capacitance as 1. This way, when
    we combine fractions, we can ensure that the numerator and denominator
    remains as small as possible.

    It turns out that with fixed capacitance 1, all related variables can fit
    within unsigned int even while neglecting the GCD step of adding fractions.
    As such, we can totally skip the GCD part of adding fractions and define our
    own struct with a custom < operator that considers a / b < c / d <=> ad < bc
    for use by std::set when checking for order.
*/

#include <iostream>
#include <set>
#include <vector>

struct q_t
{
    unsigned int n, d;
    q_t(unsigned int const &_n, unsigned int const &_d) : n(_n), d(_d) { }

    bool operator<(q_t const &rhs) const
    {
        return this->n * rhs.d < this->d * rhs.n;
    }
};

int main()
{
    std::set<q_t> all_values = {
        { q_t(1, 1) }
    };

    std::vector<std::set<q_t>> values = {
        { },
        { q_t(1, 1) }
    };

    for (int n = 2; n <= 18; n++)
    {
        values.emplace_back();
        int i = n - 1;
        int j = 1;
        while (i >= j)
        {
            for (q_t const &a : values[i])
            {
                for (q_t const &b : values[j])
                {
                    int v = a.n * b.d + a.d * b.n;
                    q_t parallel(v, a.d * b.d);
                    q_t series(a.n * b.n, v);
                    
                    if (all_values.find(parallel) == all_values.end())
                    {
                        values.back().emplace(parallel);
                        all_values.emplace(parallel);
                    }

                    if (all_values.find(series) == all_values.end())
                    {
                        values.back().emplace(series);
                        all_values.emplace(series);
                    }
                }
            }
            i--;
            j++;
        }
    }

    std::cout << all_values.size();
}
