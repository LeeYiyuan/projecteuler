/*
    Naive estimation of the expected value by sampling random playouts is
    extremely slow. After 100M playouts which took around 15 minutes, the
    estimated mean has converged only up to 4 decimal digits (even then, the 3rd
    decimal digit still fluctuates occasionally).

    Notice that the problem can be formulated as a Markov chain. Define a state
    as a length 4 tuple (a2, a3, a4, a5) where a2, a3, a4, a5 is the number of
    A2, A3, A4 and A5 sheets respectively. Notice that we are only starting from
    the end of the first batch, whose state is equal to the start of the next
    batch.

    One may observe that a2 <= 1, a3 <= 2, a4 <= 4, a5 <= 8. Hence, including 0,
    there are at most 2 * 3 * 5 * 9 = 270 posible states. Initially, we generate
    a transition table that maps a probability to the transition from each
    possible state to another.

    At the start of batch 2, the state probabilities are 1 for (1, 1, 1, 1) and
    0 for everything else.

    At the start of each batch, the expected number of times a single sheet of
    paper is left is given by the sum of probabilities of states whose element
    sum is exactly 1, or states whose elements are all zero, except for exactly
    one that is 1.

    At the start of each batch, we take the state probabilties map it through
    the transition table and do some summation to get the state probabilities
    after the batch.

    One may use vectors and matrices for the state probability transformations,
    but I was afraid the transition matrix will be sparse and decided to tackle
    this from a more functional point of view instead.
*/

#include <map>
#include <vector>
#include <iostream>
#include <numeric>
#include <iomanip>

int main()
{
    std::map<std::vector<int>, std::map<std::vector<int>, double>> transition_probabilities;
    for (int a2 = 0; a2 < 2; a2++)
    {
        for (int a3 = 0; a3 < 3; a3++)
        {
            for (int a4 = 0; a4 < 5; a4++)
            {
                for (int a5 = 0; a5 < 9; a5++)
                {
                    std::vector<int> state = { a2, a3, a4, a5 };
                    int next_states_count = a2 + a3 + a4 + a5;
                    if (a2 != 0)
                        transition_probabilities[state][{ a2 - 1, a3 + 1, a4 + 1, a5 + 1 }] = double(a2) / next_states_count;
                    if (a3 != 0)
                        transition_probabilities[state][{ a2, a3 - 1, a4 + 1, a5 + 1 }] = double(a3) / next_states_count;
                    if (a4 != 0)
                        transition_probabilities[state][{ a2, a3, a4 - 1, a5 + 1 }] = double(a4) / next_states_count;
                    if (a5 != 0)
                        transition_probabilities[state][{ a2, a3, a4, a5 - 1 }] = double(a5) / next_states_count;
                }
            }
        }
    }

    std::map<std::vector<int>, double> probabilities;
    probabilities[{ 1, 1, 1, 1 }] = 1;

    double expected = 0;
    for (int i = 0; i < 14; i++)
    {
        for (auto &pair : probabilities)
            if (std::accumulate(pair.first.begin(), pair.first.end(), 0) == 1)
                expected += probabilities[pair.first];
        std::map<std::vector<int>, double> _probabilities;
        for (auto &pair : probabilities)
            for (auto &pair_next : transition_probabilities[pair.first])
                _probabilities[pair_next.first] += pair.second * pair_next.second;
        probabilities = std::move(_probabilities);
    }

    std::cout << std::setprecision(6) << expected;
}
