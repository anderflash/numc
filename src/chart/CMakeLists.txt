set(NUMC_SRCS line.c chart.c cwindow.c)
add_library(numc_chart SHARED ${NUMC_SRCS})
INSTALL(TARGETS numc_chart LIBRARY DESTINATION lib)
