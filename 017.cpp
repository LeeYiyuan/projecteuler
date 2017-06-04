#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> ones = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };
    std::vector<std::string> tens = { "", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
    std::vector<std::string> special = { "", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };

    int sum_length = 0;
    for (int i = 1; i < 1000; i++)
    {
        int hundreds_digit = i / 100;
        int tens_digit = (i % 100) / 10;
        int ones_digit = i % 10;

        std::string text = "";
        if (hundreds_digit > 0)
        {
            text += ones[hundreds_digit] + "Hundred";
            if (tens_digit > 0 || ones_digit > 0)
                text += "And";
        }
        if (tens_digit == 1)
        {
            if (ones_digit == 0)
                text += tens[1];
            else
                text += special[ones_digit];
        }
        else
        {
            if (tens_digit > 0)
                text += tens[tens_digit];
            if (ones_digit > 0)
                text += ones[ones_digit];
        }
        sum_length += text.length();
    }
    sum_length += std::string("OneThousand").length();

    std::cout << sum_length;
}
