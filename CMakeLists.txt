cmake_minimum_required(VERSION 3.10)
project(InplaceVector VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR})

file(GLOB EXAMPLE_SOURCES "example/*.cpp")

foreach(source_file ${EXAMPLE_SOURCES})
    get_filename_component(file_name ${source_file} NAME_WE)
    add_executable(${file_name} ${source_file})
    # target_link_libraries(${file_name} ...)
endforeach()

install(FILES inplace_vector.h DESTINATION include)
