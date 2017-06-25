/*
    Reverse-delete algorithm.
    https://en.wikipedia.org/wiki/Reverse-delete_algorithm
*/

#include <string>
#include <numeric>
#include <unordered_set>
#include <deque>
#include <utility>
#include <algorithm>
#include <iostream>
#include "io_util.h"
#include "string_util.h"

typedef std::vector<std::vector<int>> matrix_type;
typedef std::pair<int, int> edge_type;

bool is_connected(matrix_type const &matrix)
{
    std::vector<int> vertices(matrix.size());
    std::iota(vertices.begin(), vertices.end(), 0);

    std::unordered_set<int> S;
    std::deque<int> Q;

    int root = *vertices.begin();
    vertices.erase(vertices.begin());
    S.emplace(root);
    Q.emplace_back(root);

    while (!Q.empty())
    {
        int current = Q.front();
        Q.pop_front();
        for(int &vertex : vertices)
        {
            if (S.find(vertex) == S.end() && matrix[current][vertex] != -1)
            {
                S.emplace(vertex);
                Q.emplace_back(vertex);
            }
        }
    }

    return S.size() == matrix.size();
}

int get_weight(matrix_type const &matrix)
{
    int s = 0;
    for (std::vector<int> const &row : matrix)
        for (int const &element : row)
            if (element != -1)
                s += element;
    return s / 2;
}

int find_minimum_weight(matrix_type const &matrix, std::vector<edge_type> const &edges, int index)
{
    int weight = get_weight(matrix);
    for (int i = index; i < edges.size(); i++)
    {
        edge_type edge = edges[i];
        matrix_type _matrix(matrix);
        _matrix[edges[i].first][edges[i].second] = -1;
        _matrix[edges[i].second][edges[i].first] = -1;
        if (is_connected(_matrix))
            return find_minimum_weight(_matrix, edges, i + 1);
    }
    return weight;
}

int main()
{
    std::string matrix_string = util::read_file("107_network.txt");
    matrix_type matrix;
    for (std::string &matrix_row_string : util::split(matrix_string, '\n'))
    {
        matrix.emplace_back();
        for (std::string &element_string : util::split(matrix_row_string, ','))
        {
            if (element_string == "-")
                matrix.back().emplace_back(-1);
            else
                matrix.back().emplace_back(std::stoi(element_string));
        }
    }

    std::vector<edge_type> edges;
    for (int r = 0; r < matrix.size(); r++)
    {
        for (int c = r + 1; c < matrix.size(); c++)
        {
            if (matrix[r][c] != -1)
                edges.emplace_back(r, c);
        }
    }
    std::sort(edges.begin(), edges.end(), [&matrix](edge_type const &A, edge_type const &B)
    {
        return matrix[A.first][A.second] > matrix[B.first][B.second];
    });

    std::cout <<  get_weight(matrix) - find_minimum_weight(matrix, edges, 0);
}
