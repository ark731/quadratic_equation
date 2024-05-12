#include <math.h>
// #include <quadmath.h>
#include <stdio.h>

#include "quadratic_equation.h"

int main(void) {
  quadratic_roots roots;

  // roots = solve_equation(8e+290, __DBL_MAX__, -__DBL_MAX__);
  roots = solve_equation(0, __DBL_MAX__, __DBL_MAX__);

  printf("num_roots: %d   root_1: %.16lg   root_2: %.16lg\nERR: %d\n\"%s\"\n\n",
         roots.num_roots, roots.root[0], roots.root[1], roots.err,
         roots.status_message);

  //   printf("%Qg    %Qg    %lg   = %Qg\n",
  //          (__float128)(roots.root[0]) * roots.root[0] * __DBL_MAX__ / 10.,
  //          (__float128)(__DBL_MAX__)*roots.root[0], -__DBL_MAX__,
  //          (__float128)(roots.root[0]) * roots.root[0] * __DBL_MAX__ / 10. +
  //              __DBL_MAX__ * roots.root[0] - __DBL_MAX__);
  //   printf("%Qg    %Qg    %lg   = %Qg\n",
  //          (__float128)(roots.root[1]) * roots.root[1] * __DBL_MAX__ / 10.,
  //          (__float128)(__DBL_MAX__)*roots.root[1], -__DBL_MAX__,
  //          ((__float128)(roots.root[1]) * roots.root[1] * __DBL_MAX__ / 10.)
  //          +
  //              (__DBL_MAX__ * (__float128)(roots.root[1])) - __DBL_MAX__);

  //   __float128 flt128a = INFINITY;
  //   __float128 flt128b = NAN;
  //   long double ldbla = INFINITY;
  //   long double ldblb = NAN;
  //   double dbla = INFINITY;
  //   double dblb = NAN;
  //   putchar('\n');
  //   putchar('\n');
  //   printf("%Qg   %Qg\n", flt128a, flt128b);
  //   printf("%Lg   %Lg\n", ldbla, ldblb);
  //   printf("%lg   %lg\n", dbla, dblb);

  //   putchar('\n');
  //   putchar('\n');
  //   long double ldblc = flt128a;
  //   long double ldbld = flt128b;
  //   printf("%Lg   %Lg\n", ldblc, ldbld);
  return 0;
}