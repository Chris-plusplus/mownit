# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(symengine_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(symengine_FRAMEWORKS_FOUND_RELEASE "${symengine_FRAMEWORKS_RELEASE}" "${symengine_FRAMEWORK_DIRS_RELEASE}")

set(symengine_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET symengine_DEPS_TARGET)
    add_library(symengine_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET symengine_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${symengine_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${symengine_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:gmp::gmp>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### symengine_DEPS_TARGET to all of them
conan_package_library_targets("${symengine_LIBS_RELEASE}"    # libraries
                              "${symengine_LIB_DIRS_RELEASE}" # package_libdir
                              "${symengine_BIN_DIRS_RELEASE}" # package_bindir
                              "${symengine_LIBRARY_TYPE_RELEASE}"
                              "${symengine_IS_HOST_WINDOWS_RELEASE}"
                              symengine_DEPS_TARGET
                              symengine_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "symengine"    # package_name
                              "${symengine_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${symengine_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Release ########################################
    set_property(TARGET symengine::symengine
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Release>:${symengine_OBJECTS_RELEASE}>
                 $<$<CONFIG:Release>:${symengine_LIBRARIES_TARGETS}>
                 )

    if("${symengine_LIBS_RELEASE}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET symengine::symengine
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     symengine_DEPS_TARGET)
    endif()

    set_property(TARGET symengine::symengine
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Release>:${symengine_LINKER_FLAGS_RELEASE}>)
    set_property(TARGET symengine::symengine
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Release>:${symengine_INCLUDE_DIRS_RELEASE}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET symengine::symengine
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Release>:${symengine_LIB_DIRS_RELEASE}>)
    set_property(TARGET symengine::symengine
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Release>:${symengine_COMPILE_DEFINITIONS_RELEASE}>)
    set_property(TARGET symengine::symengine
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Release>:${symengine_COMPILE_OPTIONS_RELEASE}>)

########## For the modules (FindXXX)
set(symengine_LIBRARIES_RELEASE symengine::symengine)
