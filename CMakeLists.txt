cmake_minimum_required(VERSION 2.8)

project(Tutorial)

# should we use our own math functions?
option (USE_MYMATH "Use tutorial provided math implementation" ON) 

# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

# does this system provide the log and exp functions?
include (CheckFunctionExists)
check_function_exists (log HAVE_LOG)
check_function_exists (exp HAVE_EXP)
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  )
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# add the MathFunctions library?
if (USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
  add_subdirectory (MathFunctions)
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)
 
# add the executable
add_executable (tutorial tutorial.cxx)
target_link_libraries (tutorial  ${EXTRA_LIBS})

# add the install targets
install (TARGETS tutorial DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)

# enable testing
enable_testing ()

macro (do_test arg result)
	add_test (TutorialComp${arg} Tutorial ${arg})
	set_tests_properties (TutorialComp${arg} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

# does the application run
add_test (TutorialRuns Tutorial 25)

# does it sqrt of 25
do_test(25, "25 is 5")

# does it handle negative numbers
do_test(-25, "-25 is 0")

# does it handle small numbers
do_test(0.0001, "0.0001 is 0.01")

# does the usage message work?
add_test (TutorialUsage Tutorial)
set_tests_properties (TutorialUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")
