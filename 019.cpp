#include <iostream>
#include <vector>

int main()
{
    std::vector<int> number_of_days = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    int current_year = 1901;
    int first_day = 365 % 7;

    int count = 0;
    while (current_year <= 2000)
    {
        for (int month = 0; month < number_of_days.size(); month++)
        {
            if (first_day == 6)
                count++;

            first_day += number_of_days[month];

            if (month == 1)
                //Leap year occurs on years evenly divisible by 4, but not on a century unless
                //it is divisible by 400.
                if (current_year % 4 == 0 && (current_year % 100 != 0 || current_year % 400 == 0))
                    first_day++;

            first_day %= 7;
        }
        current_year++;
    }

    std::cout << count;
}
