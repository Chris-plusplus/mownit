

# Conan automatically generated toolchain file
# DO NOT EDIT MANUALLY, it will be overwritten

# Avoid including toolchain file several times (bad if appending to variables like
#   CMAKE_CXX_FLAGS. See https://github.com/android/ndk/issues/323
include_guard()

message(STATUS "Using Conan toolchain: ${CMAKE_CURRENT_LIST_FILE}")

if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeToolchain' generator only works with CMake >= 3.15")
endif()




########## generic_system block #############
# Definition of system, platform and toolset
#############################################

# Cross building
set(CMAKE_SYSTEM_NAME Generic)








# Conan conf flags start: 
# Conan conf flags end

foreach(config IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER ${config} config)
    if(DEFINED CONAN_CXX_FLAGS_${config})
      string(APPEND CMAKE_CXX_FLAGS_${config}_INIT " ${CONAN_CXX_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_C_FLAGS_${config})
      string(APPEND CMAKE_C_FLAGS_${config}_INIT " ${CONAN_C_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_SHARED_LINKER_FLAGS_${config})
      string(APPEND CMAKE_SHARED_LINKER_FLAGS_${config}_INIT " ${CONAN_SHARED_LINKER_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_EXE_LINKER_FLAGS_${config})
      string(APPEND CMAKE_EXE_LINKER_FLAGS_${config}_INIT " ${CONAN_EXE_LINKER_FLAGS_${config}}")
    endif()
endforeach()

if(DEFINED CONAN_CXX_FLAGS)
  string(APPEND CMAKE_CXX_FLAGS_INIT " ${CONAN_CXX_FLAGS}")
endif()
if(DEFINED CONAN_C_FLAGS)
  string(APPEND CMAKE_C_FLAGS_INIT " ${CONAN_C_FLAGS}")
endif()
if(DEFINED CONAN_SHARED_LINKER_FLAGS)
  string(APPEND CMAKE_SHARED_LINKER_FLAGS_INIT " ${CONAN_SHARED_LINKER_FLAGS}")
endif()
if(DEFINED CONAN_EXE_LINKER_FLAGS)
  string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " ${CONAN_EXE_LINKER_FLAGS}")
endif()


get_property( _CMAKE_IN_TRY_COMPILE GLOBAL PROPERTY IN_TRY_COMPILE )
if(_CMAKE_IN_TRY_COMPILE)
    message(STATUS "Running toolchain IN_TRY_COMPILE")
    return()
endif()

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

# Definition of CMAKE_MODULE_PATH
list(PREPEND CMAKE_MODULE_PATH "C:/Users/Chris/.conan2/p/b/proto1602c692a015b/p/lib/cmake/protobuf" "C:/Users/Chris/.conan2/p/b/openj9fa6d0e5937d0/p/lib/cmake" "C:/Users/Chris/.conan2/p/b/opens8f174bc010936/p/lib/cmake")
# the generators folder (where conan generates files, like this toolchain)
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Definition of CMAKE_PREFIX_PATH, CMAKE_XXXXX_PATH
# The explicitly defined "builddirs" of "host" context dependencies must be in PREFIX_PATH
list(PREPEND CMAKE_PREFIX_PATH "C:/Users/Chris/.conan2/p/b/proto1602c692a015b/p/lib/cmake/protobuf" "C:/Users/Chris/.conan2/p/b/openj9fa6d0e5937d0/p/lib/cmake" "C:/Users/Chris/.conan2/p/b/opens8f174bc010936/p/lib/cmake")
# The Conan local "generators" folder, where this toolchain is saved.
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR} )
list(PREPEND CMAKE_LIBRARY_PATH "C:/Users/Chris/.conan2/p/b/openc625f8064062d9/p/lib" "lib" "C:/Users/Chris/.conan2/p/b/proto1602c692a015b/p/lib" "C:/Users/Chris/.conan2/p/b/ade839ce616f1538/p/lib" "C:/Users/Chris/.conan2/p/b/jaspe2fa9bbaf8377a/p/lib" "C:/Users/Chris/.conan2/p/b/opene7f1c5b5da3533/p/lib" "C:/Users/Chris/.conan2/p/b/imathc0681f690f4c5/p/lib" "C:/Users/Chris/.conan2/p/b/libticd4fc84e367d7/p/lib" "C:/Users/Chris/.conan2/p/b/libde03730e27e2ac4/p/lib" "C:/Users/Chris/.conan2/p/b/libjpdcc42ac8648f1/p/lib" "C:/Users/Chris/.conan2/p/b/jbig0c3dea9c346e1/p/lib" "C:/Users/Chris/.conan2/p/b/zstd477ab0c959896/p/lib" "C:/Users/Chris/.conan2/p/b/quirc3fc8d1d64acdc/p/lib" "C:/Users/Chris/.conan2/p/b/ffmpec23b4f5a10e85/p/lib" "C:/Users/Chris/.conan2/p/b/xz_uta4868f8343837/p/lib" "C:/Users/Chris/.conan2/p/b/libic8ca1546690866/p/lib" "C:/Users/Chris/.conan2/p/b/freet356301e7153ca/p/lib" "C:/Users/Chris/.conan2/p/b/libpnf6b7809731076/p/lib" "C:/Users/Chris/.conan2/p/b/bzip22b40d177acea0/p/lib" "C:/Users/Chris/.conan2/p/b/brotl87236fa0af6e8/p/lib" "C:/Users/Chris/.conan2/p/b/openj9fa6d0e5937d0/p/lib" "C:/Users/Chris/.conan2/p/b/openh25d1bf072613f/p/lib" "C:/Users/Chris/.conan2/p/b/vorbi6ad6fce05d627/p/lib" "C:/Users/Chris/.conan2/p/b/ogg984a3e5f465f7/p/lib" "C:/Users/Chris/.conan2/p/b/opuseb24b88460a88/p/lib" "C:/Users/Chris/.conan2/p/b/libx2fd715e59a16bb/p/lib" "C:/Users/Chris/.conan2/p/b/libx2a8f8540de5c15/p/lib" "C:/Users/Chris/.conan2/p/b/libvp5348b49f667aa/p/lib" "C:/Users/Chris/.conan2/p/b/libmp04af3e397f337/p/lib" "C:/Users/Chris/.conan2/p/b/libfdae611e03e040f/p/lib" "C:/Users/Chris/.conan2/p/b/libwe7f6f52dc4d42c/p/lib" "C:/Users/Chris/.conan2/p/b/opens8f174bc010936/p/lib" "C:/Users/Chris/.conan2/p/zlibf5315b13b8944/p/lib" "C:/Users/Chris/.conan2/p/b/libaoff41de25d3851/p/lib" "C:/Users/Chris/.conan2/p/b/dav1d63184adb22252/p/lib" "C:/Users/Chris/.conan2/p/b/symen0f1ce1cda3022/p/lib" "C:/Users/Chris/.conan2/p/b/gmp17d62ddb462a6/p/lib" "C:/Users/Chris/.conan2/p/b/armadb1fc857107eac/p/lib" "C:/Users/Chris/.conan2/p/b/openbec6c90876f147/p/lib")
list(PREPEND CMAKE_INCLUDE_PATH "C:/Users/Chris/.conan2/p/cvplo24a0153c45901/p/include" "C:/Users/Chris/.conan2/p/b/openc625f8064062d9/p/include" "include" "C:/Users/Chris/.conan2/p/b/proto1602c692a015b/p/include" "C:/Users/Chris/.conan2/p/b/ade839ce616f1538/p/include" "C:/Users/Chris/.conan2/p/b/jaspe2fa9bbaf8377a/p/include" "C:/Users/Chris/.conan2/p/b/opene7f1c5b5da3533/p/include" "C:/Users/Chris/.conan2/p/b/opene7f1c5b5da3533/p/include/OpenEXR" "C:/Users/Chris/.conan2/p/b/imathc0681f690f4c5/p/include" "C:/Users/Chris/.conan2/p/b/imathc0681f690f4c5/p/include/Imath" "C:/Users/Chris/.conan2/p/b/libticd4fc84e367d7/p/include" "C:/Users/Chris/.conan2/p/b/libde03730e27e2ac4/p/include" "C:/Users/Chris/.conan2/p/b/libjpdcc42ac8648f1/p/include" "C:/Users/Chris/.conan2/p/b/jbig0c3dea9c346e1/p/include" "C:/Users/Chris/.conan2/p/b/zstd477ab0c959896/p/include" "C:/Users/Chris/.conan2/p/b/quirc3fc8d1d64acdc/p/include" "C:/Users/Chris/.conan2/p/b/ffmpec23b4f5a10e85/p/include" "C:/Users/Chris/.conan2/p/b/xz_uta4868f8343837/p/include" "C:/Users/Chris/.conan2/p/b/libic8ca1546690866/p/include" "C:/Users/Chris/.conan2/p/b/freet356301e7153ca/p/include" "C:/Users/Chris/.conan2/p/b/freet356301e7153ca/p/include/freetype2" "C:/Users/Chris/.conan2/p/b/libpnf6b7809731076/p/include" "C:/Users/Chris/.conan2/p/b/bzip22b40d177acea0/p/include" "C:/Users/Chris/.conan2/p/b/brotl87236fa0af6e8/p/include" "C:/Users/Chris/.conan2/p/b/brotl87236fa0af6e8/p/include/brotli" "C:/Users/Chris/.conan2/p/b/openj9fa6d0e5937d0/p/include" "C:/Users/Chris/.conan2/p/b/openj9fa6d0e5937d0/p/include/openjpeg-2.5" "C:/Users/Chris/.conan2/p/b/openh25d1bf072613f/p/include" "C:/Users/Chris/.conan2/p/b/vorbi6ad6fce05d627/p/include" "C:/Users/Chris/.conan2/p/b/ogg984a3e5f465f7/p/include" "C:/Users/Chris/.conan2/p/b/opuseb24b88460a88/p/include" "C:/Users/Chris/.conan2/p/b/opuseb24b88460a88/p/include/opus" "C:/Users/Chris/.conan2/p/b/libx2fd715e59a16bb/p/include" "C:/Users/Chris/.conan2/p/b/libx2a8f8540de5c15/p/include" "C:/Users/Chris/.conan2/p/b/libvp5348b49f667aa/p/include" "C:/Users/Chris/.conan2/p/b/libmp04af3e397f337/p/include" "C:/Users/Chris/.conan2/p/b/libfdae611e03e040f/p/include" "C:/Users/Chris/.conan2/p/b/libwe7f6f52dc4d42c/p/include" "C:/Users/Chris/.conan2/p/b/opens8f174bc010936/p/include" "C:/Users/Chris/.conan2/p/zlibf5315b13b8944/p/include" "C:/Users/Chris/.conan2/p/b/libaoff41de25d3851/p/include" "C:/Users/Chris/.conan2/p/b/dav1d63184adb22252/p/include" "C:/Users/Chris/.conan2/p/b/symen0f1ce1cda3022/p/include" "C:/Users/Chris/.conan2/p/b/gmp17d62ddb462a6/p/include" "C:/Users/Chris/.conan2/p/b/armadb1fc857107eac/p/include" "C:/Users/Chris/.conan2/p/b/openbec6c90876f147/p/include" "C:/Users/Chris/.conan2/p/b/openbec6c90876f147/p/include/openblas")



if (DEFINED ENV{PKG_CONFIG_PATH})
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};$ENV{PKG_CONFIG_PATH}")
else()
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};")
endif()




# Variables
# Variables  per configuration


# Preprocessor definitions
# Preprocessor definitions per configuration


if(CMAKE_POLICY_DEFAULT_CMP0091)  # Avoid unused and not-initialized warnings
endif()
