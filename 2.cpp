#include <iostream>

int main()
{
    int prev = 1;
    int curr = 1;
    int s = 0;

    while (curr <= 4000000)
    {
        if (curr % 2 == 0)
            s += curr;
        curr = prev + curr;
        prev = curr - prev;
    }

    std::cout << s;
}
