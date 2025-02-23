# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(openh264_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(openh264_FRAMEWORKS_FOUND_DEBUG "${openh264_FRAMEWORKS_DEBUG}" "${openh264_FRAMEWORK_DIRS_DEBUG}")

set(openh264_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET openh264_DEPS_TARGET)
    add_library(openh264_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET openh264_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${openh264_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${openh264_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### openh264_DEPS_TARGET to all of them
conan_package_library_targets("${openh264_LIBS_DEBUG}"    # libraries
                              "${openh264_LIB_DIRS_DEBUG}" # package_libdir
                              "${openh264_BIN_DIRS_DEBUG}" # package_bindir
                              "${openh264_LIBRARY_TYPE_DEBUG}"
                              "${openh264_IS_HOST_WINDOWS_DEBUG}"
                              openh264_DEPS_TARGET
                              openh264_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "openh264"    # package_name
                              "${openh264_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${openh264_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Debug ########################################
    set_property(TARGET openh264::openh264
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Debug>:${openh264_OBJECTS_DEBUG}>
                 $<$<CONFIG:Debug>:${openh264_LIBRARIES_TARGETS}>
                 )

    if("${openh264_LIBS_DEBUG}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET openh264::openh264
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     openh264_DEPS_TARGET)
    endif()

    set_property(TARGET openh264::openh264
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Debug>:${openh264_LINKER_FLAGS_DEBUG}>)
    set_property(TARGET openh264::openh264
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Debug>:${openh264_INCLUDE_DIRS_DEBUG}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET openh264::openh264
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Debug>:${openh264_LIB_DIRS_DEBUG}>)
    set_property(TARGET openh264::openh264
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Debug>:${openh264_COMPILE_DEFINITIONS_DEBUG}>)
    set_property(TARGET openh264::openh264
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Debug>:${openh264_COMPILE_OPTIONS_DEBUG}>)

########## For the modules (FindXXX)
set(openh264_LIBRARIES_DEBUG openh264::openh264)
