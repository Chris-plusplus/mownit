# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(openblas_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(openblas_FRAMEWORKS_FOUND_DEBUG "${openblas_FRAMEWORKS_DEBUG}" "${openblas_FRAMEWORK_DIRS_DEBUG}")

set(openblas_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET openblas_DEPS_TARGET)
    add_library(openblas_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET openblas_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${openblas_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${openblas_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### openblas_DEPS_TARGET to all of them
conan_package_library_targets("${openblas_LIBS_DEBUG}"    # libraries
                              "${openblas_LIB_DIRS_DEBUG}" # package_libdir
                              "${openblas_BIN_DIRS_DEBUG}" # package_bindir
                              "${openblas_LIBRARY_TYPE_DEBUG}"
                              "${openblas_IS_HOST_WINDOWS_DEBUG}"
                              openblas_DEPS_TARGET
                              openblas_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "openblas"    # package_name
                              "${openblas_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${openblas_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## COMPONENTS TARGET PROPERTIES Debug ########################################

    ########## COMPONENT OpenBLAS::pthread #############

        set(openblas_OpenBLAS_pthread_FRAMEWORKS_FOUND_DEBUG "")
        conan_find_apple_frameworks(openblas_OpenBLAS_pthread_FRAMEWORKS_FOUND_DEBUG "${openblas_OpenBLAS_pthread_FRAMEWORKS_DEBUG}" "${openblas_OpenBLAS_pthread_FRAMEWORK_DIRS_DEBUG}")

        set(openblas_OpenBLAS_pthread_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET openblas_OpenBLAS_pthread_DEPS_TARGET)
            add_library(openblas_OpenBLAS_pthread_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET openblas_OpenBLAS_pthread_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Debug>:${openblas_OpenBLAS_pthread_FRAMEWORKS_FOUND_DEBUG}>
                     $<$<CONFIG:Debug>:${openblas_OpenBLAS_pthread_SYSTEM_LIBS_DEBUG}>
                     $<$<CONFIG:Debug>:${openblas_OpenBLAS_pthread_DEPENDENCIES_DEBUG}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'openblas_OpenBLAS_pthread_DEPS_TARGET' to all of them
        conan_package_library_targets("${openblas_OpenBLAS_pthread_LIBS_DEBUG}"
                              "${openblas_OpenBLAS_pthread_LIB_DIRS_DEBUG}"
                              "${openblas_OpenBLAS_pthread_BIN_DIRS_DEBUG}" # package_bindir
                              "${openblas_OpenBLAS_pthread_LIBRARY_TYPE_DEBUG}"
                              "${openblas_OpenBLAS_pthread_IS_HOST_WINDOWS_DEBUG}"
                              openblas_OpenBLAS_pthread_DEPS_TARGET
                              openblas_OpenBLAS_pthread_LIBRARIES_TARGETS
                              "_DEBUG"
                              "openblas_OpenBLAS_pthread"
                              "${openblas_OpenBLAS_pthread_NO_SONAME_MODE_DEBUG}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET OpenBLAS::pthread
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Debug>:${openblas_OpenBLAS_pthread_OBJECTS_DEBUG}>
                     $<$<CONFIG:Debug>:${openblas_OpenBLAS_pthread_LIBRARIES_TARGETS}>
                     )

        if("${openblas_OpenBLAS_pthread_LIBS_DEBUG}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET OpenBLAS::pthread
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         openblas_OpenBLAS_pthread_DEPS_TARGET)
        endif()

        set_property(TARGET OpenBLAS::pthread APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Debug>:${openblas_OpenBLAS_pthread_LINKER_FLAGS_DEBUG}>)
        set_property(TARGET OpenBLAS::pthread APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Debug>:${openblas_OpenBLAS_pthread_INCLUDE_DIRS_DEBUG}>)
        set_property(TARGET OpenBLAS::pthread APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Debug>:${openblas_OpenBLAS_pthread_LIB_DIRS_DEBUG}>)
        set_property(TARGET OpenBLAS::pthread APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Debug>:${openblas_OpenBLAS_pthread_COMPILE_DEFINITIONS_DEBUG}>)
        set_property(TARGET OpenBLAS::pthread APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Debug>:${openblas_OpenBLAS_pthread_COMPILE_OPTIONS_DEBUG}>)

    ########## AGGREGATED GLOBAL TARGET WITH THE COMPONENTS #####################
    set_property(TARGET OpenBLAS::OpenBLAS APPEND PROPERTY INTERFACE_LINK_LIBRARIES OpenBLAS::pthread)

########## For the modules (FindXXX)
set(openblas_LIBRARIES_DEBUG OpenBLAS::OpenBLAS)
