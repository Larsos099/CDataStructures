cmake_minimum_required(VERSION 3.15)
project(ExampleExes C)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}       
    ${CMAKE_CURRENT_SOURCE_DIR}/..     
)


file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")


foreach(src_file ${SOURCES})
    get_filename_component(exe_name ${src_file} NAME_WE)
    add_executable(${exe_name} ${src_file})
endforeach()
