########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(armadillo_COMPONENT_NAMES "")
if(DEFINED armadillo_FIND_DEPENDENCY_NAMES)
  list(APPEND armadillo_FIND_DEPENDENCY_NAMES OpenBLAS)
  list(REMOVE_DUPLICATES armadillo_FIND_DEPENDENCY_NAMES)
else()
  set(armadillo_FIND_DEPENDENCY_NAMES OpenBLAS)
endif()
set(OpenBLAS_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(armadillo_PACKAGE_FOLDER_DEBUG "C:/Users/Chris/.conan2/p/b/armadb1fc857107eac/p")
set(armadillo_BUILD_MODULES_PATHS_DEBUG "${armadillo_PACKAGE_FOLDER_DEBUG}/lib/cmake/conan-official-armadillo-variables.cmake")


set(armadillo_INCLUDE_DIRS_DEBUG "${armadillo_PACKAGE_FOLDER_DEBUG}/include")
set(armadillo_RES_DIRS_DEBUG )
set(armadillo_DEFINITIONS_DEBUG "-DARMA_DONT_USE_WRAPPER"
			"-DARMA_USE_HDF5"
			"-DARMA_USE_BLAS"
			"-DARMA_USE_LAPACK"
			"-DARMA_DONT_USE_ARPACK"
			"-DARMA_DONT_USE_SUPERLU"
			"-DARMA_DONT_USE_ATLAS")
set(armadillo_SHARED_LINK_FLAGS_DEBUG )
set(armadillo_EXE_LINK_FLAGS_DEBUG )
set(armadillo_OBJECTS_DEBUG )
set(armadillo_COMPILE_DEFINITIONS_DEBUG "ARMA_DONT_USE_WRAPPER"
			"ARMA_USE_HDF5"
			"ARMA_USE_BLAS"
			"ARMA_USE_LAPACK"
			"ARMA_DONT_USE_ARPACK"
			"ARMA_DONT_USE_SUPERLU"
			"ARMA_DONT_USE_ATLAS")
set(armadillo_COMPILE_OPTIONS_C_DEBUG )
set(armadillo_COMPILE_OPTIONS_CXX_DEBUG )
set(armadillo_LIB_DIRS_DEBUG "${armadillo_PACKAGE_FOLDER_DEBUG}/lib")
set(armadillo_BIN_DIRS_DEBUG )
set(armadillo_LIBRARY_TYPE_DEBUG STATIC)
set(armadillo_IS_HOST_WINDOWS_DEBUG 1)
set(armadillo_LIBS_DEBUG armadillo)
set(armadillo_SYSTEM_LIBS_DEBUG )
set(armadillo_FRAMEWORK_DIRS_DEBUG )
set(armadillo_FRAMEWORKS_DEBUG )
set(armadillo_BUILD_DIRS_DEBUG )
set(armadillo_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(armadillo_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${armadillo_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${armadillo_COMPILE_OPTIONS_C_DEBUG}>")
set(armadillo_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${armadillo_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${armadillo_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${armadillo_EXE_LINK_FLAGS_DEBUG}>")


set(armadillo_COMPONENTS_DEBUG )