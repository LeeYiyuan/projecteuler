#include <iostream>
#include "number_util.h"

int main()
{
    int lcm = 1;
    for (int i = 2; i < 20; i++)
    {
        lcm = (lcm * i) / gcd(lcm, i);
    }

    std::cout << lcm;
}
