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
set(symengine_PACKAGE_FOLDER_RELEASE "C:/Users/Chris/.conan2/p/symen0456211a49424/p")
set(symengine_BUILD_MODULES_PATHS_RELEASE )


set(symengine_INCLUDE_DIRS_RELEASE "${symengine_PACKAGE_FOLDER_RELEASE}/include")
set(symengine_RES_DIRS_RELEASE )
set(symengine_DEFINITIONS_RELEASE )
set(symengine_SHARED_LINK_FLAGS_RELEASE )
set(symengine_EXE_LINK_FLAGS_RELEASE )
set(symengine_OBJECTS_RELEASE )
set(symengine_COMPILE_DEFINITIONS_RELEASE )
set(symengine_COMPILE_OPTIONS_C_RELEASE )
set(symengine_COMPILE_OPTIONS_CXX_RELEASE )
set(symengine_LIB_DIRS_RELEASE "${symengine_PACKAGE_FOLDER_RELEASE}/lib")
set(symengine_BIN_DIRS_RELEASE )
set(symengine_LIBRARY_TYPE_RELEASE STATIC)
set(symengine_IS_HOST_WINDOWS_RELEASE 1)
set(symengine_LIBS_RELEASE symengine)
set(symengine_SYSTEM_LIBS_RELEASE )
set(symengine_FRAMEWORK_DIRS_RELEASE )
set(symengine_FRAMEWORKS_RELEASE )
set(symengine_BUILD_DIRS_RELEASE )
set(symengine_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(symengine_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${symengine_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${symengine_COMPILE_OPTIONS_C_RELEASE}>")
set(symengine_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${symengine_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${symengine_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${symengine_EXE_LINK_FLAGS_RELEASE}>")


set(symengine_COMPONENTS_RELEASE )