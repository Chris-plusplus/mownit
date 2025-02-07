########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(symengine_FIND_QUIETLY)
    set(symengine_MESSAGE_MODE VERBOSE)
else()
    set(symengine_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/symengineTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${symengine_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(symengine_VERSION_STRING "0.11.2")
set(symengine_INCLUDE_DIRS ${symengine_INCLUDE_DIRS_DEBUG} )
set(symengine_INCLUDE_DIR ${symengine_INCLUDE_DIRS_DEBUG} )
set(symengine_LIBRARIES ${symengine_LIBRARIES_DEBUG} )
set(symengine_DEFINITIONS ${symengine_DEFINITIONS_DEBUG} )

# Only the first installed configuration is included to avoid the collision
foreach(_BUILD_MODULE ${symengine_BUILD_MODULES_PATHS_DEBUG} )
    message(${symengine_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


