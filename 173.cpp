/*
    For each possible inner square with width a, we calculate the number of 
    outlines possible, which is trivial: we only need count how many positive 
    integers i there are such that

        (a + 2i)^2 - a^2 <= n
    
    where n is the number of tiles given. We can obtained a closed form for
    this:
        
        1 <= i <= (\sqrt(n + a^2) - a) / 2
    
    and we sum the number of solutions across a while 4a + 4 <= n, because
    4a + 4 <= (a + 2i)^2 - a^2; When 4a + 4 exceeds n, there are no cases at
    all.
*/

#include <iostream>
#include <cmath>
#include <cstdint>

int main()
{
    int n = 1000000;
    uint64_t c = 0;
    for (uint64_t a = 1; 4 * a + 4 <= n; a++)
        c += uint64_t((std::sqrt(n + a * a) - a) / 2);

    std::cout << c;
}