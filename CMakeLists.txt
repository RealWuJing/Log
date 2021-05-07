cmake_minimum_required(VERSION 3.0.0)
project(Log VERSION 0.1.0)

include(CTest)
enable_testing()

# add_library(Log Log.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(INSTALL_HEAD_FILES Log.h)

install(FILES ${INSTALL_HEAD_FILES} DESTINATION  ${CMAKE_INSTALL_PREFIX}/include)



