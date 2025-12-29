# 1. 指定 CMake 最低版本要求，3.10 是比较通用的版本
cmake_minimum_required(VERSION 3.10)

# 2. 定义项目名称，指定语言为 C++
project(HelloCMake CXX)

# 3. 生成可执行文件 hello_cmake，源文件是 main.cpp
add_executable(test2 test2.cpp math.cpp math.h)

# add_executable(test2 math.cpp math.h)