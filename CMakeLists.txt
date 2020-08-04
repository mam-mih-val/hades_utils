cmake_minimum_required(VERSION 3.15)
project(hades_utils)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
list(APPEND CMAKE_PREFIX_PATH $ENV{AnalysisTree_HOME})
list(APPEND CMAKE_PREFIX_PATH ${AnalysisTree_HOME})

find_package(ROOT REQUIRED COMPONENTS RIO Tree)
find_package(AnalysisTree REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall")
include(${ROOT_USE_FILE})

include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
        ${ROOT_INCLUDE_DIRS}
        ${AnalysisTree_INCLUDE_DIR}
)
link_directories(
        ${CMAKE_SOURCE_DIR}
        ${AnalysisTree_LIBRARY_DIR}
)

set(HEADERS
        src/constants.h
        src/centrality.h
        src/au123_cuts.h
        src/ag123_cuts.h
        src/cuts.h
        )

set(SOURCES
        src/centrality.cc
        src/cuts.cc
        )

set(${PROJECT_NAME}_INCLUDE_DIR "include")
set(${PROJECT_NAME}_LIBRARY_DIR "lib")

add_library(HadesUtils SHARED ${SOURCES})

install(TARGETS HadesUtils DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)