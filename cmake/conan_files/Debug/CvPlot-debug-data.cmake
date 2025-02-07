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
set(cvplot_PACKAGE_FOLDER_DEBUG "C:/Users/Chris/.conan2/p/cvplo24a0153c45901/p")
set(cvplot_BUILD_MODULES_PATHS_DEBUG )


set(cvplot_INCLUDE_DIRS_DEBUG "${cvplot_PACKAGE_FOLDER_DEBUG}/include")
set(cvplot_RES_DIRS_DEBUG )
set(cvplot_DEFINITIONS_DEBUG "-DCVPLOT_HEADER_ONLY")
set(cvplot_SHARED_LINK_FLAGS_DEBUG )
set(cvplot_EXE_LINK_FLAGS_DEBUG )
set(cvplot_OBJECTS_DEBUG )
set(cvplot_COMPILE_DEFINITIONS_DEBUG "CVPLOT_HEADER_ONLY")
set(cvplot_COMPILE_OPTIONS_C_DEBUG )
set(cvplot_COMPILE_OPTIONS_CXX_DEBUG )
set(cvplot_LIB_DIRS_DEBUG )
set(cvplot_BIN_DIRS_DEBUG )
set(cvplot_LIBRARY_TYPE_DEBUG UNKNOWN)
set(cvplot_IS_HOST_WINDOWS_DEBUG 1)
set(cvplot_LIBS_DEBUG )
set(cvplot_SYSTEM_LIBS_DEBUG )
set(cvplot_FRAMEWORK_DIRS_DEBUG )
set(cvplot_FRAMEWORKS_DEBUG )
set(cvplot_BUILD_DIRS_DEBUG )
set(cvplot_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(cvplot_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${cvplot_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${cvplot_COMPILE_OPTIONS_C_DEBUG}>")
set(cvplot_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${cvplot_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${cvplot_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${cvplot_EXE_LINK_FLAGS_DEBUG}>")


set(cvplot_COMPONENTS_DEBUG )