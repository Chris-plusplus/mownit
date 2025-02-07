# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(gmp_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(gmp_FRAMEWORKS_FOUND_DEBUG "${gmp_FRAMEWORKS_DEBUG}" "${gmp_FRAMEWORK_DIRS_DEBUG}")

set(gmp_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET gmp_DEPS_TARGET)
    add_library(gmp_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET gmp_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${gmp_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${gmp_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:gmp::libgmp>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### gmp_DEPS_TARGET to all of them
conan_package_library_targets("${gmp_LIBS_DEBUG}"    # libraries
                              "${gmp_LIB_DIRS_DEBUG}" # package_libdir
                              "${gmp_BIN_DIRS_DEBUG}" # package_bindir
                              "${gmp_LIBRARY_TYPE_DEBUG}"
                              "${gmp_IS_HOST_WINDOWS_DEBUG}"
                              gmp_DEPS_TARGET
                              gmp_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "gmp"    # package_name
                              "${gmp_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${gmp_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## COMPONENTS TARGET PROPERTIES Debug ########################################

    ########## COMPONENT gmp::gmpxx #############

        set(gmp_gmp_gmpxx_FRAMEWORKS_FOUND_DEBUG "")
        conan_find_apple_frameworks(gmp_gmp_gmpxx_FRAMEWORKS_FOUND_DEBUG "${gmp_gmp_gmpxx_FRAMEWORKS_DEBUG}" "${gmp_gmp_gmpxx_FRAMEWORK_DIRS_DEBUG}")

        set(gmp_gmp_gmpxx_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET gmp_gmp_gmpxx_DEPS_TARGET)
            add_library(gmp_gmp_gmpxx_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET gmp_gmp_gmpxx_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Debug>:${gmp_gmp_gmpxx_FRAMEWORKS_FOUND_DEBUG}>
                     $<$<CONFIG:Debug>:${gmp_gmp_gmpxx_SYSTEM_LIBS_DEBUG}>
                     $<$<CONFIG:Debug>:${gmp_gmp_gmpxx_DEPENDENCIES_DEBUG}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'gmp_gmp_gmpxx_DEPS_TARGET' to all of them
        conan_package_library_targets("${gmp_gmp_gmpxx_LIBS_DEBUG}"
                              "${gmp_gmp_gmpxx_LIB_DIRS_DEBUG}"
                              "${gmp_gmp_gmpxx_BIN_DIRS_DEBUG}" # package_bindir
                              "${gmp_gmp_gmpxx_LIBRARY_TYPE_DEBUG}"
                              "${gmp_gmp_gmpxx_IS_HOST_WINDOWS_DEBUG}"
                              gmp_gmp_gmpxx_DEPS_TARGET
                              gmp_gmp_gmpxx_LIBRARIES_TARGETS
                              "_DEBUG"
                              "gmp_gmp_gmpxx"
                              "${gmp_gmp_gmpxx_NO_SONAME_MODE_DEBUG}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET gmp::gmpxx
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Debug>:${gmp_gmp_gmpxx_OBJECTS_DEBUG}>
                     $<$<CONFIG:Debug>:${gmp_gmp_gmpxx_LIBRARIES_TARGETS}>
                     )

        if("${gmp_gmp_gmpxx_LIBS_DEBUG}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET gmp::gmpxx
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         gmp_gmp_gmpxx_DEPS_TARGET)
        endif()

        set_property(TARGET gmp::gmpxx APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Debug>:${gmp_gmp_gmpxx_LINKER_FLAGS_DEBUG}>)
        set_property(TARGET gmp::gmpxx APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Debug>:${gmp_gmp_gmpxx_INCLUDE_DIRS_DEBUG}>)
        set_property(TARGET gmp::gmpxx APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Debug>:${gmp_gmp_gmpxx_LIB_DIRS_DEBUG}>)
        set_property(TARGET gmp::gmpxx APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Debug>:${gmp_gmp_gmpxx_COMPILE_DEFINITIONS_DEBUG}>)
        set_property(TARGET gmp::gmpxx APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Debug>:${gmp_gmp_gmpxx_COMPILE_OPTIONS_DEBUG}>)

    ########## COMPONENT gmp::libgmp #############

        set(gmp_gmp_libgmp_FRAMEWORKS_FOUND_DEBUG "")
        conan_find_apple_frameworks(gmp_gmp_libgmp_FRAMEWORKS_FOUND_DEBUG "${gmp_gmp_libgmp_FRAMEWORKS_DEBUG}" "${gmp_gmp_libgmp_FRAMEWORK_DIRS_DEBUG}")

        set(gmp_gmp_libgmp_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET gmp_gmp_libgmp_DEPS_TARGET)
            add_library(gmp_gmp_libgmp_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET gmp_gmp_libgmp_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Debug>:${gmp_gmp_libgmp_FRAMEWORKS_FOUND_DEBUG}>
                     $<$<CONFIG:Debug>:${gmp_gmp_libgmp_SYSTEM_LIBS_DEBUG}>
                     $<$<CONFIG:Debug>:${gmp_gmp_libgmp_DEPENDENCIES_DEBUG}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'gmp_gmp_libgmp_DEPS_TARGET' to all of them
        conan_package_library_targets("${gmp_gmp_libgmp_LIBS_DEBUG}"
                              "${gmp_gmp_libgmp_LIB_DIRS_DEBUG}"
                              "${gmp_gmp_libgmp_BIN_DIRS_DEBUG}" # package_bindir
                              "${gmp_gmp_libgmp_LIBRARY_TYPE_DEBUG}"
                              "${gmp_gmp_libgmp_IS_HOST_WINDOWS_DEBUG}"
                              gmp_gmp_libgmp_DEPS_TARGET
                              gmp_gmp_libgmp_LIBRARIES_TARGETS
                              "_DEBUG"
                              "gmp_gmp_libgmp"
                              "${gmp_gmp_libgmp_NO_SONAME_MODE_DEBUG}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET gmp::libgmp
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Debug>:${gmp_gmp_libgmp_OBJECTS_DEBUG}>
                     $<$<CONFIG:Debug>:${gmp_gmp_libgmp_LIBRARIES_TARGETS}>
                     )

        if("${gmp_gmp_libgmp_LIBS_DEBUG}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET gmp::libgmp
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         gmp_gmp_libgmp_DEPS_TARGET)
        endif()

        set_property(TARGET gmp::libgmp APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Debug>:${gmp_gmp_libgmp_LINKER_FLAGS_DEBUG}>)
        set_property(TARGET gmp::libgmp APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Debug>:${gmp_gmp_libgmp_INCLUDE_DIRS_DEBUG}>)
        set_property(TARGET gmp::libgmp APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Debug>:${gmp_gmp_libgmp_LIB_DIRS_DEBUG}>)
        set_property(TARGET gmp::libgmp APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Debug>:${gmp_gmp_libgmp_COMPILE_DEFINITIONS_DEBUG}>)
        set_property(TARGET gmp::libgmp APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Debug>:${gmp_gmp_libgmp_COMPILE_OPTIONS_DEBUG}>)

    ########## AGGREGATED GLOBAL TARGET WITH THE COMPONENTS #####################
    set_property(TARGET gmp::gmp APPEND PROPERTY INTERFACE_LINK_LIBRARIES gmp::gmpxx)
    set_property(TARGET gmp::gmp APPEND PROPERTY INTERFACE_LINK_LIBRARIES gmp::libgmp)

########## For the modules (FindXXX)
set(gmp_LIBRARIES_DEBUG gmp::gmp)
