#pragma once

#include <vector>
#include <gmpxx.h>

namespace util
{
    struct pell_solution
    {
        mpz_class x, y;

        pell_solution();
        pell_solution(mpz_class x, mpz_class y);
    };

    class pell_PQa_algorithm
    {
    public:
        mpz_class P_0, Q_0, D;
        mpf_class D_sqrt;
        mpz_class i = -1;
        std::vector<mpz_class> P, Q, a, A = { 0, 1 }, B = { 1, 0 }, G;

        void init(mpz_class P_0, mpz_class Q_0, mpz_class D);
        pell_PQa_algorithm();
        pell_PQa_algorithm(mpz_class P_0, mpz_class Q_0, mpz_class D);
        void move_next();
        bool has_repeated();
    };

    std::vector<pell_solution> LMM_algorithm(mpz_class D, mpz_class N);

    class pell_solver
    {
    public:
        mpz_class D, N;
        pell_solution solution;

        void init(mpz_class D, mpz_class N);
        pell_solver();
        pell_solver(mpz_class D, mpz_class N);
        bool move_next();

    private:
        bool has_solution;
        pell_solution unit_fundamental;
        std::vector<pell_solution> fundamentals;
        std::vector<pell_solution> unit_solutions;
        std::vector<pell_solution> solutions;
    };
}
