########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(libtiff_COMPONENT_NAMES "")
if(DEFINED libtiff_FIND_DEPENDENCY_NAMES)
  list(APPEND libtiff_FIND_DEPENDENCY_NAMES libdeflate JPEG jbig zstd LibLZMA WebP ZLIB)
  list(REMOVE_DUPLICATES libtiff_FIND_DEPENDENCY_NAMES)
else()
  set(libtiff_FIND_DEPENDENCY_NAMES libdeflate JPEG jbig zstd LibLZMA WebP ZLIB)
endif()
set(libdeflate_FIND_MODE "NO_MODULE")
set(JPEG_FIND_MODE "MODULE")
set(jbig_FIND_MODE "NO_MODULE")
set(zstd_FIND_MODE "NO_MODULE")
set(LibLZMA_FIND_MODE "MODULE")
set(WebP_FIND_MODE "NO_MODULE")
set(ZLIB_FIND_MODE "MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(libtiff_PACKAGE_FOLDER_DEBUG "C:/Users/Chris/.conan2/p/b/libticd4fc84e367d7/p")
set(libtiff_BUILD_MODULES_PATHS_DEBUG )


set(libtiff_INCLUDE_DIRS_DEBUG )
set(libtiff_RES_DIRS_DEBUG )
set(libtiff_DEFINITIONS_DEBUG )
set(libtiff_SHARED_LINK_FLAGS_DEBUG )
set(libtiff_EXE_LINK_FLAGS_DEBUG )
set(libtiff_OBJECTS_DEBUG )
set(libtiff_COMPILE_DEFINITIONS_DEBUG )
set(libtiff_COMPILE_OPTIONS_C_DEBUG )
set(libtiff_COMPILE_OPTIONS_CXX_DEBUG )
set(libtiff_LIB_DIRS_DEBUG "${libtiff_PACKAGE_FOLDER_DEBUG}/lib")
set(libtiff_BIN_DIRS_DEBUG )
set(libtiff_LIBRARY_TYPE_DEBUG STATIC)
set(libtiff_IS_HOST_WINDOWS_DEBUG 1)
set(libtiff_LIBS_DEBUG tiffxxd tiffd)
set(libtiff_SYSTEM_LIBS_DEBUG )
set(libtiff_FRAMEWORK_DIRS_DEBUG )
set(libtiff_FRAMEWORKS_DEBUG )
set(libtiff_BUILD_DIRS_DEBUG )
set(libtiff_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(libtiff_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${libtiff_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${libtiff_COMPILE_OPTIONS_C_DEBUG}>")
set(libtiff_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${libtiff_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${libtiff_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${libtiff_EXE_LINK_FLAGS_DEBUG}>")


set(libtiff_COMPONENTS_DEBUG )