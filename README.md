# Quadratic equation solving module
This module will solve quadratic equations in real numbers and provide better precision than regular solutions in edge cases.

### Файл README на русском языке находится в папке quadratic_equation.

## Usage
Simply add this module to your C/C++ project, include header file and add dependencies:
1. Add source files `quadratic_equation.c` and `quadratic_equation.h` to your project.
2. Include the header file (`#include "quadratic_equation.h"`) in your source code.
3. Add the required library dependencies to your compilation/linker command:
    * **`libm (-lm)`** is a hard dependency and must be included.
    * **`libquadmath (-lquadmath)`** is a soft dependency that can be enabled in config section of the header file. If enabled, internal calculations are done with float128, which may improve result precision in rare edge cases. If you use quadmath elsewhere, why not enable it here, too?

Alternatively, you can compile this module into a static library using `make` command and link against the resulting library file.


## Contract
Core function of this module is `solve_equation()`. Its signature is:\
`quadratic_roots solve_equation(double a, double b, double c)`\
where a, b and c are coefficients for `ax^2 + bx + c = 0` equation.\
It returns `quadratic_roots` struct with following fields:
```
typedef struct quadratic_equation_result_struct {
  double root[2];         // array storing roots
  int num_roots;          // number of roots found (by default 0 to 2)
  solve_equation_return_status err;  // result status code
  const char* status_message;        // message for result status
} quadratic_roots;
```
* `double root[2]`: An array storing roots of the equation. If equation has only one root, both cells will be equal. If equation has no roots, array will hold NaN values.
* `int num_roots`: The number of roots found, which can be 0, 1 or 2. **There is a special case** where all coefficients are 0 and equation has infinite number of roots. In this case, function will either return **\`num_roots = 0\`** and error or **\`num_roots = 3\`** and warning. **This can be configured in config section in header file**, by default it will return 0 and error.
* `solve_equation_return_status err`: Result status code. **0 indicates success, negative values indicate warnings, positive values indicate errors.**
* `const char* status_message`: Pointer to string literal with message for result status code.

#### Note that behavior of this function can be customized depending on configuration settings in the header file.
In particular, the use of libquadmath (internal calculations in quad precision) and behavior of the function when all coefficients are 0 can be customized.

## Unit tests and coverage report
### Tests:
**Run** `make check` **to run tests.** This command will compile module into static lib, link it against unit tests file and run tests. For it to run, there must be unit tests source file present in tests folder. By default, it's `tests/unittests.c` and the file is provided in repository.

Alternatively, unit tests source file can be assembled from `*.check` modules in unit tests folder (by default, `unit_tests/`).\
**To do this, run** `make unittests` **target.** Assembling works in following steps:
1. All `*.check` modules will be combined into one `.check` file. Module `include.check` will always be at the top, use this file to include necessary headers and declare what needs to be declared for tests.
2. `checkmk` utility will convert combined `.check` file into unit tests source file and put it into tests folder.
### Coverage report:
**Run** `make gcov` **to make .html coverage report and open it in default browser.**\
Coverage report gcda/gcno files are automatically generated by unit tests. This target uses `gcovr` utility to generate .html report from them.


## solve_equation() function logic
In general, `solve_equation` function flows like this:
1. Take coefficients for quadratic equation as arguments `double a, b, c`
2. Check coefficients for validity (no INF or NANs) and convert them to float128 or long double type variables.
3. Start checking them for value 0 in order from `a` to `c`.
4. if `a` is **not** zero, solve quadratic equation:
    * Calculate discriminant. If it is out of range, normalize coefficients and calculate again.
    * If `discriminant is positive`, find two roots. Function picks more numerically stable formula for given coefficients, calculates roots and then recalculates root with smaller absolute value from larger one.
    * If `discriminant is zero`, find one root but still copy it into both array cells.
    * If `discriminant is negative`, there are no roots, return NANs and OK status.
5. if `a` is zero but `b` is **not** zero, solve linear equation.
6. if `b` is also zero but `c` is not, there are no roots, return NANs and OK status.
7. if all three coefficients are zero, there are infinite amount of roots. Handle this situation according to configuration in header file by producing either a warning, or an error.
