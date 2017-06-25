/*
    This solution draws ideas from how genetic algorithms can be used to
    determine combinations of operators and values to give some selected number.

    We consider arithmetic operations in Polish notation. We have a set of
    operators, A = {'.', '+', '-', '*', '/'} where '.' refers to a unary
    operator that maps a number to itself.

    First we start with a tuple ('+') corresponding to the outer most operator.
    We expand this tuple by selecting the possible pairs of second outer most
    operators, i.e. we expand (+) to one of

        (+(.)(+))   (+(.)(-))   (+(.)(*))   (+(.)(/))   (+(.)(.))
        (+(+)(+))   (+(+)(-))   (+(+)(*))   (+(+)(/))   (+(+)(.))
        (+(-)(+))   (+(-)(-))   (+(-)(*))   (+(-)(/))   (+(-)(.))
        (+(*)(+))   (+(*)(-))   (+(*)(*))   (+(*)(/))   (+(*)(.))
        (+(/)(+))   (+(/)(-))   (+(/)(*))   (+(/)(/))   (+(/)(.))

    Next, we move on to expand the sub operators, in this case the last two
    operators. For (+(-)(*)), we expand (-) and (*), giving results such as

        (+(-(.)(.)) (*(.)(.)))

    A tuple is said to be fully expanded when it cannot be expanded anymore,
    i.e. when the innermost operators at each depth is '.'. Examples are

        (+(.)(.))
        (+(+(.)(.)))

    Note we need expansion with "length" 4. These are full expansions with 4 '.',
    for which we can slot a, b, c, d into.

    With our expressions table, we try out all combinations of a < b < c < d.
    For each combination, we evaluate the expressions in the expressions table
    with values that are permutations of (a, b, c, d) and collect the integer
    results (of course catching divide by zero errors and discarding such
    cases).

    Finally, we pick the combination that gives the most consecutive first
    positive integers.
*/

#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <cmath>
#include "iter_util.h"

std::vector<std::string> ops = { ".", "+", "-", "/", "*" };

std::vector<std::string> get_exprs(std::string op, int length)
{
    std::vector<std::string> exprs;

    if (op == ".")
    {
        if (length == 1)
            exprs.emplace_back("(.)");
        else
            return exprs;
    }

    if (length < 2)
        return exprs;

    for (int length_left = 1; length_left < length; length_left++)
    {
        int length_right = length - length_left;
        std::vector<std::string> exprs_left, exprs_right;
        for (std::string &_op : ops)
        {
            for (std::string &expr : get_exprs(_op, length_left))
                exprs_left.emplace_back(expr);
            for (std::string &expr : get_exprs(_op, length_right))
                exprs_right.emplace_back(expr);
        }
        for (std::string &expr_left : exprs_left)
            for (std::string &expr_right : exprs_right)
                exprs.emplace_back("(" + op + expr_left + expr_right + ")");
    }
}

std::string substitute(std::string expr, std::vector<int> const &digits)
{
    std::string _expr = expr;
    for (int const &d : digits)
        _expr.replace(_expr.find('.'), 1, 1, (char)(d + '0'));
    return _expr;
}

double evaluate(std::string expr)
{
    if (expr[1] - '0' >= 0 && expr[1] - '0' <= 9)
        return expr[1] - '0';

    std::string op(1, expr[1]);
    std::string expr_left;
    std::string expr_right;

    int count = 1;
    int start = 2;
    int end = start + 1;
    while (count > 0)
    {
        if (expr[end] == '(') count++;
        else if (expr[end] == ')') count--;
        end++;
    }
    expr_left = expr.substr(start, end - start);

    count = 1;
    start = end++;;
    while (count > 0)
    {
        if (expr[end] == '(') count++;
        else if (expr[end] == ')') count--;
        end++;
    }
    expr_right = expr.substr(start, end - start);

    double val_left = evaluate(expr_left);
    double val_right = evaluate(expr_right);

    if (op == "+") return val_left + val_right;
    if (op == "-") return val_left - val_right;
    if (op == "*") return val_left * val_right;
    if (op == "/") return val_left / val_right;

    return 0;
}

int main()
{
    std::vector<std::string> exprs;
    std::vector<std::string> _ops = { "+", "-", "/", "*" };
    for (std::string &op : _ops)
    {
        std::vector<std::string> _exprs = get_exprs(op, 4);
        exprs.insert(exprs.end(), _exprs.begin(), _exprs.end());
    }

    std::string digits_best;
    int length_best = -1;

    std::vector<int> valid_digits = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    for (std::vector<int> &digits : util::get_combinations(valid_digits.begin(), valid_digits.end(), 4))
    {
        std::set<int> values;

        do
        {
            for (std::string &expr : exprs)
            {
                std::string expr_sub = substitute(expr, digits);
                double value = evaluate(expr_sub);
                if (!std::isinf(value) && std::fmod(value, 1) == 0)
                    values.emplace(value);
            }
        } while (std::next_permutation(digits.begin(), digits.end()));

        int length = 0;
        for (; values.find(length + 1) != values.end(); length++);

        if (length > length_best)
        {
            digits_best = "";
            for (int &d : digits)
                digits_best += d + '0';
            length_best = length;
        }
    }

    std::cout << digits_best;
}
