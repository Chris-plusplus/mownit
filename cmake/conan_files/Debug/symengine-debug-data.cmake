########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(symengine_COMPONENT_NAMES "")
if(DEFINED symengine_FIND_DEPENDENCY_NAMES)
  list(APPEND symengine_FIND_DEPENDENCY_NAMES gmp)
  list(REMOVE_DUPLICATES symengine_FIND_DEPENDENCY_NAMES)
else()
  set(symengine_FIND_DEPENDENCY_NAMES gmp)
endif()
set(gmp_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(symengine_PACKAGE_FOLDER_DEBUG "C:/Users/Chris/.conan2/p/b/symen0f1ce1cda3022/p")
set(symengine_BUILD_MODULES_PATHS_DEBUG )


set(symengine_INCLUDE_DIRS_DEBUG "${symengine_PACKAGE_FOLDER_DEBUG}/include")
set(symengine_RES_DIRS_DEBUG )
set(symengine_DEFINITIONS_DEBUG )
set(symengine_SHARED_LINK_FLAGS_DEBUG )
set(symengine_EXE_LINK_FLAGS_DEBUG )
set(symengine_OBJECTS_DEBUG )
set(symengine_COMPILE_DEFINITIONS_DEBUG )
set(symengine_COMPILE_OPTIONS_C_DEBUG )
set(symengine_COMPILE_OPTIONS_CXX_DEBUG )
set(symengine_LIB_DIRS_DEBUG "${symengine_PACKAGE_FOLDER_DEBUG}/lib")
set(symengine_BIN_DIRS_DEBUG )
set(symengine_LIBRARY_TYPE_DEBUG STATIC)
set(symengine_IS_HOST_WINDOWS_DEBUG 1)
set(symengine_LIBS_DEBUG symengine)
set(symengine_SYSTEM_LIBS_DEBUG )
set(symengine_FRAMEWORK_DIRS_DEBUG )
set(symengine_FRAMEWORKS_DEBUG )
set(symengine_BUILD_DIRS_DEBUG )
set(symengine_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(symengine_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${symengine_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${symengine_COMPILE_OPTIONS_C_DEBUG}>")
set(symengine_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${symengine_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${symengine_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${symengine_EXE_LINK_FLAGS_DEBUG}>")


set(symengine_COMPONENTS_DEBUG )