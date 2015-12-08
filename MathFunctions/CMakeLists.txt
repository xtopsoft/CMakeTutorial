add_library(MathFunctions mysqrt.cxx)

install (TARGETS MathFunctions ARCHIVE DESTINATION bin)
install (FILES MathFunctions.h DESTINATION include)