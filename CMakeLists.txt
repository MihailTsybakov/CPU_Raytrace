cmake_minimum_required(VERSION 3.1)

project(Raytrace)

include_directories(${PROJECT_SOURCE_DIR})

set(RAYTRACE_SRC main.cpp Figures.cpp reader.cpp auxiliary_funcs.cpp raytrace.cpp)
set(RAYTRACE_HDR Figures.h reader.h exceptions.h auxiliary_funcs.h raytrace.h)

add_executable(${PROJECT_NAME} ${RAYTRACE_SRC} ${RAYTRACE_HDR})