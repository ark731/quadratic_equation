#ifndef SOLVE_QUADRATIC_EQUATION_H
#define SOLVE_QUADRATIC_EQUATION_H

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////
/*  -------------------------------- CONFIG --------------------------------  */
/* Set to 1 to enable quad precision for internal calculations.               */
/* May provide better result in rare edge cases.                              */
#define ENABLE_FLOAT128 0
/* Controls behavior when all coefficients are 0 (infinite number of roots).  */
/* 0 - returns WARNING status and num_roots = 3                               */
/* 1 - returns ERROR status and num_roots = 0                                 */
#define INFINITE_NUMBER_OF_ROOTS_IS_ERROR 1
/*  ------------------------------------------------------------------------  */
////////////////////////////////////////////////////////////////////////////////

/*  ---------------------------- RESULT STRUCT -----------------------------  */
/// @brief Structure holds equation roots, number of roots and execution status
/// @param root[2] Roots.
/// @param num_roots Number of roots found. 3 - infinite number of roots.
/// @param err Execution status.
/// @param error_message Message for given execution status.
typedef struct quadratic_equation_result_struct {
  double root[2];
  int num_roots;
  solve_equation_return_status err;
  const char* status_message;
} quadratic_roots;

/*  ---------------------------- RETURN STATUS -----------------------------  */
/// @brief Execution status.
/// OK = 0.
/// Warnings have negative values.
/// Errors have positive values.
typedef enum {
  WARNING_INFINITE_NUMBER_OF_ROOTS = -2,
  WARNING_ROOT_IS_INFINITY,
  OK = 0,
  INVALID_COEFFICIENTS,
  ERROR_INFINITE_NUMBER_OF_ROOTS,
  UNKNOWN_ERROR
} solve_equation_return_status;

/*  --------------------------- STATUS MESSAGES ----------------------------  */
#define MESSAGE_WARNING_INFINITE_NUMBER_OF_ROOTS \
  "Warning: all coefficients are zero, equation has infinite number of roots."
#define MESSAGE_WARNING_ROOT_IS_INFINITY \
  "Warning: one or both roots of equation are infinity."
#define MESSAGE_SOLVE_EQUATION_OK "Success: equation has been solved."
#define MESSAGE_INVALID_COEFFICIENTS "Error: invalid equation coefficients."
#define MESSAGE_ERROR_INFINITE_NUMBER_OF_ROOTS \
  "Error: all coefficients are zero, equation has infinite number of roots."
#define MESSAGE_UNKNOWN_ERROR "Error: unknown error."

/*  ----------------------- SOLVE EQUATION FUNCTION ------------------------  */
/// @brief Solution of a quadratic equation in real numbers
/// @param a Senior coefficient
/// @param b Middle coefficient
/// @param c Free term
/// @return Structure with equation roots, number of roots and execution status
quadratic_roots solve_equation(double a, double b, double c);

#ifdef __cplusplus
}  // extern C
#endif

#endif  // SOLVE_QUADRATIC_EQUATION_H