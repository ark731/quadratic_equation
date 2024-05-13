# This module will test code for memory handling errors
# ///// DEPENDENCIES: /////
#
# External variables:
#   LIB - name for target that will build library for testing.
#   TEST_EXEC - name for target that will build tests.
#
# External targets:
#   check - Hard dependency target that will run tests.
#
# Utilities:
#   gcovr - Hard dependency utility that is required for this module to function correctly.

valgrind: $(TEST_EXEC)
	@valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TEST_EXEC)

valgrind_short: $(TEST_EXEC)
	@valgrind -s --track-origins=yes --verbose ./$(TEST_EXEC)

.PHONY: valgrind valgrind_short
