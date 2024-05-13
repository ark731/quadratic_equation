# Main Makefile module that will handle compilation and unit tests.
# !!! Run 'make installdeps' to install dependencies.
#
# ////////////////////  DEPENDENCIES  ///////////////////
#
# External targets:
#   unittests_nofork - Soft dependency target that builds unit tests source
#       file from test modules. If this target is not present, provide
#       unit tests source file manually.
#
# Utilities:
#   pkg-config - Hard dependency target needed to link 'check' library
#   check      - Hard dependency.
#   checkmk    - Soft dependency needed to build unit tests source file.
#   gcovr      - Soft dependency for coverage report.
#
#  /////////////////////  VARIABLES  /////////////////////
# Aliases
LIB = quadratic_equation.a
TEST_LIB = $(addprefix test_, $(LIB))
TESTS = unittests.c
TEST_EXEC = test
CC = gcc
# For M1-M3 macs, force GCC compiler
ifeq ($(shell uname -p), arm)
	CC = gcc-13
	GCOV = gcov-13
endif
LIB_SOURCES = $(wildcard *.c)
LIB_OBJECTS = $(addprefix $(BUILD_DIR)/, $(LIB_SOURCES:.c=.o))
TEST_LIB_OBJECTS = $(addprefix $(TEST_BUILD_DIR)/, $(LIB_SOURCES:.c=.o))
TEST_OBJECTS = $(addprefix $(BUILD_TEST_DIR)/, $(notdir $(TESTS:.c=.o)))
# Directories
TEST_DIR = tests
BUILD_DIR = build
BUILD_TEST_DIR = build_tests
TEST_BUILD_DIR = test_build
DOC_DIR = doc
# Flags
FLAGS = -Wall -Werror -Wextra -std=c11
OPTFLAGS = -g -pedantic
GFLAGS = -fprofile-arcs -ftest-coverage
EXTRAFLAGS = -lm
GCOVFLAGS = -lgcov
IN_FLAGS = $(shell pkg-config --cflags check)
CHFLAGS = $(shell pkg-config --cflags --libs check)
QUADMATH_FLAGS = -lquadmath
QUADMATH_LIB_CHECK = $(shell find /usr -name 'libquadmath.a' -print -quit 2>/dev/null)
QUADMATH_HEADER_CHECK = $(shell find /usr -name 'quadmath.h' -print -quit 2>/dev/null)
ifeq ($(QUADMATH_LIB_CHECK),)
    QUADMATH_FLAGS = -DENABLE_FLOAT128=0
endif
ifeq ($(QUADMATH_HEADER_CHECK),)
    QUADMATH_FLAGS = -DENABLE_FLOAT128=0
endif


#  //////////////////////  DEFAULT  //////////////////////
all: $(LIB) 


#  ///////////////////////  TESTS  ///////////////////////
check: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJECTS) $(TEST_LIB)
	$(CC) $(FLAGS) $(OPTFLAGS) $(TEST_OBJECTS) -o $@ \
	$(CHFLAGS) $(EXTRAFLAGS) $(TEST_LIB) $(GCOVFLAGS) $(QUADMATH_FLAGS)

$(TEST_OBJECTS): $(BUILD_TEST_DIR)/%.o : $(TEST_DIR)/%.c
	@mkdir -p $(BUILD_TEST_DIR)
	$(CC) $(FLAGS) $(IN_FLAGS) -c $< -o $@

$(TEST_LIB): $(TEST_LIB_OBJECTS)
	ar -rcs $@ $^

$(TEST_LIB_OBJECTS): $(TEST_BUILD_DIR)/%.o : %.c $(LIB:.a=.h)
	@mkdir -p $(TEST_BUILD_DIR)
	$(CC) $(FLAGS) $(OPTFLAGS) $(GFLAGS) -c $< -o $@


#  ////////////////////  BUILD LIB  //////////////////////
$(LIB): $(LIB_OBJECTS)
	ar -rcs $@ $^
	@rm -rf $(BUILD_DIR)
	@if [ -x "$(shell command -v ranlib)" ]; then \
        ranlib $(LIB); \
    fi	

$(LIB_OBJECTS): $(BUILD_DIR)/%.o : %.c $(LIB:.a=.h)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(OPTFLAGS) -c $< -o $@ $(QUADMATH_FLAGS)


#  /////////////////////  REMOVAL  //////////////////////
clean:
	@echo ==Cleaning...==
	@rm -rf $(BUILD_DIR) $(BUILD_TEST_DIR) $(TEST_BUILD_DIR) $(DOC_DIR)
	@rm -rf $(GCOV_DIR)/gcov_report.html $(GCOV_DIR)/*.gcna $(GCOV_DIR)/*.gcno
	@rm -rf $(UNITTESTS_FOLDER)/_unittests.check 	# too dangerous to replace with variable
	@rm -rf gcov_report 							# too dangerous to replace with variable
	@rm -rf *.html
	@rm -rf *.out $(TEST_EXEC)
	@rm -rf *.a *.o
	@rm -rf *.css
	@rm -rf *.gch $(TEST_DIR)/*.gch
	@echo ==Done!==

rebuild: 
	$(MAKE) clean
	$(MAKE) all


#  ///////////////  INSTALL DEPENDENCIES  ////////////////
installdeps:
ifeq ($(shell uname -s), Linux)
		sudo apt-get install pkg-config check checkmk gcovr -y
endif
ifeq ($(shell uname -s), Darwin)
		brew install pkg-config check checkmk gcovr
endif


#  //////////////////////  EXTRAS  ///////////////////////
.PHONY: all clean rebuild check installdeps 


#  /////////////////////  INCLUDES  //////////////////////
include makefiles/assemble_tests.mk
include makefiles/gcov_report.mk
include makefiles/linters.mk
include makefiles/valgrind.mk
