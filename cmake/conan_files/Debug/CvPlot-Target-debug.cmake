# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(cvplot_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(cvplot_FRAMEWORKS_FOUND_DEBUG "${cvplot_FRAMEWORKS_DEBUG}" "${cvplot_FRAMEWORK_DIRS_DEBUG}")

set(cvplot_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET cvplot_DEPS_TARGET)
    add_library(cvplot_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET cvplot_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${cvplot_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${cvplot_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:opencv::opencv>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### cvplot_DEPS_TARGET to all of them
conan_package_library_targets("${cvplot_LIBS_DEBUG}"    # libraries
                              "${cvplot_LIB_DIRS_DEBUG}" # package_libdir
                              "${cvplot_BIN_DIRS_DEBUG}" # package_bindir
                              "${cvplot_LIBRARY_TYPE_DEBUG}"
                              "${cvplot_IS_HOST_WINDOWS_DEBUG}"
                              cvplot_DEPS_TARGET
                              cvplot_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "cvplot"    # package_name
                              "${cvplot_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${cvplot_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Debug ########################################
    set_property(TARGET CvPlot::CvPlot
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Debug>:${cvplot_OBJECTS_DEBUG}>
                 $<$<CONFIG:Debug>:${cvplot_LIBRARIES_TARGETS}>
                 )

    if("${cvplot_LIBS_DEBUG}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET CvPlot::CvPlot
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     cvplot_DEPS_TARGET)
    endif()

    set_property(TARGET CvPlot::CvPlot
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Debug>:${cvplot_LINKER_FLAGS_DEBUG}>)
    set_property(TARGET CvPlot::CvPlot
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Debug>:${cvplot_INCLUDE_DIRS_DEBUG}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET CvPlot::CvPlot
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Debug>:${cvplot_LIB_DIRS_DEBUG}>)
    set_property(TARGET CvPlot::CvPlot
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Debug>:${cvplot_COMPILE_DEFINITIONS_DEBUG}>)
    set_property(TARGET CvPlot::CvPlot
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Debug>:${cvplot_COMPILE_OPTIONS_DEBUG}>)

########## For the modules (FindXXX)
set(cvplot_LIBRARIES_DEBUG CvPlot::CvPlot)
