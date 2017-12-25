/*
    We represent the problem as a graph traversal problem. Each node represents
    a coordinate in the matrix. A node corresponding to (r, c) is connected to
    the nodes corresponding to (r - 1, c), (r, c - 1), (r, c + 1), (r + 1, c).

    d(A, B) is given by the value of the matrix element corresponding to node B.

    The distance between A and B is non commutative, i.e. d(A, B) does not
    necessarily equal d(B, A).

    We start from the node corresponding to (0, 0) and look for the shortest
    path to the node corresponding to (79, 79). This is done using Dijkistra's.
    (https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm).

    We not have the minimum matrix path sum excluding initial element. We add
    back M(0, 0) to get the minimum path sum.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include "io_util.h"
#include "string_util.h"

typedef std::pair<int, int> node_t;

int get_length(std::vector<std::vector<int>> const &M, node_t const &u, node_t const &v)
{
    return M[v.first][v.second];
}

int compare_dist(int a, int b)
{
    if (a == -1 && b == -1)
        return 0;
    if (a != -1 && b == -1)
        return -1;
    if (a == -1 && b != -1)
        return 1;
    if (a > b)
        return 1;
    if (a == b)
        return 0;
    if (a < b)
        return -1;
}

std::vector<node_t> get_neighbours(std::vector<std::vector<int>> const &M, node_t const &v)
{
    int r = v.first;
    int c = v.second;
    std::vector<node_t> neighbours;

    if (r > 0)
        neighbours.emplace_back(r - 1, c);
    if (r < M.size() - 1)
        neighbours.emplace_back(r + 1, c);
    if (c > 0)
        neighbours.emplace_back(r, c - 1);
    if (c < M.size() - 1)
        neighbours.emplace_back(r, c + 1);

    return neighbours;
}

int main()
{
    std::string matrix_string = util::read_file("083_matrix.txt");
    std::vector<std::vector<int>> M;
    for (std::string &matrix_row_string : util::split(matrix_string, '\n'))
    {
        M.emplace_back();
        for (std::string &n_string : util::split(matrix_row_string, ','))
        {
            M.back().emplace_back(std::stoi(n_string));
        }
    }

    std::vector<node_t> Q;
    std::map<node_t, int> dist;
    std::map<node_t, node_t> prev;
    node_t source(0, 0);

    for(int r = 0; r < M.size(); r++)
    {
        for (int c = 0; c < M.size(); c++)
        {
            Q.emplace_back(r, c);
            node_t &v = Q.back();
            dist[v] = -1;
            prev[v] = node_t(-1, -1);
        }
    }
    dist[source] = 0;

    while (Q.size() > 0)
    {
        node_t u(-1, -1);
        for (node_t &v : Q)
            if (u == node_t(-1, -1) || compare_dist(dist[v], dist[u]) == -1)
                u = v;
        Q.erase(std::remove(Q.begin(), Q.end(), u), Q.end());

        for (node_t &v : get_neighbours(M, u))
        {
            if (std::find(Q.begin(), Q.end(), v) != Q.end())
            {
                int alt = dist[u] + get_length(M, u, v);
                if (compare_dist(alt, dist[v]) == -1)
                {
                    dist[v] = alt;
                    prev[v] = u;
                }
            }
        }
    }

    std::cout << dist[node_t(M.size() - 1, M.size() - 1)] + M[source.first][source.second];
}
