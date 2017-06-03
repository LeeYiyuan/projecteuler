/*
    This question is just...
*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <tuple>
#include "io_util.h"
#include "string_util.h"

std::map<char, int> card_values = {
    { '2', 0 },
    { '3', 1 },
    { '4', 2 },
    { '5', 3 },
    { '6', 4 },
    { '7', 5 },
    { '8', 6 },
    { '9', 7 },
    { 'T', 8 },
    { 'J', 9 },
    { 'Q', 10 },
    { 'K', 11 },
    { 'A', 12 }
};

// Son of a b!tch.
std::tuple<int, int, int, int, int, int> get_hand_value(std::vector<std::string> &hand)
{
    std::tuple<int, int, int, int, int, int> max_value = std::make_tuple(-1, -1, -1, -1, -1, -1);

    std::vector<int> values;
    for (std::string &card : hand)
        values.emplace_back(card_values[card[0]]);

    bool is_straight =
        card_values[hand[0][0]] == card_values[hand[1][0]] - 1 &&
        card_values[hand[1][0]] == card_values[hand[2][0]] - 1 &&
        card_values[hand[2][0]] == card_values[hand[3][0]] - 1 &&
        card_values[hand[3][0]] == card_values[hand[4][0]] - 1;
    bool is_flush =
        hand[0][1] == hand[1][1] &&
        hand[1][1] == hand[2][1] &&
        hand[2][1] == hand[3][1] &&
        hand[3][1] == hand[4][1];

    if (is_straight && is_flush)
    {
        if (hand[0][0] == 'T')
            max_value = std::max(max_value, std::make_tuple(10, values[4], -1, -1, -1, -1));

        // If same rank, compare high card.
        max_value = std::max(max_value, std::make_tuple(9, values[4], -1, -1, -1, -1));
    }
    else if (is_flush)
    {
        // If same rank, compare highest card, then second highest, etc.
        max_value = std::max(max_value, std::make_tuple(6, values[4], values[3], values[2], values[1], values[0]));
    }
    else if (is_straight)
    {
        // If same rank, compare highest card.
        max_value = std::max(max_value, std::make_tuple(5, values[4], -1, -1, -1, -1));
    }

    // Check four of a kind.
    if (hand[0][0] == hand[1][0] && hand[1][0] == hand[2][0] && hand[2][0] == hand[3][0])
        max_value = std::max(max_value, std::make_tuple(8, values[0], -1, -1, -1, -1));
    if (hand[1][0] == hand[2][0] && hand[2][0] == hand[3][0] && hand[3][0] == hand[4][0])
        max_value = std::max(max_value, std::make_tuple(8, values[1], -1, -1, -1, -1));

    // Check full house.
    if (hand[0][0] == hand[1][0] && hand[1][0] == hand[2][0] && hand[3][0] == hand[4][0])
        max_value = std::max(max_value, std::make_tuple(7, values[0], values[3], -1, -1, -1));
    if (hand[1][0] == hand[2][0] && hand[2][0] == hand[3][0] && hand[0][0] == hand[4][0])
        max_value = std::max(max_value, std::make_tuple(7, values[1], values[0], -1, -1, -1));
    if (hand[2][0] == hand[3][0] && hand[3][0] == hand[4][0] && hand[0][0] == hand[1][0])
        max_value = std::max(max_value, std::make_tuple(7, values[2], values[0], -1, -1, -1));

    // Check three of a kind.
    if (hand[0][0] == hand[1][0] && hand[1][0] == hand[2][0])
        max_value = std::max(max_value, std::make_tuple(4, values[0], values[4], values[3], -1, -1));
    if (hand[1][0] == hand[2][0] && hand[2][0] == hand[3][0])
        max_value = std::max(max_value, std::make_tuple(4, values[1], values[4], values[0], -1, -1));
    if (hand[2][0] == hand[3][0] && hand[3][0] == hand[4][0])
        max_value = std::max(max_value, std::make_tuple(4, values[2], values[1], values[0], -1, -1));

    // Check two pairs.
    if (hand[0][0] == hand[1][0] && hand[2][0] == hand[3][0])
        max_value = std::max(max_value, std::make_tuple(3, values[2], values[0], values[4], -1, -1));
    if (hand[0][0] == hand[1][0] && hand[3][0] == hand[4][0])
        max_value = std::max(max_value, std::make_tuple(3, values[3], values[0], values[2], -1, -1));
    if (hand[1][0] == hand[2][0] && hand[3][0] == hand[4][0])
        max_value = std::max(max_value, std::make_tuple(3, values[3], values[1], values[0], -1, -1));

    // Check one pair.
    if (hand[0][0] == hand[1][0])
        max_value = std::max(max_value, std::make_tuple(2, values[0], values[4], values[3], values[2], -1));
    if (hand[1][0] == hand[2][0])
        max_value = std::max(max_value, std::make_tuple(2, values[1], values[4], values[3], values[0], -1));
    if (hand[2][0] == hand[3][0])
        max_value = std::max(max_value, std::make_tuple(2, values[2], values[4], values[1], values[0], -1));
    if (hand[3][0] == hand[4][0])
        max_value = std::max(max_value, std::make_tuple(2, values[3], values[2], values[1], values[0], -1));

    // Nothing.
    max_value = std::max(max_value, std::make_tuple(1, values[4], values[3], values[2], values[1], values[0]));

    return max_value;
}

int main()
{
    std::string hands_string = read_file("54_poker.txt");

    int count = 0;
    for (std::string &hand_string : split(hands_string, '\n'))
    {
        std::vector<std::string> cards = split(hand_string, ' ');

        std::vector<std::string> hand_a = { cards[0], cards[1], cards[2], cards[3], cards[4] };
        std::vector<std::string> hand_b = { cards[5], cards[6], cards[7], cards[8], cards[9] };

        std::sort(hand_a.begin(), hand_a.end(), [](std::string const &card_a, std::string const &card_b) -> bool
        {
            return card_values[card_a[0]] < card_values[card_b[0]];
        });
        std::sort(hand_b.begin(), hand_b.end(), [](std::string const &card_a, std::string const &card_b) -> bool
        {
            return card_values[card_a[0]] < card_values[card_b[0]];
        });

        if (get_hand_value(hand_a) > get_hand_value(hand_b))
            count++;
    }

    std::cout << count;
}
