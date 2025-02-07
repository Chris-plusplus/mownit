########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

list(APPEND gmp_COMPONENT_NAMES gmp::libgmp gmp::gmpxx)
list(REMOVE_DUPLICATES gmp_COMPONENT_NAMES)
if(DEFINED gmp_FIND_DEPENDENCY_NAMES)
  list(APPEND gmp_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES gmp_FIND_DEPENDENCY_NAMES)
else()
  set(gmp_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(gmp_PACKAGE_FOLDER_DEBUG "C:/Users/Chris/.conan2/p/b/gmp17d62ddb462a6/p")
set(gmp_BUILD_MODULES_PATHS_DEBUG )


set(gmp_INCLUDE_DIRS_DEBUG "${gmp_PACKAGE_FOLDER_DEBUG}/include")
set(gmp_RES_DIRS_DEBUG )
set(gmp_DEFINITIONS_DEBUG )
set(gmp_SHARED_LINK_FLAGS_DEBUG )
set(gmp_EXE_LINK_FLAGS_DEBUG )
set(gmp_OBJECTS_DEBUG )
set(gmp_COMPILE_DEFINITIONS_DEBUG )
set(gmp_COMPILE_OPTIONS_C_DEBUG )
set(gmp_COMPILE_OPTIONS_CXX_DEBUG )
set(gmp_LIB_DIRS_DEBUG "${gmp_PACKAGE_FOLDER_DEBUG}/lib")
set(gmp_BIN_DIRS_DEBUG )
set(gmp_LIBRARY_TYPE_DEBUG STATIC)
set(gmp_IS_HOST_WINDOWS_DEBUG 1)
set(gmp_LIBS_DEBUG gmpxx gmp)
set(gmp_SYSTEM_LIBS_DEBUG )
set(gmp_FRAMEWORK_DIRS_DEBUG )
set(gmp_FRAMEWORKS_DEBUG )
set(gmp_BUILD_DIRS_DEBUG )
set(gmp_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(gmp_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${gmp_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${gmp_COMPILE_OPTIONS_C_DEBUG}>")
set(gmp_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${gmp_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${gmp_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${gmp_EXE_LINK_FLAGS_DEBUG}>")


set(gmp_COMPONENTS_DEBUG gmp::libgmp gmp::gmpxx)
########### COMPONENT gmp::gmpxx VARIABLES ############################################

set(gmp_gmp_gmpxx_INCLUDE_DIRS_DEBUG "${gmp_PACKAGE_FOLDER_DEBUG}/include")
set(gmp_gmp_gmpxx_LIB_DIRS_DEBUG "${gmp_PACKAGE_FOLDER_DEBUG}/lib")
set(gmp_gmp_gmpxx_BIN_DIRS_DEBUG )
set(gmp_gmp_gmpxx_LIBRARY_TYPE_DEBUG STATIC)
set(gmp_gmp_gmpxx_IS_HOST_WINDOWS_DEBUG 1)
set(gmp_gmp_gmpxx_RES_DIRS_DEBUG )
set(gmp_gmp_gmpxx_DEFINITIONS_DEBUG )
set(gmp_gmp_gmpxx_OBJECTS_DEBUG )
set(gmp_gmp_gmpxx_COMPILE_DEFINITIONS_DEBUG )
set(gmp_gmp_gmpxx_COMPILE_OPTIONS_C_DEBUG "")
set(gmp_gmp_gmpxx_COMPILE_OPTIONS_CXX_DEBUG "")
set(gmp_gmp_gmpxx_LIBS_DEBUG gmpxx)
set(gmp_gmp_gmpxx_SYSTEM_LIBS_DEBUG )
set(gmp_gmp_gmpxx_FRAMEWORK_DIRS_DEBUG )
set(gmp_gmp_gmpxx_FRAMEWORKS_DEBUG )
set(gmp_gmp_gmpxx_DEPENDENCIES_DEBUG gmp::libgmp)
set(gmp_gmp_gmpxx_SHARED_LINK_FLAGS_DEBUG )
set(gmp_gmp_gmpxx_EXE_LINK_FLAGS_DEBUG )
set(gmp_gmp_gmpxx_NO_SONAME_MODE_DEBUG FALSE)

# COMPOUND VARIABLES
set(gmp_gmp_gmpxx_LINKER_FLAGS_DEBUG
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${gmp_gmp_gmpxx_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${gmp_gmp_gmpxx_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${gmp_gmp_gmpxx_EXE_LINK_FLAGS_DEBUG}>
)
set(gmp_gmp_gmpxx_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${gmp_gmp_gmpxx_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${gmp_gmp_gmpxx_COMPILE_OPTIONS_C_DEBUG}>")
########### COMPONENT gmp::libgmp VARIABLES ############################################

set(gmp_gmp_libgmp_INCLUDE_DIRS_DEBUG "${gmp_PACKAGE_FOLDER_DEBUG}/include")
set(gmp_gmp_libgmp_LIB_DIRS_DEBUG "${gmp_PACKAGE_FOLDER_DEBUG}/lib")
set(gmp_gmp_libgmp_BIN_DIRS_DEBUG )
set(gmp_gmp_libgmp_LIBRARY_TYPE_DEBUG STATIC)
set(gmp_gmp_libgmp_IS_HOST_WINDOWS_DEBUG 1)
set(gmp_gmp_libgmp_RES_DIRS_DEBUG )
set(gmp_gmp_libgmp_DEFINITIONS_DEBUG )
set(gmp_gmp_libgmp_OBJECTS_DEBUG )
set(gmp_gmp_libgmp_COMPILE_DEFINITIONS_DEBUG )
set(gmp_gmp_libgmp_COMPILE_OPTIONS_C_DEBUG "")
set(gmp_gmp_libgmp_COMPILE_OPTIONS_CXX_DEBUG "")
set(gmp_gmp_libgmp_LIBS_DEBUG gmp)
set(gmp_gmp_libgmp_SYSTEM_LIBS_DEBUG )
set(gmp_gmp_libgmp_FRAMEWORK_DIRS_DEBUG )
set(gmp_gmp_libgmp_FRAMEWORKS_DEBUG )
set(gmp_gmp_libgmp_DEPENDENCIES_DEBUG )
set(gmp_gmp_libgmp_SHARED_LINK_FLAGS_DEBUG )
set(gmp_gmp_libgmp_EXE_LINK_FLAGS_DEBUG )
set(gmp_gmp_libgmp_NO_SONAME_MODE_DEBUG FALSE)

# COMPOUND VARIABLES
set(gmp_gmp_libgmp_LINKER_FLAGS_DEBUG
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${gmp_gmp_libgmp_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${gmp_gmp_libgmp_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${gmp_gmp_libgmp_EXE_LINK_FLAGS_DEBUG}>
)
set(gmp_gmp_libgmp_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${gmp_gmp_libgmp_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${gmp_gmp_libgmp_COMPILE_OPTIONS_C_DEBUG}>")