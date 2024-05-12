# This module will handle static analysis and formatting of source code.
# ///// DEPENDENCIES: /////
#
# Utilities:
#   clang-format
#   cppcheck

#  /////////////////////  ATTENTION  /////////////////////
# Make sure you call these targets in correct directories or use glob variants.

STYLE=Google

style: 
	@clang-format -n -style=$(STYLE) *.h *.c
	@echo ==STYLE CHECK COMPLETED. STYLE=$(STYLE)==

style-glob: 
	@clang-format -n -style=$(STYLE) **/*.h **/*.c
	@echo ==STYLE CHECK COMPLETED. STYLE=$(STYLE)==

style-fix: 
	@clang-format -i -style=$(STYLE) *.h *.c
	@echo ==STYLE FIX COMPLETED. STYLE=$(STYLE)==

style-fix-glob: 
	@clang-format -i -style=$(STYLE) **/*.h **/*.c
	@echo ==STYLE FIX COMPLETED. STYLE=$(STYLE)==

cppcheck:
	@cppcheck --enable=all --suppress=missingIncludeSystem *.c

cppcheck-glob:
	@cppcheck --enable=all --suppress=missingIncludeSystem **/*.c

.PHONY: style style-fix cppcheck
