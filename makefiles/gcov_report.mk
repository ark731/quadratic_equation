# This module will handle gcov coverage report
# ///// DEPENDENCIES: /////
#
# External variables:
#   LIB       - name for target that will build library for testing.
#   TEST_EXEC - name for target that will build tests.
#
# External targets:
#   check - Hard dependency target that will run tests.
#
# Utilities:
#   gcovr - Hard dependency utility that is required for this module to function correctly.

GCOV = gcov
GCOV_DIR = gcov_report
OPENOS = vi
ifeq ($(shell uname -s), Linux)
	OPENOS = xdg-open
endif
ifeq ($(shell uname -s), Darwin)
	OPENOS = open
endif

gcov: gcov_build_report
	@$(OPENOS) ./$(GCOV_DIR)/gcov_report.html

gcov_build_report: $(LIB) check $(GCOV_DIR)/gcov_report.html

$(GCOV_DIR)/gcov_report.html: $(LIB) $(TEST_EXEC)
	@rm -rf $(GCOV_DIR)
	@mkdir -p $(GCOV_DIR)
	@gcovr -r . --gcov-executable $(GCOV) --html --html-details -o $(GCOV_DIR)/gcov_report.html

.PHONY: gcov gcov_build_report
