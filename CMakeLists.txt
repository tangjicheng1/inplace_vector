cmake_minimum_required(VERSION 3.10)

# 项目信息
project(InplaceVector VERSION 1.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR})

# 查找 example 目录中的所有 .cpp 文件
file(GLOB EXAMPLE_SOURCES "example/*.cpp")

# 为每个源文件创建一个可执行文件
foreach(source_file ${EXAMPLE_SOURCES})
    # 获取文件名，不带扩展名
    get_filename_component(file_name ${source_file} NAME_WE)
    
    # 创建可执行文件
    add_executable(${file_name} ${source_file})
    
    # 设置可执行文件的编译选项（如果需要的话）
    # target_compile_options(${file_name} PRIVATE ...)
    
    # 链接库（如果有需要的话）
    # target_link_libraries(${file_name} ...)
endforeach()

# 安装头文件
install(FILES inplace_vector.h DESTINATION include)
