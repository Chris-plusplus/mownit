########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(cvplot_COMPONENT_NAMES "")
if(DEFINED cvplot_FIND_DEPENDENCY_NAMES)
  list(APPEND cvplot_FIND_DEPENDENCY_NAMES OpenCV)
  list(REMOVE_DUPLICATES cvplot_FIND_DEPENDENCY_NAMES)
else()
  set(cvplot_FIND_DEPENDENCY_NAMES OpenCV)
endif()
set(OpenCV_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(cvplot_PACKAGE_FOLDER_RELEASE "C:/Users/Chris/.conan2/p/cvplo24a0153c45901/p")
set(cvplot_BUILD_MODULES_PATHS_RELEASE )


set(cvplot_INCLUDE_DIRS_RELEASE "${cvplot_PACKAGE_FOLDER_RELEASE}/include")
set(cvplot_RES_DIRS_RELEASE )
set(cvplot_DEFINITIONS_RELEASE "-DCVPLOT_HEADER_ONLY")
set(cvplot_SHARED_LINK_FLAGS_RELEASE )
set(cvplot_EXE_LINK_FLAGS_RELEASE )
set(cvplot_OBJECTS_RELEASE )
set(cvplot_COMPILE_DEFINITIONS_RELEASE "CVPLOT_HEADER_ONLY")
set(cvplot_COMPILE_OPTIONS_C_RELEASE )
set(cvplot_COMPILE_OPTIONS_CXX_RELEASE )
set(cvplot_LIB_DIRS_RELEASE )
set(cvplot_BIN_DIRS_RELEASE )
set(cvplot_LIBRARY_TYPE_RELEASE UNKNOWN)
set(cvplot_IS_HOST_WINDOWS_RELEASE 1)
set(cvplot_LIBS_RELEASE )
set(cvplot_SYSTEM_LIBS_RELEASE )
set(cvplot_FRAMEWORK_DIRS_RELEASE )
set(cvplot_FRAMEWORKS_RELEASE )
set(cvplot_BUILD_DIRS_RELEASE )
set(cvplot_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(cvplot_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${cvplot_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${cvplot_COMPILE_OPTIONS_C_RELEASE}>")
set(cvplot_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${cvplot_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${cvplot_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${cvplot_EXE_LINK_FLAGS_RELEASE}>")


set(cvplot_COMPONENTS_RELEASE )