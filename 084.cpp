/*
    This solution use random playouts to determine the frequencies of each square.

    First start with a hits counter for each of the square.

    We play 20000 matches, each for a total of 8000 rounds. (A multiple of 16 is
    chosen to make sure to eliminate bias in the CC and CH carts although I am
    not sure how much this helps).

    Each match starts with its own shuffled list of CC and CH cards. Each match
    starts at step 0.
    For each round, we simulate the gameplay and roll two random numbers to
    determine the eventual square after applying all the rules. The hits counter
    for that particular square is incremented by 1.

    After all the matches, we pick the three squares with the top most hits.
*/

#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <functional>
#include <algorithm>
#include <string>

std::vector<int> trial(std::mt19937 &mt, std::uniform_int_distribution<int> &dis)
{
    auto rand = std::bind(dis, mt);

    std::vector<int> hits(40);
    int doubles_count = 0;
    std::vector<int> community_chest = { 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    std::vector<int> chance = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0 };
    std::vector<int> railway = { 5, 15, 25, 35 };
    std::vector<int> utility = { 12, 28 };
    std::shuffle(community_chest.begin(), community_chest.end(), mt);
    std::shuffle(chance.begin(), chance.end(), mt);
    int step = 0;

    for (int t = 0; t < 8000; t++)
    {
        int roll1 = rand();
        int roll2 = rand();

        if (roll1 == roll2)
            doubles_count++;
        else
            doubles_count = 0;

        if (doubles_count == 3) // Go to jail for consecutive doubles.
        {
            step = 10;
            doubles_count = 0;
        }
        else
        {
            step = (step + roll1 + roll2) % 40; // Advance.

            if (step == 30) // G2J.
            {
                step = 10;
            }
            else if (step == 2 || step == 17 || step == 33) // Community chest.
            {
                int c = community_chest[0];
                std::rotate(community_chest.begin(), community_chest.begin() + 1, community_chest.end());

                if (c == 1) // Advance to GO.
                {
                    step = 0;
                }
                else if (c == 2) // Go to jail.
                {
                    step = 10;
                }
            }
            else if (step == 7 || step == 22 || step == 36) // Chance.
            {
                int c = chance[0];
                std::rotate(chance.begin(), chance.begin() + 1, chance.end());

                if (c == 1) // Advance to GO.
                {
                    step = 0;
                }
                else if (c == 2) // Go to jail.
                {
                    step = 10;
                }
                else if (c == 3) // Go to C1.
                {
                    step = 11;
                }
                else if (c == 4) // Go to E3.
                {
                    step = 24;
                }
                else if (c == 5) // Go to H2.
                {
                    step = 39;
                }
                else if (c == 6) // Go to R1.
                {
                    step = 5;
                }
                else if (c == 7 || c == 8) // Go to the next R.
                {
                    int i_r = 0;
                    for (; i_r < railway.size() && railway[i_r] <= step; i_r++);
                    step = railway[i_r % railway.size()];
                }
                else if (c == 9) // Go to the next U.
                {
                    int i_u = 0;
                    for (; i_u < utility.size() && utility[i_u] <= step; i_u++);
                    step = utility[i_u % utility.size()];
                }
                else if (c == 10) // Go back 3 squares.
                {
                    step = (step - 3) % 40;
                    if (step == 2 || step == 17 || step == 33) // Community chest.
                    {
                        int _c = community_chest[0];
                        std::rotate(community_chest.begin(), community_chest.begin() + 1, community_chest.end());

                        if (_c == 1) // Advance to GO.
                        {
                            step = 0;
                        }
                        else if (_c == 2) // Go to jail.
                        {
                            step = 10;
                        }
                    }
                }
            }
        }
        hits[step]++;
    }

    return hits;
}

int main()
{
    std::vector<int> hits(40);
    std::mt19937 mt(time(0));
    std::uniform_int_distribution<int> dis(1, 4);
    for (int t = 0; t < 20000; t++)
    {
        std::vector<int> _hits = trial(mt, dis);
        std::transform(hits.begin(), hits.end(), _hits.begin(), hits.begin(), std::plus<int>());
    }

    std::vector<int> hits_largest(3, -1);
    std::vector<int> i_largest(3, -1);
    for (int i = 0; i < hits.size(); i++)
    {
        int hit = hits[i];
        int j = 0;
        for (; j < hits_largest.size() && hit < hits_largest[j]; j++);
        if (j < hits_largest.size())
        {
            for (int k = hits_largest.size() - 1; k > j; k--)
            {
                hits_largest[k] = hits_largest[k - 1];
                i_largest[k] = i_largest[k - 1];
            }
            hits_largest[j] = hit;
            i_largest[j] = i;
        }
    }

    std::string result = "";
    for (int &i : i_largest)
        result += (i < 10 ? "0" : "") + std::to_string(i);

    std::cout << result;
}
