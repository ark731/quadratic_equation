/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "unit_tests/_unittests.check" instead.
 */

#include <check.h>
#include <math.h>

#include "../quadratic_equation.h"

#define CK_FORK 0
#define QUADRATIC_TEST_EPSILON __DBL_EPSILON__ * 1000

/* Compare roots to epsilon above. */
static int compare_roots(double x1, double x2, quadratic_roots *roots) {
  double tmp;
  if (roots->root[0] > roots->root[1]) {
    tmp = roots->root[0];
    roots->root[0] = roots->root[1];
    roots->root[1] = tmp;
  }
  if (x1 > x2) {
    tmp = x1;
    x1 = x2;
    x2 = tmp;
  }
  double eps1 = fmax(fabs(x1), fabs(roots->root[0])) * QUADRATIC_TEST_EPSILON;
  double eps2 = fmax(fabs(x2), fabs(roots->root[1])) * QUADRATIC_TEST_EPSILON;
  if (!eps1) eps1 = __DBL_MIN__;
  if (!eps2) eps2 = __DBL_MIN__;
  return (fabs(x1 - roots->root[0]) <= eps1) &&
         (fabs(x2 - roots->root[1]) <= eps2);
}

START_TEST(test_edge_cases1) {
  double a = __DBL_MAX__;
  double b = __DBL_MAX__;
  double c = __DBL_MAX__;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, isnan(roots.root[0]) && isnan(roots.root[1]));
  ck_assert_int_eq(0, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_edge_cases2) {
  double a = 0;
  double b = __DBL_MAX__;
  double c = __DBL_MAX__;
  double x1 = -1.0;
  double x2 = -1.0;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(1, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_edge_cases3) {
  double a = __DBL_MAX__;
  double b = __DBL_MAX__;
  double c = -__DBL_MAX__;
  double x1 = 0.618033988749894;
  double x2 = -1.618033988749894;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_edge_cases4) {
  double a = __DBL_MAX__ / 10.;
  double b = __DBL_MAX__;
  double c = -__DBL_MAX__;
  double x1 = 0.916079783099616;
  double x2 = -10.916079783099616;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_edge_cases5) {
  double a = __DBL_DENORM_MIN__;
  double b = 0;
  double c = -100;
  double x1 = 4.498913794543196e+162;
  double x2 = -4.498913794543196e+162;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_edge_cases6) {
  double a = __DBL_DENORM_MIN__;
  double b = 0;
  double c = -1.0e280;
  double x1 = 4.498913794543197e+301;
  double x2 = -4.498913794543197e+301;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_edge_cases7) {
  double a = -21;
  double b = 8e+150;
  double c = 1.08145e+300;
  double x1 = -1.0579867883597554e+149;
  double x2 = 4.8675105978835645e+149;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_edge_cases8) {
  double a = -0.002;
  double b = 8.0e+149;
  double c = 1.0e+299;
  double x1 = -1.2496096189501535e+149;
  double x2 = 4.0012496096189503e+152;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_edge_cases9) {
  double a = 4.0e-287;
  double b = -1000;
  double c = -8.0e+290;
  double x1 = 2.5775918047351755e+289;
  double x2 = -7.759180473517537e+287;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_edge_cases10) {
  double a = 8e+295;
  double b = -1.0e29;
  double c = 0;
  double x1 = 0;
  double x2 = 1.25e-267;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_errors1) {
  double a = NAN;
  double b = 124.12424;
  double c = -4.54;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(INVALID_COEFFICIENTS, roots.err);
}
END_TEST

START_TEST(test_errors2) {
  double a = 5387873.587;
  double b = 124.12424;
  double c = -NAN;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(INVALID_COEFFICIENTS, roots.err);
}
END_TEST

START_TEST(test_errors3) {
  double a = 835293.958;
  double b = INFINITY;
  double c = -4.54;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(INVALID_COEFFICIENTS, roots.err);
}
END_TEST

START_TEST(test_errors4) {
  double a = 835293.958;
  double b = 15346.245;
  double c = -INFINITY;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(INVALID_COEFFICIENTS, roots.err);
}
END_TEST

START_TEST(test_errors5) {
  double a = 0.0;
  double b = 0.0;
  double c = 0.0;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, (roots.err == ERROR_INFINITE_NUMBER_OF_ROOTS) ||
                          (roots.err == WARNING_INFINITE_NUMBER_OF_ROOTS));
}
END_TEST

START_TEST(test_errors6) {
  double a = __DBL_DENORM_MIN__;
  double b = 0;
  double c = -__DBL_MAX__;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, (roots.err == WARNING_ROOT_IS_INFINITY));
}
END_TEST

START_TEST(test_solve_linear1) {
  double a = 0;
  double b = 7;
  double c = -3;
  double x1 = 0.428571428571428;
  double x2 = 0.428571428571428;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(1, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_linear2) {
  double a = 0;
  double b = 5;
  double c = -10;
  double x1 = 2;
  double x2 = 2;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(1, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_linear3) {
  double a = 0;
  double b = 3;
  double c = -4;
  double x1 = 1.3333333333333333;
  double x2 = 1.3333333333333333;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(1, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_no_roots1) {
  double a = 0;
  double b = 0;
  double c = -1;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, isnan(roots.root[0]) && isnan(roots.root[1]));
  ck_assert_int_eq(0, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_no_roots2) {
  double a = 0;
  double b = 0;
  double c = 5;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, isnan(roots.root[0]) && isnan(roots.root[1]));
  ck_assert_int_eq(0, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

/*  ----- DISCRIMINANT > 0 -----  */

START_TEST(test_solve_quadratic1) {
  double a = 5;
  double b = 7;
  double c = -3;
  double x1 = 0.344030650891055;
  double x2 = -1.744030650891055;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic2) {
  double a = 1;
  double b = -3;
  double c = 2;
  double x1 = 1;
  double x2 = 2;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic3) {
  double a = 1;
  double b = 0;
  double c = -9;
  double x1 = 3;
  double x2 = -3;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic4) {
  double a = 1;
  double b = 0;
  double c = -1;
  double x1 = 1;
  double x2 = -1;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic5) {
  double a = 2;
  double b = 6;
  double c = 4;
  double x1 = -1;
  double x2 = -2;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic6) {
  double a = 1;
  double b = 1.0e+30;
  double c = -1;
  double x1 = -1.0e+30;
  double x2 = 1.0e-30;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic7) {
  double a = 1;
  double b = -1.0e+30;
  double c = 1;
  double x1 = 1.0e+30;
  double x2 = 1.0e-30;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic8) {
  double a = 21;
  double b = 2121;
  double c = -21212121;
  double x1 = 955.8057437975797;
  double x2 = -1056.8057437975797;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic9) {
  double a = -21;
  double b = 2121;
  double c = 21212121;
  double x1 = -955.8057437975797;
  double x2 = 1056.8057437975797;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic10) {
  double a = 21;
  double b = -2121;
  double c = -21212121;
  double x1 = -955.8057437975797;
  double x2 = 1056.8057437975797;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic11) {
  double a = -21;
  double b = -2121;
  double c = 21212121;
  double x1 = 955.8057437975797;
  double x2 = -1056.8057437975797;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(2, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);

  /*  ----- DISCRIMINANT = 0 -----  */
}
END_TEST

START_TEST(test_solve_quadratic12) {
  double a = 1;
  double b = 4;
  double c = 4;
  double x1 = -2;
  double x2 = -2;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(1, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic13) {
  double a = 1;
  double b = 2;
  double c = 1;
  double x1 = -1;
  double x2 = -1;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(1, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic14) {
  double a = 1;
  double b = -4;
  double c = 4;
  double x1 = 2;
  double x2 = 2;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(1, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic15) {
  double a = 1;
  double b = 0;
  double c = 0;
  double x1 = 0;
  double x2 = 0;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, compare_roots(x1, x2, &roots));
  ck_assert_int_eq(1, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);

  /*  ----- DISCRIMINANT < 0 -----  */
}
END_TEST

START_TEST(test_solve_quadratic16) {
  double a = 1;
  double b = 0;
  double c = 1;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, isnan(roots.root[0]) && isnan(roots.root[1]));
  ck_assert_int_eq(0, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic17) {
  double a = 1;
  double b = -1.0e-18;
  double c = 1;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, isnan(roots.root[0]) && isnan(roots.root[1]));
  ck_assert_int_eq(0, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic18) {
  double a = 2;
  double b = -2;
  double c = 8;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, isnan(roots.root[0]) && isnan(roots.root[1]));
  ck_assert_int_eq(0, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic19) {
  double a = 21;
  double b = 2121;
  double c = 21212121;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, isnan(roots.root[0]) && isnan(roots.root[1]));
  ck_assert_int_eq(0, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic20) {
  double a = 21;
  double b = -2121;
  double c = 21212121;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, isnan(roots.root[0]) && isnan(roots.root[1]));
  ck_assert_int_eq(0, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic21) {
  double a = -21;
  double b = 2121;
  double c = -21212121;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, isnan(roots.root[0]) && isnan(roots.root[1]));
  ck_assert_int_eq(0, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

START_TEST(test_solve_quadratic22) {
  double a = -21;
  double b = -2121;
  double c = -21212121;
  quadratic_roots roots;
  roots = solve_equation(a, b, c);
  ck_assert_int_eq(1, isnan(roots.root[0]) && isnan(roots.root[1]));
  ck_assert_int_eq(0, roots.num_roots);
  ck_assert_int_eq(OK, roots.err);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("test_edge_cases");
  TCase *tc1_1 = tcase_create("test_edge_cases");
  Suite *s2 = suite_create("test_errors");
  TCase *tc2_1 = tcase_create("test_errors");
  Suite *s3 = suite_create("test_solve_linear");
  TCase *tc3_1 = tcase_create("test_solve_linear");
  Suite *s4 = suite_create("test_solve_no_roots");
  TCase *tc4_1 = tcase_create("test_solve_no_roots");
  Suite *s5 = suite_create("test_solve_quadratic");
  TCase *tc5_1 = tcase_create("test_solve_quadratic");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_edge_cases1);
  tcase_add_test(tc1_1, test_edge_cases2);
  tcase_add_test(tc1_1, test_edge_cases3);
  tcase_add_test(tc1_1, test_edge_cases4);
  tcase_add_test(tc1_1, test_edge_cases5);
  tcase_add_test(tc1_1, test_edge_cases6);
  tcase_add_test(tc1_1, test_edge_cases7);
  tcase_add_test(tc1_1, test_edge_cases8);
  tcase_add_test(tc1_1, test_edge_cases9);
  tcase_add_test(tc1_1, test_edge_cases10);
  suite_add_tcase(s2, tc2_1);
  tcase_add_test(tc2_1, test_errors1);
  tcase_add_test(tc2_1, test_errors2);
  tcase_add_test(tc2_1, test_errors3);
  tcase_add_test(tc2_1, test_errors4);
  tcase_add_test(tc2_1, test_errors5);
  tcase_add_test(tc2_1, test_errors6);
  suite_add_tcase(s3, tc3_1);
  tcase_add_test(tc3_1, test_solve_linear1);
  tcase_add_test(tc3_1, test_solve_linear2);
  tcase_add_test(tc3_1, test_solve_linear3);
  suite_add_tcase(s4, tc4_1);
  tcase_add_test(tc4_1, test_solve_no_roots1);
  tcase_add_test(tc4_1, test_solve_no_roots2);
  suite_add_tcase(s5, tc5_1);
  tcase_add_test(tc5_1, test_solve_quadratic1);
  tcase_add_test(tc5_1, test_solve_quadratic2);
  tcase_add_test(tc5_1, test_solve_quadratic3);
  tcase_add_test(tc5_1, test_solve_quadratic4);
  tcase_add_test(tc5_1, test_solve_quadratic5);
  tcase_add_test(tc5_1, test_solve_quadratic6);
  tcase_add_test(tc5_1, test_solve_quadratic7);
  tcase_add_test(tc5_1, test_solve_quadratic8);
  tcase_add_test(tc5_1, test_solve_quadratic9);
  tcase_add_test(tc5_1, test_solve_quadratic10);
  tcase_add_test(tc5_1, test_solve_quadratic11);
  tcase_add_test(tc5_1, test_solve_quadratic12);
  tcase_add_test(tc5_1, test_solve_quadratic13);
  tcase_add_test(tc5_1, test_solve_quadratic14);
  tcase_add_test(tc5_1, test_solve_quadratic15);
  tcase_add_test(tc5_1, test_solve_quadratic16);
  tcase_add_test(tc5_1, test_solve_quadratic17);
  tcase_add_test(tc5_1, test_solve_quadratic18);
  tcase_add_test(tc5_1, test_solve_quadratic19);
  tcase_add_test(tc5_1, test_solve_quadratic20);
  tcase_add_test(tc5_1, test_solve_quadratic21);
  tcase_add_test(tc5_1, test_solve_quadratic22);

  srunner_add_suite(sr, s2);
  srunner_add_suite(sr, s3);
  srunner_add_suite(sr, s4);
  srunner_add_suite(sr, s5);

  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
