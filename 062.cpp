/*
    Define a digit vector v_n of a number n as a length 10 tuple where v_i is
    the number of occurences of the digit i in n, where leading zeros are
    ignored. Define the count of v_n to be the sum of the elements in v_n, which
    is exactly the number of digits in n.

    We maintain a map of digit vectors to a (count, min_cube) pair. For every
    cube n^3 starting from n = 1, we update the map entry corresponding to v_n
    by incrementing count by 1 and setting min_cube to the the minimum between
    the previous value of min_cube and n^3. Equivalently, since n is increasing,
    we record the min_cube of every digit vector as the first n^3 with that
    digit vector.

    We stop when we get a digit vector with count = 5.

    Notice that we have not shown that the digit vector whose count first
    reaches 5 gives the min_cube that is minimal across all digit vectors whose
    count will subsequently reach 5. In fact, we haven't even shown that the
    digit vector count will remain at exactly 5 and not grow anymore (there
    could be larger cubes with the same digit vector)!

    Fortunately however, the first digit vector whose count hits 5 has min_cube
    that is the correct answer.
*/

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <map>
#include <algorithm>

std::vector<int> get_digit_vector(unsigned long long n)
{
    std::vector<int> v(10);
    for (char &digit : std::to_string(n))
        v[digit - '0']++;
    return v;
}

int main()
{
    std::map<std::vector<int>, std::vector<unsigned long long>> digit_vectors;

    unsigned long long n = 1;
    while (true)
    {
        unsigned long long cube = n * n * n;
        std::vector<int> v = get_digit_vector(cube);
        auto it = digit_vectors.find(v);
        if (it == digit_vectors.end())
            it = digit_vectors.emplace(v, std::vector<unsigned long long>{ 0, cube }).first;
        it->second[0]++;
        if (it->second[0] == 5)
        {
            std::cout << it->second[1];
            return 0;
        }
        n++;
    }
}
