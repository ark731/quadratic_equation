#include "quadratic_equation.h"

#include <math.h>

/*  ------------------- Pick precision for calculations --------------------  */
/* Edit CONFIG section in header file to disable quad/extended precision.     */
/* Make will check for quadmath.h lib and set this to 1 if it is available.   */
#if ENABLE_FLOAT128 == 1 && defined(__SIZEOF_FLOAT128__)
/* Use quad precision if available.                                           */
#include <quadmath.h>
typedef __float128 extra_precise_t;
#define sqrt_ sqrtq
#define fabs_ fabsq
#define fmax_ fmaxq
#define isinf_ isinfq
#define isnan_ isnanq

#else
/* If not, use long double.                                                   */
typedef long double extra_precise_t;
#define sqrt_ sqrtl
#define fabs_ fabsl
#define fmax_ fmaxl
#define isinf_ isinf
#define isnan_ isnan

#endif  // ENABLE_FLOAT128 == 1 && defined(__SIZEOF_FLOAT128__)

/*  ------------------- Structure for internal variables -------------------  */
typedef struct quadratic_equation_coefficients {
  extra_precise_t a;
  extra_precise_t b;
  extra_precise_t c;
  extra_precise_t discriminant;
  extra_precise_t sqrt_discriminant;
} coefficients_;

//

////////////////////////////////////////////////////////////////////////////////
/*  --------------------- Static functions declaration ---------------------  */
////////////////////////////////////////////////////////////////////////////////
static inline int check_arguments_validity(double a, double b, double c);
static inline coefficients_ store_coefficients(double a, double b, double c);
static inline void normalize_coefficients(coefficients_ *coef);
static inline void calculate_discriminant(coefficients_ *coef);
static inline int discriminant_is_still_invalid(const coefficients_ *coef);
static inline void calculate_two_roots(const coefficients_ *coef,
                                       quadratic_roots *roots);
static inline void try_other_formula(const coefficients_ *coef,
                                     quadratic_roots *roots);
static inline void find_quadratic_roots(coefficients_ *coef,
                                        quadratic_roots *roots);
static inline void find_root_for_zero_discriminant(const coefficients_ *coef,
                                                   quadratic_roots *roots);
static inline void find_linear_root(const coefficients_ *coef,
                                    quadratic_roots *roots);
static inline void recalculate_smaller_root_with_higher_precision(
    const coefficients_ *coef, quadratic_roots *roots);
static inline void check_roots_validity(quadratic_roots *roots);
static inline void no_roots_write_nans(quadratic_roots *roots);
static inline void set_no_roots(quadratic_roots *roots);
static inline void set_infinite_roots(quadratic_roots *roots);
static inline void throw_unknown_error(quadratic_roots *roots);

//

////////////////////////////////////////////////////////////////////////////////
/*  ---------------------------- Solve equation ----------------------------  */
////////////////////////////////////////////////////////////////////////////////

quadratic_roots solve_equation(double a, double b, double c) {
  quadratic_roots roots = {0};
  coefficients_ coefficients = store_coefficients(a, b, c);

  /* Check arguments. */
  if (check_arguments_validity(a, b, c)) {
    roots.err = INVALID_COEFFICIENTS;
    roots.status_message = MESSAGE_INVALID_COEFFICIENTS;
    return roots;
  }

  /* Solve equation. */
  if (a) {
    find_quadratic_roots(&coefficients, &roots);
  } else if (b) {
    find_linear_root(&coefficients, &roots);
  } else if (c) {
    set_no_roots(&roots);
  } else {  // all arguments are 0, infinite number of roots
    set_infinite_roots(&roots);
  }

  return roots;
}

static inline void find_quadratic_roots(coefficients_ *coef,
                                        quadratic_roots *roots) {
  /* If forced to use float64 (long double = double), discriminant may overflow.
   * If this happens, normalize coefficients and recalculate discriminant. */
  calculate_discriminant(coef);
  if (isinf_(coef->discriminant)) {
    normalize_coefficients(coef);
    calculate_discriminant(coef);
  }

  /* Check discriminant once again. */
  if (discriminant_is_still_invalid(coef)) {
    throw_unknown_error(roots);

    /* Calculate roots. */
  } else if (coef->discriminant > 0.) {  //  DISCRIMINANT > 0
    calculate_two_roots(coef, roots);
    if (WARNING_ROOT_IS_INFINITY == roots->err) {
      try_other_formula(coef, roots);
    }
  } else if (coef->discriminant == 0.) {  // DISCRIMINANT = 0
    find_root_for_zero_discriminant(coef, roots);
  } else {  //                               DISCRIMINANT < 0
    set_no_roots(roots);
  }
}

//

static inline void calculate_two_roots(const coefficients_ *coef,
                                       quadratic_roots *roots) {
  roots->status_message = MESSAGE_SOLVE_EQUATION_OK;
  roots->num_roots = 2;
  roots->root[0] = (-coef->b + coef->sqrt_discriminant) / (2 * coef->a);
  roots->root[1] = (-coef->b - coef->sqrt_discriminant) / (2 * coef->a);
  check_roots_validity(roots);
  if (OK == roots->err) {
    recalculate_smaller_root_with_higher_precision(coef, roots);
  }
}

static inline void try_other_formula(const coefficients_ *coef,
                                     quadratic_roots *roots) {
  roots->status_message = MESSAGE_SOLVE_EQUATION_OK;
  roots->num_roots = 2;
  roots->root[0] = (-2 * coef->c) / (coef->b + coef->sqrt_discriminant);
  roots->root[1] = (-2 * coef->c) / (coef->b - coef->sqrt_discriminant);
  check_roots_validity(roots);
  if (OK == roots->err) {
    recalculate_smaller_root_with_higher_precision(coef, roots);
  }
}

static inline void recalculate_smaller_root_with_higher_precision(
    const coefficients_ *coef, quadratic_roots *roots) {
  /* In general, root that is closer to 0 (smaller absolute value) is more
   * likely to suffer from catastrophic loss of precision. Recalculate it from
   * the other root using Vieta's theorem. Put root with larger absolute value
   * into root[1], then recaltulate root[0]. */
  roots->status_message = MESSAGE_SOLVE_EQUATION_OK;
  roots->root[1] = (fabs_(roots->root[0]) > fabs_(roots->root[1]))
                       ? roots->root[0]
                       : roots->root[1];
  roots->root[0] = coef->c / (coef->a * roots->root[1]);
  check_roots_validity(roots);
}

static inline void find_root_for_zero_discriminant(const coefficients_ *coef,
                                                   quadratic_roots *roots) {
  roots->status_message = MESSAGE_SOLVE_EQUATION_OK;
  roots->num_roots = 1;
  roots->root[0] = -coef->b / (2 * coef->a);
  roots->root[1] = roots->root[0];
  check_roots_validity(roots);
}

static inline void find_linear_root(const coefficients_ *coef,
                                    quadratic_roots *roots) {
  roots->status_message = MESSAGE_SOLVE_EQUATION_OK;
  roots->num_roots = 1;
  roots->root[0] = -coef->c / coef->b;
  roots->root[1] = roots->root[0];
  check_roots_validity(roots);
}

static inline void no_roots_write_nans(quadratic_roots *roots) {
  roots->num_roots = 0;
  roots->root[0] = 0.0 / 0.0;
  roots->root[1] = 0.0 / 0.0;
}

static inline void set_no_roots(quadratic_roots *roots) {
  roots->status_message = MESSAGE_SOLVE_EQUATION_OK;  // no roots is still OK
  no_roots_write_nans(roots);
}

static inline void set_infinite_roots(quadratic_roots *roots) {
  no_roots_write_nans(roots);
  if (INFINITE_NUMBER_OF_ROOTS_IS_ERROR) {  // set in CONFIG in header file
    roots->num_roots = 0;
    roots->err = ERROR_INFINITE_NUMBER_OF_ROOTS;
    roots->status_message = MESSAGE_ERROR_INFINITE_NUMBER_OF_ROOTS;
  } else {
    roots->num_roots = 3;
    roots->err = WARNING_INFINITE_NUMBER_OF_ROOTS;
    roots->status_message = MESSAGE_WARNING_INFINITE_NUMBER_OF_ROOTS;
  }
}

//

////////////////////////////////////////////////////////////////////////////////
/*  --------------------------- Other functions ----------------------------  */
////////////////////////////////////////////////////////////////////////////////

static inline int check_arguments_validity(double a, double b, double c) {
  return isnan(a) || isnan(b) || isnan(c) || isinf(a) || isinf(b) || isinf(c);
}

static inline coefficients_ store_coefficients(double a, double b, double c) {
  coefficients_ coef;
  coef.a = a;
  coef.b = b;
  coef.c = c;
  coef.discriminant = 0.;
  coef.sqrt_discriminant = 0.;
  return coef;
}

/* This function will be called only if long double is an alias for double.
 * It is still tested and I recommend to keep it around. To test it again,
 * simply redefine extra_precise_t as typedef for 'double'
 */
static inline void normalize_coefficients(coefficients_ *coef) {
  extra_precise_t scaler =
      fmax_(fabs_(coef->a), fmax_(fabs_(coef->b), fabs_(coef->c)));
  coef->a /= scaler;
  coef->b /= scaler;
  coef->c /= scaler;
}

static inline void calculate_discriminant(coefficients_ *coef) {
  coef->discriminant = coef->b * coef->b - 4.0 * coef->a * coef->c;
  coef->sqrt_discriminant = sqrt_(coef->discriminant);
}

static inline int discriminant_is_still_invalid(const coefficients_ *coef) {
  return isinf_(coef->discriminant) || isnan_(coef->discriminant);
}

static inline void check_roots_validity(quadratic_roots *roots) {
  if (isnan(roots->root[0]) || isnan(roots->root[1])) {
    throw_unknown_error(roots);
  } else if (isinf(roots->root[0]) || isinf(roots->root[1])) {
    roots->err = WARNING_ROOT_IS_INFINITY;
    roots->status_message = MESSAGE_WARNING_ROOT_IS_INFINITY;
  }
}

static inline void throw_unknown_error(quadratic_roots *roots) {
  no_roots_write_nans(roots);
  roots->err = UNKNOWN_ERROR;
  roots->status_message = MESSAGE_UNKNOWN_ERROR;
}