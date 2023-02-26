// A Small program for solving quadratic equation for real roots.
// Made by Shabanov Nikita, 26th February 2023.

#include "equationClass.h"

void main(void)
{
    equationCl equation(0, 0, 0);
    equation.initFromFile("input.txt");
    equation.outputRootsToFile("output.txt");
}