########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(CvPlot_FIND_QUIETLY)
    set(CvPlot_MESSAGE_MODE VERBOSE)
else()
    set(CvPlot_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/CvPlotTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${cvplot_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(CvPlot_VERSION_STRING "1.2.2")
set(CvPlot_INCLUDE_DIRS ${cvplot_INCLUDE_DIRS_RELEASE} )
set(CvPlot_INCLUDE_DIR ${cvplot_INCLUDE_DIRS_RELEASE} )
set(CvPlot_LIBRARIES ${cvplot_LIBRARIES_RELEASE} )
set(CvPlot_DEFINITIONS ${cvplot_DEFINITIONS_RELEASE} )

# Only the first installed configuration is included to avoid the collision
foreach(_BUILD_MODULE ${cvplot_BUILD_MODULES_PATHS_RELEASE} )
    message(${CvPlot_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


