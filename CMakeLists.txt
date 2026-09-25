cmake_minimum_required(VERSION 3.10)
project(ReprojectionProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(reprojection_test 
    main.cpp 
    src/reprojection.cpp
)