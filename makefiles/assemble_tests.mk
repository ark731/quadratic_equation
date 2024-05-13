##############################################################
# Спасибо Владиславу @lothostr за оригинальную идею и скрипт #
##############################################################
# This module will assemble unit tests source file from '.check' modules
# ///// DEPENDENCIES: /////
#
# External variables:
#   TEST_DIR  - where to put unit tests source file.
#   TESTS     - name for unit tests source file.
#   STYLE     - name for style for clang-format (if clang-format is present).
#
# External targets:
#   style-fix - Soft dependency target that also expects 'clang-format' to be installed.
#
# Utilities:
#   checkmk - Hard dependency utility that is required for this module to function correctly.
#   clang-format - Soft dependency utility used by the 'style-fix' target.

UNITTESTS_FOLDER=unit_tests
CHECK_INCLUDES=$(UNITTESTS_FOLDER)/includes.check
COMBINED_FILE=$(UNITTESTS_FOLDER)/_unittests.check
CHECK_FILES=$(filter-out $(CHECK_INCLUDES) $(COMBINED_FILE), $(wildcard $(UNITTESTS_FOLDER)/*.check))


unittests: $(TEST_DIR)/$(TESTS)
ifeq ($(shell uname -s), Linux)
	@sed -i 's/\bsrunner_run_all\b/srunner_set_fork_status(sr, CK_NOFORK);\n\n srunner_run_all/' $^
endif
ifeq ($(shell uname -s), Darwin)
	@sed -i '' 's/\bsrunner_run_all\b/srunner_set_fork_status(sr, CK_NOFORK);\n\n srunner_run_all/' $^
endif
	@if [ -x "$(shell command -v clang-format)" ]; then \
		clang-format -i -style=$(STYLE) $(TEST_DIR)/$(TESTS); \
	fi

$(TEST_DIR)/$(TESTS): $(COMBINED_FILE)
	@mkdir -p $(TEST_DIR)
	checkmk clean_mode=1 $(COMBINED_FILE) > $@
	@rm -f $(COMBINED_FILE)
	@if [ -x "$(shell command -v clang-format)" ]; then \
		clang-format -i -style=$(STYLE) $(TEST_DIR)/$(TESTS); \
	fi

$(COMBINED_FILE): $(CHECK_INCLUDES) $(CHECK_FILES)
	@echo ==COMBINING '.check' FILES==
	@$(MAKE) test_numbering
	@rm -f $(COMBINED_FILE)
	@cat $^ > $(COMBINED_FILE)

test_numbering:
	@for file in $$(find $(UNITTESTS_FOLDER) -name "*.check"); do \
		cp $$file $$file.bak; \
		awk -v count=1 -v prev="" ' \
		/^#test/ { \
			split($$0, a, " "); \
			gsub(/[0-9]+$$/, "", a[2]); \
			if(a[2] != prev){ \
				count = 1; \
				prev = a[2]; \
			} \
			printf "%s %s%d", a[1], a[2], count++; \
			for (i=3; i<=length(a); i++) printf " %s", a[i]; \
			print ""; \
		} \
		!/^#test/ {print $$0}' $$file.bak > $$file; \
		rm $$file.bak; \
	done

#  /////////////////////  EXTRAS  //////////////////////
.PHONY: $(COMBINED_FILE) $(TEST_DIR)/$(TESTS) unittests test_numbering
