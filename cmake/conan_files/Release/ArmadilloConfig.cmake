########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(Armadillo_FIND_QUIETLY)
    set(Armadillo_MESSAGE_MODE VERBOSE)
else()
    set(Armadillo_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/ArmadilloTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${armadillo_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(Armadillo_VERSION_STRING "12.6.4")
set(Armadillo_INCLUDE_DIRS ${armadillo_INCLUDE_DIRS_RELEASE} )
set(Armadillo_INCLUDE_DIR ${armadillo_INCLUDE_DIRS_RELEASE} )
set(Armadillo_LIBRARIES ${armadillo_LIBRARIES_RELEASE} )
set(Armadillo_DEFINITIONS ${armadillo_DEFINITIONS_RELEASE} )

# Only the first installed configuration is included to avoid the collision
foreach(_BUILD_MODULE ${armadillo_BUILD_MODULES_PATHS_RELEASE} )
    message(${Armadillo_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


