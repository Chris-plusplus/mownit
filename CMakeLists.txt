cmake_minimum_required(VERSION 3.19)

project("mownit")

set(CMAKE_CXX_STANDARD 23)

if (MSVC)
    add_compile_options("/Zc:__cplusplus")
    add_compile_options("/Zc:preprocessor")
endif (MSVC)

file(GLOB_RECURSE MY_SOURCES src/*.cpp)

foreach(LAB "lab1")
    add_executable(${LAB} "labs/${LAB}.cpp")
    target_include_directories(${LAB} PUBLIC include)
    target_sources(${LAB} PUBLIC ${MY_SOURCES})
endforeach() 