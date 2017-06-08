/*
    Consider a set A with length 7 with the required properties. Let the
    elements of the set be a_1 < a_2 < ... < a_7. We try to search recursively
    for each of a, at each recursion imposing a bound that is determined by the
    previous element.

    Consider element a_i with a >= 3. Then, the sum of the first j element
    starting from a_i, namely a_i + ... + a_{i + (j - 1)}, must be less than all
    subsets of (a_1, ..., a_{i - 1}) that has length j + 1 as imposed by the
    properties required of elements of A.

    But we only need to compare a_1 + ... + a_{i + (j - 1)} for the minimum
    length j + 1 subset of (a_1, ..., a_{i - 1}), which is exactly a_1 + ... +
    a_{j + 1}, to show that it is less than all length j + 1 subset of (a_1, ...,
    a_{i - 1}}).

    Hence, when considering the values that a_i can take, we start with a_i =
    a_{i - 1} + 1 (since a_i > a_{i - 1}), up to some value for a_i such that

        a_i + ... + a_{i + (j - 1)} < a_1 + ... + a_{j}

    Next, we need to weave our subset properties check into our recursion
    algorithm. We start at the top-most step of our algorithm, where we select
    the values for a_3. Suppose we have a previous list of subsets from {a_1,
    a_2}, namely {a_1}, {a_2}, {a_1, a_2}. We partition our subsets of {a_1,
    a_2, a_3} into two cases, those that do not contain a_3 and those that do.

    Subsets that do not contain a_3 must be subsets of {a_1, a_2}, which is
    exactly the previous list. Since this previous list has been checked such
    that the properties of pairs of disjoint subsets fulfil the required
    properties, we are done.

    Next, subsets that contain a_3. These are exactly the subsets of {a_1, a_2}
    extended with a_3. The subsets among this case all contain a_3, so there are
    no disjoint pairs among them.

    As such, we only need to check pairs of subset with one element coming from
    the subsets that do not contain a_3, and one coming from the subsets that
    contain a_3. For each disjoint pair, we check if the required properties
    hold true. If anyone pair fails, we reject the test value of a_3 and move on
    to the next test value.

    After the subset check, we concatenate the subsets not containing a_3, which
    are exactly the subset from the previous step, with the subsets containing
    a_3 and use this as the subsets list for our next step.

    Up till now, we have a recursive algorithm that, given A that only contains
    the first two numbers at the start, can extend A until it reaches length 7,
    while maintaining the properties required of disjoing subsets. We also limit
    the branching factor at each step based on our knowledge that the current
    element must be more than the previous element, and also from bounds implied
    by the required properties of disjoint subsets.

    Now, we need to iterate through pairs of numbers in order to select the
    first two items of A, in particular the smallest two items a_1, a_2. We do
    this by reverse pair iteration; That is, instead of selecting a in (a, b)
    and then selecting b such that (b > a), we select b in (a, b) and select b
    from 1, ..., a - 1.

    This is necessary because the forward iteration requires the set from which
    we select a, b to be finitely bounded (so that for a fixed a, we can test
    finish all possible values of b in finite time), but this is not the case.

    We collect the minimum sums produced for each starting numbers (a_1, a_2),
    if any. We stop when a_1 + (a_1 + 1) + ... + (a_1 + 6) is greater than the
    smallest minimum sum we have collected thus far, because going any further
    will cause the minimum sum to be greater than the smallest minimum sum we
    have collected and the result will always not replace our smallest minimum
    sum.
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>

bool check_end(std::vector<int> &A, std::vector<std::pair<int, int>> &end_checks, int length_check, int n)
{
    for (std::pair<int, int> &end_check : end_checks)
        if (end_check.first * n + end_check.second > std::accumulate(A.begin(), A.begin() + length_check + 1, 0))
            return false;
    return true;
}

bool check_subsets(std::vector<std::vector<int>> &subsets, int n, std::vector<std::vector<int>> &_subsets)
{
    for (std::vector<int> &subset : subsets)
    {
        _subsets.emplace_back(subset);
        _subsets.back().emplace_back(n);
    }
    for (std::vector<int> &_subset : _subsets)
    {
        int _subset_sum = std::accumulate(_subset.begin(), _subset.end(), 0);
        for (std::vector<int> &subset : subsets)
        {
            bool is_disjoint = true;
            for (const int &n : _subset)
            {
                if (std::binary_search(subset.begin(), subset.end(), n))
                {
                    is_disjoint = false;
                    break;
                }
            }
            if (!is_disjoint)
                continue;
            int subset_sum = std::accumulate(subset.begin(), subset.end(), 0);
            if (_subset_sum == subset_sum)
                return false;
            if (_subset.size() < subset.size() && _subset_sum >= subset_sum)
                return false;
            if (_subset.size() > subset.size() && _subset_sum <= subset_sum)
                return false;
        }
    }
    return true;
}

bool search(std::vector<int> &A, std::vector<std::vector<int>> subsets, int index)
{
    if (index == A.size())
        return true;

    int length_previous = index;
    std::vector<std::pair<int, int>> end_checks;
    int length_check = 1;
    for (; length_check < std::min(length_previous, (int)(A.size() - index + 1)); length_check++)
        end_checks.emplace_back(length_check, length_check * (length_check - 1) / 2);

    int n = index == 0 ? 1 : (A[index - 1] + 1);
    while (check_end(A, end_checks, length_check, n))
    {
        std::vector<std::vector<int>> _subsets;
        if (!check_subsets(subsets, n, _subsets))
        {
            n++;
            continue;
        }


        A[index] = n;
        _subsets.insert(_subsets.begin(), subsets.begin(), subsets.end());
        if (search(A, _subsets, index + 1))
            return true;
        n++;
    }
    return false;
}

bool get_minimum_sum(int item0, int item1, int n, std::pair<std::vector<int>, int> &sum)
{
    std::vector<int> _A(n);
    _A[0] = item0;
    _A[1] = item1;
    std::vector<std::vector<int>> _subsets{
        { },
        { item0 },
        { item1 },
        { item0, item1 }
    };

    if (!search(_A, _subsets, 2))
        return false;

    sum.first = _A;
    sum.second = std::accumulate(_A.begin(), _A.end(), 0);
    return true;
}

int main()
{
    int n = 7;
    bool has_minimum_sum = false;
    std::pair<std::vector<int>, int> minimum_sum;
    int item1 = 2;
    while (!has_minimum_sum || n * item1 + n * (n - 1) / 2 < minimum_sum.second)
    {
        int item0 = 1;
        while (item0 < item1 && (!has_minimum_sum || item0 + (n - 1) * item1 + (n - 1) * (n - 2) / 2 < minimum_sum.second))
        {
            std::pair<std::vector<int>, int> _minimum_sum;
            if (get_minimum_sum(item0, item1, 7, _minimum_sum))
            {
                if (!has_minimum_sum || _minimum_sum.second < minimum_sum.second)
                {
                    minimum_sum = _minimum_sum;
                    has_minimum_sum = true;
                }
            }
            item0++;
        }
        item1++;
    }

    std::string s = "";
    for (int &n : minimum_sum.first)
        s += std::to_string(n);
    std::cout << s;
}
