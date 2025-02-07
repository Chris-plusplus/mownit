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
set(armadillo_PACKAGE_FOLDER_RELEASE "C:/Users/Chris/.conan2/p/armad7dab5bafc28b6/p")
set(armadillo_BUILD_MODULES_PATHS_RELEASE "${armadillo_PACKAGE_FOLDER_RELEASE}/lib/cmake/conan-official-armadillo-variables.cmake")


set(armadillo_INCLUDE_DIRS_RELEASE "${armadillo_PACKAGE_FOLDER_RELEASE}/include")
set(armadillo_RES_DIRS_RELEASE )
set(armadillo_DEFINITIONS_RELEASE "-DARMA_NO_DEBUG"
			"-DARMA_DONT_USE_WRAPPER"
			"-DARMA_USE_HDF5"
			"-DARMA_USE_BLAS"
			"-DARMA_USE_LAPACK"
			"-DARMA_DONT_USE_ARPACK"
			"-DARMA_DONT_USE_SUPERLU"
			"-DARMA_DONT_USE_ATLAS")
set(armadillo_SHARED_LINK_FLAGS_RELEASE )
set(armadillo_EXE_LINK_FLAGS_RELEASE )
set(armadillo_OBJECTS_RELEASE )
set(armadillo_COMPILE_DEFINITIONS_RELEASE "ARMA_NO_DEBUG"
			"ARMA_DONT_USE_WRAPPER"
			"ARMA_USE_HDF5"
			"ARMA_USE_BLAS"
			"ARMA_USE_LAPACK"
			"ARMA_DONT_USE_ARPACK"
			"ARMA_DONT_USE_SUPERLU"
			"ARMA_DONT_USE_ATLAS")
set(armadillo_COMPILE_OPTIONS_C_RELEASE )
set(armadillo_COMPILE_OPTIONS_CXX_RELEASE )
set(armadillo_LIB_DIRS_RELEASE "${armadillo_PACKAGE_FOLDER_RELEASE}/lib")
set(armadillo_BIN_DIRS_RELEASE )
set(armadillo_LIBRARY_TYPE_RELEASE STATIC)
set(armadillo_IS_HOST_WINDOWS_RELEASE 1)
set(armadillo_LIBS_RELEASE armadillo)
set(armadillo_SYSTEM_LIBS_RELEASE )
set(armadillo_FRAMEWORK_DIRS_RELEASE )
set(armadillo_FRAMEWORKS_RELEASE )
set(armadillo_BUILD_DIRS_RELEASE )
set(armadillo_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(armadillo_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${armadillo_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${armadillo_COMPILE_OPTIONS_C_RELEASE}>")
set(armadillo_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${armadillo_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${armadillo_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${armadillo_EXE_LINK_FLAGS_RELEASE}>")


set(armadillo_COMPONENTS_RELEASE )