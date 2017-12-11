/*
    ============================================================================
            THEOREM 1 : f(n, d) direct computation for special values of n.
    ============================================================================
    LEMMA 1: f(10^{m + 1} - 1, d) = 10f(10^m -  1, d) + 10^m for all positive
    digits d and all positive integers m.

    PROOF: Let m be some positive integer m, for example 6. Then f(10^{m + 1} -
    1, d) is essentially the sum of the number of occurences of d across the
    numbers 000000 - 999999. Note that we can split these numbers into ranges
    that are grouped according to their first digits:

        000000 - 0999999    300000 - 399999    600000 - 699999    900000 - 999999
        100000 - 1999999    400000 - 499999    700000 - 799999
        200000 - 2999999    500000 - 599999    800000 - 899999

    For every digit d, each range contributes exactly f(10^m - 1, d) to the
    required f(10^{m + 1} - 1, d). Additionally, every number in the range with
    leading digit equal to d contributes an additional 1 to f(10^{m + 1} - 1,
    d). There are 10 ranges and 10^m numbers in each range. Hence,

        f(10^{m + 1} - 1, d) = 10f(10^m - 1, d) + 10^n

    as required.

    THEOREM 1: f(10^m - 1, d) = 10^{m - 1}n with f(0, d) = 0 for all positive
    digits d.

    PROOF: In the expression of theorem 1, move all terms with f to the LHS.
    Then, divide all terms by 10^{m + 1}. By summing up both sides from m = 1 to
    m = M, cancellations occur on the LHS and RHS is just the sum of the same
    constant M times. Eventually and rather trivially, one can work out that

        f(10^m - 1, d) = 10^{m - 1}m

    as required.

    ============================================================================
            ALGORITHM 1 : f(n, d) direct computation for general n.
    ============================================================================
    This algorithm computes directly f(n, d) for positive digits d and positive
    n.

    Similar to the proof of lemma 1, we can split every number into ranges that
    are grouped, in this case, by their first digits. For example for 3519989,
    we have

        00000000 - 09999999    30000000 - 30999999    35000000 - 35099999
        10000000 - 19999999    31000000 - 31999999    35100000 - 35109999
        20000000 - 29999999    32000000 - 32999999    35110000 - 35119999
                               33000000 - 33999999
                               34000000 - 34999999

    .. and so on.

    For each range, let m be the number of last digits that are varying. The
    range 33000000 - 33999999 would have m = 6 in this case.

    The varying last m digits will contribute f(10^m - 1, d) = f(n, d). But from
    theorem 1, f(10^m - 1, d) is just 10^{m - 1}m.

    Additionally, for each of the 10^m number in the range, the range "header",
    which is the first fixed digits, will repeat 10^m times. Let k be the number
    of occurences of d in the range header. Then there is an additional
    contribution of k * 10^m by the range to f(n, d).

    We sum up the contributions across all ranges to compute directly f(n, d)
    for all positive digits d.

    ============================================================================
            ALGORITHM 2 : Search algorithm for n satisfying f(n, d) = n.
    ============================================================================
    For each digit e in n, we refer to the digit value as e appended with the
    respective trailing zeroes. For example, 199981 has digit values

        100000
         90000
          9000
           900
            80
             1

    We first start by selecting the largest digit value that corresponds to
    the left most digit. Then, we do a backtracking search for the next
    digit value starting with 0, ..., 9, 10, ..., 90, 100, ..., 900,... whose
    length must be strictly less than the current digit value considered.

    For each node in the search tree, we have candidates for the next digit
    value. We can check if each candidate is valid by considering the maximum
    and minimum allowed f(n, d) results for the particular range header which
    considers the candidate.

    For example, we start at the root node with initial digit value 100000. We
    consider the candidate 90000. The resultant range header will be 190000.
    Suppose that there exists some n with this header, i.e. some n that lies in
    190000 - 199999, such that f(n, d) = n for selected d. Then f(n, d) must
    also have header 190000. Since f(n, d) is monotonically increasing with
    respect to n, then

        f(190000, d) <= f(n, d) = n <= 199999
        f(199999, d) >= f(n, d) = n >= 190000

    In principle, if instead f(190000, d) > 199999 or f(199999) < 190000
    respectively, then we know there cannot exist any solution with such a
    header and we can eliminate the candidate entirely.

    We have a solution at every node where the previously selected digit value
    is one digit long and do not search any further beyond these nodes.

    At the moment, it turns out that selecting initial digit values up to
    90000000000 and doing a search for each of these initial digit values works,
    but I suppose an upper limit on the length of n is provable.
*/

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <numeric>

typedef unsigned long long ull;

ull f(ull n, int digit)
{
    ull result = 0;
    std::string n_s = std::to_string(n);
    int l = n_s.length();
    int head_count = 0;

    for (int i = 0; i < n_s.length(); i++)
    {
        int d = n_s[i] - '0';
        for (int _d = 0; _d < d; _d++)
        {
            int _head_count = head_count;
            if (_d == digit)
                _head_count++;
            result += ((ull)std::pow(10, l - i - 2)) * (l- i - 1);
            result += std::pow(10, l - i - 1) * _head_count;
        }
        if (d == digit)
            head_count++;
    }
    result += head_count;

    return result;
}

void search(std::vector<ull> const &selected, ull n_selected, int digit, ull &sum)
{
    if (selected.back() < 10)
    {
        if (f(n_selected, digit) == n_selected)
            sum += n_selected;
        return;
    }

    ull d_limit = 1;
    ull _d_limit = selected.back();
    while (_d_limit >= 10)
    {
        d_limit *= 10;
        _d_limit /= 10;
    }

    int d_base = 0;
    ull m = 1;
    ull d = d_base * m;
    ull n = n_selected + d;
    while (d < d_limit)
    {
        ull sub_n_min = n;
        ull sub_n_max = n + m - 1;

        if (f(sub_n_min, digit) <= sub_n_max && f(sub_n_max, digit) >= sub_n_min)
        {
            std::vector<ull> _selected(selected);
            _selected.emplace_back(d);
            search(_selected, n_selected + d, digit, sum);
        }

        d_base++;
        if (d_base == 10)
        {
            d_base = 1;
            m *= 10;
        }
        d = d_base * m;
        n = n_selected + d;
    }
}

int main()
{
    ull sum = 0;
    for (int digit = 1; digit <= 9; digit++)
    {
        int d_base = 0;
        ull m = 1;
        ull d = d_base * m;
        while (d <= 90000000000)
        {
            search({ d }, d, digit, sum);

            d_base++;
            if (d_base == 10)
            {
                d_base = 1;
                m *= 10;
            }
            d = d_base * m;
        }
    }
    std::cout << sum;
}
