########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(libx265_COMPONENT_NAMES "")
if(DEFINED libx265_FIND_DEPENDENCY_NAMES)
  list(APPEND libx265_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES libx265_FIND_DEPENDENCY_NAMES)
else()
  set(libx265_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(libx265_PACKAGE_FOLDER_RELEASE "C:/Users/Chris/.conan2/p/libx2997b103fcf89a/p")
set(libx265_BUILD_MODULES_PATHS_RELEASE )


set(libx265_INCLUDE_DIRS_RELEASE )
set(libx265_RES_DIRS_RELEASE )
set(libx265_DEFINITIONS_RELEASE )
set(libx265_SHARED_LINK_FLAGS_RELEASE )
set(libx265_EXE_LINK_FLAGS_RELEASE )
set(libx265_OBJECTS_RELEASE )
set(libx265_COMPILE_DEFINITIONS_RELEASE )
set(libx265_COMPILE_OPTIONS_C_RELEASE )
set(libx265_COMPILE_OPTIONS_CXX_RELEASE )
set(libx265_LIB_DIRS_RELEASE "${libx265_PACKAGE_FOLDER_RELEASE}/lib")
set(libx265_BIN_DIRS_RELEASE )
set(libx265_LIBRARY_TYPE_RELEASE STATIC)
set(libx265_IS_HOST_WINDOWS_RELEASE 1)
set(libx265_LIBS_RELEASE x265)
set(libx265_SYSTEM_LIBS_RELEASE )
set(libx265_FRAMEWORK_DIRS_RELEASE )
set(libx265_FRAMEWORKS_RELEASE )
set(libx265_BUILD_DIRS_RELEASE )
set(libx265_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(libx265_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${libx265_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${libx265_COMPILE_OPTIONS_C_RELEASE}>")
set(libx265_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${libx265_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${libx265_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${libx265_EXE_LINK_FLAGS_RELEASE}>")


set(libx265_COMPONENTS_RELEASE )