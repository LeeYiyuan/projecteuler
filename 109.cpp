/*
    We use breadth first search for this.

    Start at the root node with an empty hit combination.

    At depth 1, we select the ending hit, which must be a double. These cases
    check out with one hit.

    At depth 2, we select the second hit, which can be anything. These cases check
    out with two hits.

    At depth 3, we select the final hit, which we take to be the element that is
    at least at the same position as the previously selected hit in some ordered
    list of possible hits. The cases check out with three hits.

    The total number of cases where score < 100 is summed.
*/

#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include <algorithm>

typedef std::pair<std::string, int> hit_type;

int get_value(hit_type &hit)
{
    return (hit.first == "S" ? 1 : hit.first == "D" ? 2 : 3) * hit.second;
}

int get_score(std::vector<hit_type> &combination)
{
    int sum = 0;
    for (hit_type &hit : combination)
        sum +=  get_value(hit);
    return sum;
}

int main()
{
    std::vector<hit_type> hits;

    std::vector<std::string> m_strings = { "S", "D", "T" };
    for (std::string &m : m_strings)
        for (int i = 1; i < 21; i++)
            hits.emplace_back(m, i);
    hits.emplace_back("S", 25);
    hits.emplace_back("D", 25);

    std::vector<std::vector<hit_type>> combinations;
    for (hit_type &hit : hits)
        if (hit.first == "D")
                combinations.emplace_back(1, hit);

    int count = combinations.size();

    for (int i = 0; i < 2; i++)
    {
        std::vector<std::vector<hit_type>> _combinations;
        for (std::vector<hit_type> &combination : combinations)
        {
            auto it_hit = hits.begin();
            if (i == 1)
                it_hit = std::find(hits.begin(), hits.end(), combination.back());
            for (; it_hit != hits.end(); ++it_hit)
            {
                hit_type &hit = *it_hit;
                _combinations.emplace_back(combination);
                _combinations.back().emplace_back(hit);
                if (get_score(_combinations.back()) < 100)
                    count++;
            }
        }
        combinations = _combinations;
    }

    std::cout << count;
}
