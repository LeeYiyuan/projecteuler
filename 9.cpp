#include <iostream>

int main()
{
    int sum = 1000;
    for (int a = 1; a < sum; a++)
    {
        for (int b = a + 1; b < sum - a; b++)
        {
            int c = 1000 - a - b;
            if (a * a + b * b == c * c)
            {
                std::cout << a * b * c;
                return 0;
            }
        }
    }
}
