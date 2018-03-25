CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(numc)

# SCRIPTS =====================================================================
INCLUDE(CMakeDependentOption)
FIND_PACKAGE (PkgConfig)
FUNCTION(JOIN VALUES GLUE OUTPUT)
  STRING (REGEX REPLACE "([^\\]|^);" "\\1${GLUE}" _TMP_STR "${VALUES}")
  STRING (REGEX REPLACE "[\\](.)" "\\1" _TMP_STR "${_TMP_STR}") #fixes escaping
  SET (${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
ENDFUNCTION()

# CMAKE SETUP =================================================================
OPTION(BUILD_CORE    "" ON)
OPTION(BUILD_OO      "" ON)
OPTION(BUILD_GUI     "" ON)
CMAKE_DEPENDENT_OPTION(BUILD_CHART "Build CHART (DEPS: CORE)" ON "BUILD_CORE" OFF)
CMAKE_DEPENDENT_OPTION(BUILD_IMG   "Build IMG (DEPS: CORE)"   ON "BUILD_CORE" OFF)
SET(CMAKE_C_STANDARD 11)

# DEPENDENCIES ================================================================

# Zlib -------------
FIND_PACKAGE(ZLIB REQUIRED)
IF(${ZLIB_FOUND})
  INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIRS})
  ADD_DEFINITIONS(-DHAVE_ZLIB)
ENDIF()

# GTK 3 ------------
IF(BUILD_GUI STREQUAL "ON" OR BUILD_CHART STREQUAL "ON")
  PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
  INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
ENDIF()

# RESOURCES ===================================================================
FILE(COPY rsc DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# HEADERS =====================================================================
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/include)
INCLUDE_DIRECTORIES(include)
EXECUTE_PROCESS(COMMAND cog.py -d a.h.py.in
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/nc/core
                OUTPUT_FILE a.h.in
                RESULT_VARIABLE RESULT)
SET(ANAMES au8 au16 au32 au64 ai8 ai16 ai32 ai64 af ad)
SET(ATYPES uint8_t uint16_t uint32_t uint64_t int8_t int16_t int32_t int64_t float double)
LIST(LENGTH ANAMES LEN_ANAMES)
MATH(EXPR LEN_ANAMES_M "${LEN_ANAMES} - 1")
FOREACH(IDX RANGE ${LEN_ANAMES_M})
  LIST(GET ANAMES ${IDX} ANAME)
  LIST(GET ATYPES ${IDX} ATYPE)
  STRING(TOUPPER ${ANAME} ANAME_UPPER)
  CONFIGURE_FILE(include/nc/core/a.h.in include/nc/core/${ANAME}.h @ONLY)
ENDFOREACH()

SET(NUMC_HDRS include/numc.h)


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
#=================================================================== DEMOS
ADD_SUBDIRECTORY(demo)
