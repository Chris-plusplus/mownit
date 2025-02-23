# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(jbig_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(jbig_FRAMEWORKS_FOUND_DEBUG "${jbig_FRAMEWORKS_DEBUG}" "${jbig_FRAMEWORK_DIRS_DEBUG}")

set(jbig_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET jbig_DEPS_TARGET)
    add_library(jbig_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET jbig_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${jbig_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${jbig_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### jbig_DEPS_TARGET to all of them
conan_package_library_targets("${jbig_LIBS_DEBUG}"    # libraries
                              "${jbig_LIB_DIRS_DEBUG}" # package_libdir
                              "${jbig_BIN_DIRS_DEBUG}" # package_bindir
                              "${jbig_LIBRARY_TYPE_DEBUG}"
                              "${jbig_IS_HOST_WINDOWS_DEBUG}"
                              jbig_DEPS_TARGET
                              jbig_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "jbig"    # package_name
                              "${jbig_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${jbig_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Debug ########################################
    set_property(TARGET jbig::jbig
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Debug>:${jbig_OBJECTS_DEBUG}>
                 $<$<CONFIG:Debug>:${jbig_LIBRARIES_TARGETS}>
                 )

    if("${jbig_LIBS_DEBUG}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET jbig::jbig
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     jbig_DEPS_TARGET)
    endif()

    set_property(TARGET jbig::jbig
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Debug>:${jbig_LINKER_FLAGS_DEBUG}>)
    set_property(TARGET jbig::jbig
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Debug>:${jbig_INCLUDE_DIRS_DEBUG}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET jbig::jbig
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Debug>:${jbig_LIB_DIRS_DEBUG}>)
    set_property(TARGET jbig::jbig
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Debug>:${jbig_COMPILE_DEFINITIONS_DEBUG}>)
    set_property(TARGET jbig::jbig
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Debug>:${jbig_COMPILE_OPTIONS_DEBUG}>)

########## For the modules (FindXXX)
set(jbig_LIBRARIES_DEBUG jbig::jbig)
