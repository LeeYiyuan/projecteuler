#include <iostream>
#include <string>
#include "string_util.h"

int main()
{
    int largest = 0;
    for (int a = 900; a < 1000; a++)
    {
        for (int b = 900; b < 1000; b++)
        {
            int n = a * b;
            if (is_palindrome(std::to_string(n)) and n > largest)
                largest = n;
        }
    }

    std::cout << largest;
}
