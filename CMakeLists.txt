cmake_minimum_required(VERSION 2.8)
project(numc)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
include_directories(include)


FUNCTION(JOIN VALUES GLUE OUTPUT)
  STRING (REGEX REPLACE "([^\\]|^);" "\\1${GLUE}" _TMP_STR "${VALUES}")
  STRING (REGEX REPLACE "[\\](.)" "\\1" _TMP_STR "${_TMP_STR}") #fixes escaping
  SET (${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
ENDFUNCTION()

# Copy resources to build
file(COPY rsc DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Process and generate headers
execute_process(COMMAND cog.py -d a.h.py.in
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/nc/core
                OUTPUT_FILE a.h.in
                RESULT_VARIABLE RESULT)
set(ANAMES au8 au16 au32 au64 ai8 ai16 ai32 ai64 af ad)
set(ATYPES uint8_t uint16_t uint32_t uint64_t int8_t int16_t int32_t int64_t float double)
list(LENGTH ANAMES LEN_ANAMES)
math(EXPR LEN_ANAMES_M "${LEN_ANAMES} - 1")
foreach(IDX RANGE ${LEN_ANAMES_M})
  list(GET ANAMES ${IDX} ANAME)
  list(GET ATYPES ${IDX} ATYPE)
  string(TOUPPER ${ANAME} ANAME_UPPER)
  configure_file(include/nc/core/a.h.in include/nc/core/${ANAME}.h @ONLY)
endforeach()

set(NUMC_HDRS include/numc.h)

# ------------------
# Zlib
# ------------------
find_package(ZLIB REQUIRED)
if(${ZLIB_FOUND})
  include_directories(${ZLIB_INCLUDE_DIRS})
  add_definitions(-DHAVE_ZLIB)
endif()

# ADD NUMC LIBRARY
add_subdirectory(src)
LIST(APPEND PKG_CONFIG_LIBS "-lnumc_core")
LIST(APPEND PKG_CONFIG_LIBS "-lnumc_img")

# ADD TESTS
include(CTest)
if(${BUILD_TESTING})
  enable_testing()
  SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")
  SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
  SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

  add_subdirectory(lib)
  add_subdirectory(test)
endif()

# INSTALL MODULES
INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/rsc/ DESTINATION share/nc)
INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)
INSTALL(DIRECTORY ${CMAKE_BINARY_DIR}/include/ DESTINATION include)
INSTALL(FILES    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc" DESTINATION lib/pkgconfig)
# IF(BUILD_CORE)

# ENDIF(BUILD_CORE)
# IF(BUILD_IMG)

# ENDIF(BUILD_IMG)
# IF(BUILD_GUI)
#  INSTALL(TARGETS   nc_gui       LIBRARY DESTINATION lib)
#ENDIF(BUILD_GUI)
#IF(BUILD_CHART)
#  INSTALL(TARGETS   nc_chart     LIBRARY DESTINATION lib)
#ENDIF(BUILD_CHART)

#============================================================== PKG-CONFIG
# SET(PKG_CONFIG_REQUIRES    gtk+-3.0)
SET(PKG_CONFIG_REQUIRES   )
SET(PKG_CONFIG_LIBDIR      "\${prefix}/lib")
SET(PKG_CONFIG_INCLUDEDIR  "\${prefix}/include")
LIST(APPEND PKG_CONFIG_LIBS "-L\${libdir} -lpng -ljpeg -lz")
JOIN("${PKG_CONFIG_LIBS}" " " PKG_CONFIG_LIBS)
SET(PKG_CONFIG_CFLAGS      "-I\${includedir}")
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pc.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
)
