########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(OpenCV_FIND_QUIETLY)
    set(OpenCV_MESSAGE_MODE VERBOSE)
else()
    set(OpenCV_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/OpenCVTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${opencv_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(OpenCV_VERSION_STRING "4.8.1")
set(OpenCV_INCLUDE_DIRS ${opencv_INCLUDE_DIRS_RELEASE} )
set(OpenCV_INCLUDE_DIR ${opencv_INCLUDE_DIRS_RELEASE} )
set(OpenCV_LIBRARIES ${opencv_LIBRARIES_RELEASE} )
set(OpenCV_DEFINITIONS ${opencv_DEFINITIONS_RELEASE} )

# Only the first installed configuration is included to avoid the collision
foreach(_BUILD_MODULE ${opencv_BUILD_MODULES_PATHS_RELEASE} )
    message(${OpenCV_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


