execute_process(COMMAND cog.py -d a.c.py.in
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                OUTPUT_FILE a.c.in
                RESULT_VARIABLE RESULT)
MESSAGE( STATUS "RESULT_VARIABLE: " ${RESULT})
list(LENGTH ANAMES LEN_ANAMES)
math(EXPR LEN_ANAMES_M "${LEN_ANAMES} - 1")
foreach(IDX RANGE ${LEN_ANAMES_M})
  list(GET ANAMES ${IDX} ANAME)
  list(GET ATYPES ${IDX} ATYPE)
  configure_file(a.c.in ${ANAME}.c @ONLY)
endforeach()
set(NUMC_SRCS au8.c au16.c au32.c au64.c ai8.c ai16.c ai32.c ai64.c af.c ad.c util.c ncz.c)
add_library(numc_core SHARED ${NUMC_SRCS})
INSTALL(TARGETS   numc_core      LIBRARY DESTINATION lib)
