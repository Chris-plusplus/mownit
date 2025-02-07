cmake_minimum_required(VERSION 3.19)

project("mownit")

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(NOFILE=0)
add_compile_definitions(NOPLOT=0)

if (MSVC)
	add_compile_options("/Za")
	add_compile_options("/Zc:__cplusplus")
	add_compile_options("/Zc:preprocessor")
	add_compile_options("/experimental:c11atomics")
	add_compile_options("/permissive-")
	add_compile_definitions(NOMINMAX)
endif (MSVC)

#set(MOWNIT_FORCE_CONAN_INSTALL TRUE)

# check build type
if(
	"${CMAKE_CONFIGURATION_TYPES}" STREQUAL Debug
	OR "${CMAKE_BUILD_TYPE}" STREQUAL Debug
	OR "${CMAKE_CONFIGURATION_TYPES}" STREQUAL "RelWithDebInfo"
	OR "${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo"
)
	set(MOWNIT_DEBUG TRUE)
	set(MOWNIT_RELEASE FALSE)

	set(MOWNIT_BUILD_TYPE "Debug")
	
	add_definitions(-DMOWNIT_DEBUG=1)
	add_definitions(-DMOWNIT_RELEASE=0)
else()
	set(MOWNIT_DEBUG FALSE)
	set(MOWNIT_RELEASE TRUE)
	
	set(MOWNIT_BUILD_TYPE "Release")
	
	add_definitions(-DMOWNIT_DEBUG=0)
	add_definitions(-DMOWNIT_RELEASE=1)
endif()

message(STATUS "Build mode: ${MOWNIT_BUILD_TYPE}")

# check if conan is installed
execute_process(
	COMMAND "conan" "--version"
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	OUTPUT_VARIABLE CONAN_CHECK_OUT
)
if(NOT CONAN_CHECK_OUT MATCHES ".?Conan.?")
	message(FATAL_ERROR "Conan not found")
else()
	message(STATUS "Conan present")
endif()

# check for conan files
if(MOWNIT_FORCE_CONAN_INSTALL OR NOT EXISTS "${PROJECT_SOURCE_DIR}/cmake/conan_files/${MOWNIT_BUILD_TYPE}/conan_toolchain.cmake")
	if(MOWNIT_FORCE_CONAN_INSTALL)
		message(STATUS "Forced Conan configuration for ${MOWNIT_BUILD_TYPE} mode")
	else()
		message(STATUS "Conan files not found for ${MOWNIT_BUILD_TYPE} mode, configuring conan for ${MOWNIT_BUILD_TYPE} mode")
	endif()

	file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/cmake/conan_files/${MOWNIT_BUILD_TYPE}/")

	# option only for MSCV
	if(MSVC)
		set(MOWNIT_CONAN_COMPILER_RUNTIME_TYPE "-s:b compiler.runtime_type=${MOWNIT_BUILD_TYPE} -s:h compiler.runtime_type=${MOWNIT_BUILD_TYPE}")
	endif()

	# install conan requirements
	execute_process(
		COMMAND conan install . -s:b build_type=${MOWNIT_BUILD_TYPE} -s:b compiler.cppstd=20 -s:h build_type=${MOWNIT_BUILD_TYPE} -s:h compiler.cppstd=20 ${MOWNIT_CONAN_INSTALL_RUNTIME_TYPE} ${MOWNIT_CONAN_PACKAGE_MANAGER} -of=cmake/conan_files/${MOWNIT_BUILD_TYPE} --build=missing
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		OUTPUT_VARIABLE MOWNIT_CONAN_INSTALL_OUTPUT
		RESULT_VARIABLE MOWNIT_CONAN_INSTALL_RESULT
		COMMAND_ECHO STDOUT
	)

	# check conan result
	if(NOT ${MOWNIT_CONAN_INSTALL_RESULT} EQUAL 0)
		file(REMOVE_RECURSE "${PROJECT_SOURCE_DIR}/cmake/conan_files/${MOWNIT_BUILD_TYPE}/")
		message(FATAL_ERROR "Conan installation failed")
	else()
		message(STATUS "Conan installation succeded")
	endif()
else()
	message(STATUS "Conan files found for ${MOWNIT_BUILD_TYPE} mode") 
endif()

# manual include conan toolchain
include("${PROJECT_SOURCE_DIR}/cmake/conan_files/${MOWNIT_BUILD_TYPE}/conan_toolchain.cmake")
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/conan_files/${MOWNIT_BUILD_TYPE})
foreach(path ${CMAKE_INCLUDE_PATH})
	#message(STATUS ${path})
endforeach()
add_compile_definitions(CVPLOT_HEADER_ONLY)
include_directories(${CMAKE_INCLUDE_PATH})

#foreach(lib_paths ${CMAKE_LIBRARY_PATH})
#    file(GLOB test_lib ${lib_paths}/**.lib)
#    foreach(lib_path ${test_lib})
#        list(PREPEND MOWNIT_LIBS ${lib_path})
#		#message(STATUS ${lib_path})
#    endforeach()
#endforeach()
#message(STATUS ${MOWNIT_LIBS})

file(GLOB_RECURSE LAB_SOURCES RELATIVE ${PROJECT_SOURCE_DIR}/labs labs/*.cpp)

find_package(opencv CONFIG REQUIRED)
find_package(cvplot CONFIG REQUIRED)
find_package(symengine CONFIG REQUIRED)

file(GLOB_RECURSE MY_SOURCES src/**.cpp)

foreach(LAB_FILE ${LAB_SOURCES})
	string(LENGTH ${LAB_FILE} LAB_FILE_LEN)
	math(EXPR LAB_FILE_LEN "${LAB_FILE_LEN}-4")
	string(SUBSTRING ${LAB_FILE} 0 ${LAB_FILE_LEN} LAB)
	message(STATUS ${LAB})
	add_executable(${LAB} "labs/${LAB}.cpp")
	target_sources(${LAB} PRIVATE ${MY_SOURCES})
	target_include_directories(${LAB} PUBLIC include)
	target_link_libraries(${LAB} CvPlot::CvPlot symengine::symengine)
	if(MSVC)
		add_definitions(/FI"types.hpp")
	else()
		# GCC lub Clang
		add_definitions(-include types.hpp)
	endif()
endforeach()