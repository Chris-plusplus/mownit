# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(armadillo_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(armadillo_FRAMEWORKS_FOUND_RELEASE "${armadillo_FRAMEWORKS_RELEASE}" "${armadillo_FRAMEWORK_DIRS_RELEASE}")

set(armadillo_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET armadillo_DEPS_TARGET)
    add_library(armadillo_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET armadillo_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${armadillo_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${armadillo_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:OpenBLAS::OpenBLAS>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### armadillo_DEPS_TARGET to all of them
conan_package_library_targets("${armadillo_LIBS_RELEASE}"    # libraries
                              "${armadillo_LIB_DIRS_RELEASE}" # package_libdir
                              "${armadillo_BIN_DIRS_RELEASE}" # package_bindir
                              "${armadillo_LIBRARY_TYPE_RELEASE}"
                              "${armadillo_IS_HOST_WINDOWS_RELEASE}"
                              armadillo_DEPS_TARGET
                              armadillo_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "armadillo"    # package_name
                              "${armadillo_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${armadillo_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Release ########################################
    set_property(TARGET Armadillo::Armadillo
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Release>:${armadillo_OBJECTS_RELEASE}>
                 $<$<CONFIG:Release>:${armadillo_LIBRARIES_TARGETS}>
                 )

    if("${armadillo_LIBS_RELEASE}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET Armadillo::Armadillo
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     armadillo_DEPS_TARGET)
    endif()

    set_property(TARGET Armadillo::Armadillo
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Release>:${armadillo_LINKER_FLAGS_RELEASE}>)
    set_property(TARGET Armadillo::Armadillo
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Release>:${armadillo_INCLUDE_DIRS_RELEASE}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET Armadillo::Armadillo
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Release>:${armadillo_LIB_DIRS_RELEASE}>)
    set_property(TARGET Armadillo::Armadillo
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Release>:${armadillo_COMPILE_DEFINITIONS_RELEASE}>)
    set_property(TARGET Armadillo::Armadillo
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Release>:${armadillo_COMPILE_OPTIONS_RELEASE}>)

########## For the modules (FindXXX)
set(armadillo_LIBRARIES_RELEASE Armadillo::Armadillo)
