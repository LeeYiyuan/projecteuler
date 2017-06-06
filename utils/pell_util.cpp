#include "pell_util.h"
#include <vector>
#include <gmpxx.h>
#include <gmp.h>
#include <cmath>

/*
    Algorithm(s) taken from:
    "Solving the generalized Pell equation x2 - Dy2 = N" (John P. Robertson, 2004)
    http://www.jpr2718.org/pell.pdf
*/

util::pell_solution::pell_solution()
{

}

util::pell_solution::pell_solution(mpz_class x, mpz_class y)
{
    this->x = x;
    this->y = y;
}





void util::pell_PQa_algorithm::init(mpz_class P_0, mpz_class Q_0, mpz_class D)
{
    this->P_0 = P_0;
    this->Q_0 = Q_0;
    this->D = D;
    D_sqrt = sqrt(mpf_class(D));
    G.emplace_back(-P_0);
    G.emplace_back(Q_0);
}

util::pell_PQa_algorithm::pell_PQa_algorithm()
{

}

util::pell_PQa_algorithm::pell_PQa_algorithm(mpz_class P_0, mpz_class Q_0, mpz_class D)
{
    init(P_0, Q_0, D);
}

void util::pell_PQa_algorithm::move_next()
{
    i++;
    mpz_class P_i, Q_i;
    if (i == 0)
    {
        P_i = P_0;
        Q_i = Q_0;
    }
    else
    {
        P_i = a[a.size() - 1] * Q[Q.size() - 1] - P[P.size() - 1];
        Q_i = (D - P_i * P_i) / Q[Q.size() - 1];
    }

    mpz_class a_i = mpz_class((mpf_class(P_i) + D_sqrt) / mpf_class(Q_i));
    mpz_class A_i = a_i * A[A.size() - 1] + A[A.size() - 2];
    mpz_class B_i = a_i * B[B.size() - 1] + B[B.size() - 2];
    mpz_class G_i = a_i * G[G.size() - 1] + G[G.size() - 2];

    P.emplace_back(P_i);
    Q.emplace_back(Q_i);
    a.emplace_back(a_i);
    A.emplace_back(A_i);
    B.emplace_back(B_i);
    G.emplace_back(G_i);
}

/*
    Checks if the PQa algorithm has repeated by looking at the values of P, Q, a.
    Unfortunately I was not able to get the termintation check on pg. 7 to work.
*/
bool util::pell_PQa_algorithm::has_repeated()
{
    if (i <= 1)
        return false;
    for (int j = 0; j < a.size() - 1; j++)
        if (P.back() == P[j] && Q.back() == Q[j] && a.back() == a[j])
            return true;
    return false;
}

std::vector<util::pell_solution> util::LMM_algorithm(mpz_class D, mpz_class N)
{
    std::vector<util::pell_solution> fundamentals;

    std::vector<mpz_class> f_list;
    mpz_class f = 0;
    while ((++f) * f <= abs(N))
        if (N % (f * f) == 0)
            f_list.emplace_back(f);
    for (mpz_class &f : f_list)
    {
        mpz_class m = N / (f * f);
        mpz_class m_abs = abs(m);
        std::vector<mpz_class> z_list;
        for (mpz_class z = mpz_class(floor(-mpf_class(m_abs) / 2)) + 1; z < mpz_class(floor(mpf_class(m_abs) / 2)) + 1 ; z++)
            if ((z * z - D) % m_abs == 0)
                z_list.emplace_back(z);
        for (mpz_class &z : z_list)
        {
            pell_PQa_algorithm gen(z, m_abs, D);
            bool found_Q = false;
            while (true)
            {
                gen.move_next();
                if (gen.has_repeated())
                {
                    found_Q = false;
                    break;
                }
                if (gen.i >= 1 && abs(gen.Q[gen.Q.size() - 1]) == 1)
                {
                    found_Q = true;
                    break;
                }
            }
            if (!found_Q)
                continue;

            if (gen.G[gen.G.size() - 2] * gen.G[gen.G.size() - 2] - D * gen.B[gen.B.size() - 2] * gen.B[gen.B.size() - 2] == m)
            {
                fundamentals.emplace_back(f * gen.G[gen.G.size() - 2], f * gen.B[gen.B.size() - 2]);
            }
            else
            {
                gen.move_next();
                while (abs(gen.Q[gen.Q.size() - 1]) != 1)
                    gen.move_next();
                if (gen.G[gen.G.size() - 2] * gen.G[gen.G.size() - 2] - D * gen.B[gen.B.size() - 2] * gen.B[gen.B.size() - 2] == m)
                    fundamentals.emplace_back(f * gen.G[gen.G.size() - 2], f * gen.B[gen.B.size() - 2]);
            }
        }
    }

    return fundamentals;
}





void util::pell_solver::init(mpz_class D, mpz_class N)
{
    this->D = D;
    this->N = N;

    mpf_class D_sqrt = sqrt(mpf_class(D));
    if (floor(D_sqrt) != D_sqrt)
    {
        unit_fundamental = LMM_algorithm(D, 1)[0];
        if (N == 1)
        {
            fundamentals.emplace_back(1, 0);
            unit_solutions.emplace_back(unit_fundamental);
            solutions.emplace_back(unit_fundamental);
        }
        else
        {
            for (pell_solution &fundamental : LMM_algorithm(D, N))
            {
                fundamentals.emplace_back(fundamental);
                unit_solutions.emplace_back(pell_solution(1, 0));
                solutions.emplace_back(fundamental);
            }
        }
    }

    has_solution = !fundamentals.empty();
}

util::pell_solver::pell_solver()
{

}

util::pell_solver::pell_solver(mpz_class D, mpz_class N)
{
    init(D, N);
}

bool util::pell_solver::move_next()
{
    if (!has_solution)
        return false;

    bool has_minimal_solution = false;
    pell_solution minimal_solution;

    for (pell_solution &solution : solutions)
    {
        if (!has_minimal_solution || (
                abs(solution.x) < abs(minimal_solution.x) ||
                (abs(solution.x) == abs(minimal_solution.x) && abs(solution.y) < abs(minimal_solution.y))))
        {
            has_minimal_solution = true;
            minimal_solution.x = abs(solution.x);
            minimal_solution.y = abs(solution.y);
        }
    }

    for (int i = 0; i < fundamentals.size(); i++)
    {
        while (abs(solutions[i].x) <= minimal_solution.x && abs(solutions[i].y) <= minimal_solution.y)
        {
            unit_solutions[i] = pell_solution(
                unit_fundamental.x * unit_solutions[i].x + D * unit_fundamental.y * unit_solutions[i].y,
                unit_fundamental.x * unit_solutions[i].y + unit_fundamental.y * unit_solutions[i].x
            );

            solutions[i] = pell_solution(
                fundamentals[i].x * unit_solutions[i].x + D * fundamentals[i].y * unit_solutions[i].y,
                fundamentals[i].x * unit_solutions[i].y + fundamentals[i].y * unit_solutions[i].x
            );
        }
    }

    solution = minimal_solution;

    return true;
}
