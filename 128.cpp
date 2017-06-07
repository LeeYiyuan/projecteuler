/*
    Interesting. By brute forcing through the first few rings, one can notice that
    PD(3) only occurs either at the start or end of the rings and nowhere else. We
    can prove this conjecture. There are two cases for the numbers.

    Firstly, suppose n lies on some vertex k = 0, 1, ..., 5 of ring r, with k = 0
    running from the top most vertex anti-clockwise.

    Then n is given by 2 + 3r(r - 1) + kr. The neighbours on ring r + 1 are then
    2 + 3(r + 1)r + k(r + 1) + {-1, 0, 1}. The differences are then

        6r + k - 1, 6r + k, 6r + k + 1

    Now, we consider the differences util::modulo 2 and 3 for the possible values of k. For
    util::modulo 2 and 3, the 6r term is annihilated so we only have to worry about the k
    and constant terms.

        k   (k - 1) % 2   k % 2   (k + 1) % 2   (k - 1) % 3   k % 3   (k + 1) % 3
       ---------------------------------------------------------------------------
        0        1          0          1             2          0          1
        1        0          1          0             0          1          2
        2        1          0          1             1          2          0
        3        0          1          0             2          0          1
        4        1          0          1             0          1          2
        5        0          1          0             1          2          0

    It turns out that for k = 1, ..., 5, there are at least two differences that
    are each divisible by either 2 or 3. On the other hand, when k = 0, there
    are two differences that are divisible by neither 2 or 3. As such, out of the
    three neighbours in ring r + 1, there will be at most one prime difference
    except when n is on the top most vertex, in which case there can be up to two
    prime differences.

    Moving on, we see that the maximum PD(n) is contributed by:

        - The consecutive differences between n and the 3 consecutive neighbours on
          ring r + 1. As discussed earlier, this is at most 1 if n does not lie
          on the top most vertex of ring r, and at most 2 if it does.
        - If n does not lies on the top most vertex, there is no prime difference
          between n and the number before and after n on ring r, because these
          differences are exactly 1 which is not prime. However, if n lies on the
          top most vertex then there can be at most 1 prime difference contributed
          by the previous element which "wraps around" to the last element of the
          ring.
        - There is at most one prime difference from the neighbour on ring r - 1 if
          k = 1, 3, 5. However, if n lies on vertex k = 0, 2, 4, where 0 is the top
          most vertex, then the neighbour from ring r - 1 is exactly
          n' = 2 + 3(r - 1)(r) + kr. Either one of the consecutive r - 1, r must \
          be divisible by 2. Furthermore,  2 | k. Hence 2 | n' if n lies on vertex
          0, 2, or 4, leading to no prime differences (both n and the neighbour
          from ring r - 1 are even, so their difference is even).

    In all, PD(n) <= 1 + 0 + 1 = 2 if n does not lie on the top most vertex,
    and PD(n) <= 2 + 1 + 0 = 3 if n lies on the top most vertex. Hence we only
    need to check the top most vertices of the rings.



    Secondly, suppose n lies on some edge on ring r, and n is not the last element
    of the ring. The maximum PD(n) is contributed by:

        - The two consecutive neighbours on ring r + 1. The difference between n
          and these two neighbours are consecutive, and thus only one of them can
          be odd. Hence there is at most 1 prime difference.
        - The number before and after n on ring r. The differences are 1 which is
          not prime.
        - The two consecutive neighbours on ring r - 1. The difference between n
          and these two neighbours are again consecutive, and thus only one ot them
          can be odd. Therefore there is at most 1 prime difference.

    Hence, PD(n) = 2 whenever n lies on some edge and is not equal to the last
    element. The only way PD(n) for an edge n can be equal to 3 is if n is the
    last element of ring r, in which case the number after n on ring r is not 1
    away from n; Rather, the number after n "wraps around" the ring to provide a
    possible prime difference of more than 1.



    We have thus proved that there is only a need to check the top most vertex and the
    last element of each ring.
*/

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include "prime_util.h"
#include "number_util.h"

typedef signed long long ll;
typedef std::pair<ll, ll> node_type;

ll get_number(ll r, ll i)
{
    return 2 + 3 * r * (r - 1) + i;
}

std::vector<node_type> get_neighbours(ll r, ll i)
{
    std::vector<node_type> results;
    ll f = i / r;
    if (i % r != 0)
    {
        results.emplace_back(r - 1, util::mod(f * (r - 1) + (i - f * r) - 1, 6 * (r - 1)));
        results.emplace_back(r - 1, util::mod(f * (r - 1) + (i - f * r), 6 * (r - 1)));
        results.emplace_back(r, util::mod(i - 1, 6 * r));
        results.emplace_back(r, util::mod(i + 1, 6 * r));
        results.emplace_back(r + 1, util::mod(f * (r + 1) + (i - f * r), 6 * (r + 1)));
        results.emplace_back(r + 1, util::mod(f * (r + 1) + (i - f * r) + 1, 6 * (r + 1)));
    }
    else
    {
        results.emplace_back(r - 1, util::mod(f * (r - 1), 6 * (r - 1)));
        results.emplace_back(r, util::mod(i - 1, 6 * r));
        results.emplace_back(r, util::mod(i + 1, 6 * r));
        results.emplace_back(r + 1, util::mod(f * (r + 1) - 1, 6 * (r + 1)));
        results.emplace_back(r + 1, util::mod(f * (r + 1), 6 * (r + 1)));
        results.emplace_back(r + 1, util::mod(f * (r + 1) + 1, 6 * (r + 1)));
    }
    return results;
}

int PD(ll r, ll i)
{
    int count = 0;
    ll n = get_number(r, i);
    for (node_type &neighbour : get_neighbours(r, i))
    {
        ll n_neighbour = get_number(neighbour.first, neighbour.second);
        ll diff = n > n_neighbour ? (n - n_neighbour) : (n_neighbour - n);
        if (util::is_prime(diff))
            count++;
    }
    return count;
}

int main()
{
    // PD(1) = 3, PD(2) = 3.
    ll index = 2;
    ll r = 2;
    while (true)
    {
        std::vector<ll> values_i = { 0, 6 * r - 1 };
        for (ll &i : values_i)
        {
            if (PD(r, i) == 3)
            {
                index++;
                if (index == 2000)
                {
                    std::cout << get_number(r, i);
                    return 0;
                }
            }
        }
        r++;
    }
}
