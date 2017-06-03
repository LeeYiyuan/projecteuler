/*
    For the incidence of some beam with gradient m onto a point x, y, we consider
    how the gradient of the reflected beam, m', will change with respect to the
    gradient of the mirror tangent at (x, y).

    In general we can split the cases into the four usual quadrants. For each
    quadrant, we split the cases of m into two, positive or negative, and use atan2
    to determine the reflected angle, which we can use to determine the reflected
    gradient.

    Note also that the rays always reflect clockwise so we can half the number
    of cases to consider.

    Because I can't really draw here, the details of the gradient transformations
    are therefore, as some may say, left as an exercise to the reader.

    After finding m' for an incidence (x, y, m), we can let the equation of the
    reflected ray be y' = mx' + s. s can be found using the incidence coordinates:
    s = y - mx. Next, we are interested in where y' = mx' + s intersects the ellipse.
    That is, we need

        (mx' + s)^2 = 100 - 4x'^2

    from which we can setup a quadratic in x' and solve. We reject the root that
    is equal to x, and the other root will be x'. y' can then be recovered using
    y' = mx' + s.

    This gives us the coordinates of the next incidence, (x', y', m'). We loop
    until an incidence (x, y, m) such that -0.01 <= x <= 0.01 and y' > 0.
*/

#include <cmath>
#include <iostream>

#define PI 3.14159265358979323846

struct step_struct
{
    double x, y, m;
    step_struct(double x, double y, double m)
    {
        this->x = x;
        this->y = y;
        this->m = m;
    }
};

double mod(double n, double m)
{
    double result = std::fmod(n, m);
    if (result < 0)
        result += m;
    return result;
}

step_struct get_next(step_struct &step)
{
    double x = step.x;
    double y = step.y;
    double m = step.m;
    double m_r = -4.0 * x / y;

    double offset, incident;

    if (x > 0 && y > 0)
    {
        offset = mod(std::atan2(-m_r, -1), 2 * PI);
        incident = mod(std::atan2(-m, -1), 2 * PI);
    }
    else if (x < 0 && y > 0)
    {
        offset = mod(std::atan2(-m_r, -1), 2 * PI);
        if (m > 0)
            incident = mod(std::atan2(-m, -1), 2 * PI);
        else
            incident = std::atan2(m, 1);
    }
    else if (x < 0 && y < 0)
    {
        offset = std::atan2(m_r, 1);
        incident = std::atan2(m, 1);
    }
    else if (x > 0 && y < 0)
    {
        offset = std::atan2(m_r, 1);
        if (m > 0)
            incident = std::atan2(m, 1);
        else
            incident = std::atan2(-m, -1);
    }

    double theta = incident - offset;
    m = std::tan(PI - theta + offset);
    double s = y - m * x;

    double a = m * m + 4;
    double b = 2 * m * s;
    double c = s * s - 100;

    double x1 = (-b + std::sqrt(b * b - 4 * a * c)) / (2 * a);
    double x2 = (-b - std::sqrt(b * b - 4 * a * c)) / (2 * a);

    double x_next;
    if (std::abs(x1 - x) > std::abs(x2 - x))
        x_next = x1;
    else
        x_next = x2;

    double y_next = m * x_next + s;

    return step_struct(x_next, y_next, m);
}

int main()
{
    int count = 0;
    step_struct step(1.4, -9.6, (-9.6 - 10.1) / (1.4 - 0));
    while (!(std::abs(step.x) <= 0.01 && step.y > 0))
    {
        step = get_next(step);
        count++;
    }

    std::cout << count;
}
