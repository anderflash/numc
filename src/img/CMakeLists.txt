set(NUMC_SRCS io.c)
add_library(numc_img SHARED ${NUMC_SRCS})
INSTALL(TARGETS   numc_img       LIBRARY DESTINATION lib)
