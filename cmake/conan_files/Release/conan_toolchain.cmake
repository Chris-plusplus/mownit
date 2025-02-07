

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
list(PREPEND CMAKE_MODULE_PATH "C:/Users/Chris/.conan2/p/b/proto3e9aadca66364/p/lib/cmake/protobuf" "C:/Users/Chris/.conan2/p/openj58733c81470a1/p/lib/cmake" "C:/Users/Chris/.conan2/p/b/opensc09aa5a637f10/p/lib/cmake")
# the generators folder (where conan generates files, like this toolchain)
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Definition of CMAKE_PREFIX_PATH, CMAKE_XXXXX_PATH
# The explicitly defined "builddirs" of "host" context dependencies must be in PREFIX_PATH
list(PREPEND CMAKE_PREFIX_PATH "C:/Users/Chris/.conan2/p/b/proto3e9aadca66364/p/lib/cmake/protobuf" "C:/Users/Chris/.conan2/p/openj58733c81470a1/p/lib/cmake" "C:/Users/Chris/.conan2/p/b/opensc09aa5a637f10/p/lib/cmake")
# The Conan local "generators" folder, where this toolchain is saved.
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR} )
list(PREPEND CMAKE_LIBRARY_PATH "C:/Users/Chris/.conan2/p/b/opencf2601fda4e54d/p/lib" "lib" "C:/Users/Chris/.conan2/p/b/proto3e9aadca66364/p/lib" "C:/Users/Chris/.conan2/p/ade12af7d213dfb7/p/lib" "C:/Users/Chris/.conan2/p/jaspe6e278eb1cd1b7/p/lib" "C:/Users/Chris/.conan2/p/b/openee0c7adac37b92/p/lib" "C:/Users/Chris/.conan2/p/imath80c97b7d55ab8/p/lib" "C:/Users/Chris/.conan2/p/b/libticda5b3ec6448b/p/lib" "C:/Users/Chris/.conan2/p/libde712e34aa8080e/p/lib" "C:/Users/Chris/.conan2/p/libjp0a77fd78bf747/p/lib" "C:/Users/Chris/.conan2/p/jbigfe9119c355d4c/p/lib" "C:/Users/Chris/.conan2/p/zstdf1d2b6566f015/p/lib" "C:/Users/Chris/.conan2/p/quirc4a07504dcabda/p/lib" "C:/Users/Chris/.conan2/p/b/ffmpec1a16c03ef516/p/lib" "C:/Users/Chris/.conan2/p/xz_utc437dae9165b5/p/lib" "C:/Users/Chris/.conan2/p/libicb4e788959979c/p/lib" "C:/Users/Chris/.conan2/p/b/freet5780cbac4dc94/p/lib" "C:/Users/Chris/.conan2/p/b/libpn6757b9ecec583/p/lib" "C:/Users/Chris/.conan2/p/bzip2390e62dbed9cd/p/lib" "C:/Users/Chris/.conan2/p/brotl79757a5cae055/p/lib" "C:/Users/Chris/.conan2/p/openj58733c81470a1/p/lib" "C:/Users/Chris/.conan2/p/openhfd27db7edc5da/p/lib" "C:/Users/Chris/.conan2/p/vorbib3b87ba3196b8/p/lib" "C:/Users/Chris/.conan2/p/ogg0603e0d7ed2e4/p/lib" "C:/Users/Chris/.conan2/p/opus8462564dcd469/p/lib" "C:/Users/Chris/.conan2/p/libx2023aa9caac2a2/p/lib" "C:/Users/Chris/.conan2/p/libx2997b103fcf89a/p/lib" "C:/Users/Chris/.conan2/p/libvp2ea497d07acf7/p/lib" "C:/Users/Chris/.conan2/p/libmpb8490c605ee04/p/lib" "C:/Users/Chris/.conan2/p/libfda79a2c8bbcda3/p/lib" "C:/Users/Chris/.conan2/p/libweb2503c6aa238e/p/lib" "C:/Users/Chris/.conan2/p/b/opensc09aa5a637f10/p/lib" "C:/Users/Chris/.conan2/p/zlib4a799e276690b/p/lib" "C:/Users/Chris/.conan2/p/libao1ef0c9c4f4b07/p/lib" "C:/Users/Chris/.conan2/p/dav1d9fbc52b90fc14/p/lib" "C:/Users/Chris/.conan2/p/symen0456211a49424/p/lib" "C:/Users/Chris/.conan2/p/gmp0780613777525/p/lib" "C:/Users/Chris/.conan2/p/armad7dab5bafc28b6/p/lib" "C:/Users/Chris/.conan2/p/openb191c4c53bb898/p/lib")
list(PREPEND CMAKE_INCLUDE_PATH "C:/Users/Chris/.conan2/p/cvplo24a0153c45901/p/include" "C:/Users/Chris/.conan2/p/b/opencf2601fda4e54d/p/include" "include" "C:/Users/Chris/.conan2/p/b/proto3e9aadca66364/p/include" "C:/Users/Chris/.conan2/p/ade12af7d213dfb7/p/include" "C:/Users/Chris/.conan2/p/jaspe6e278eb1cd1b7/p/include" "C:/Users/Chris/.conan2/p/b/openee0c7adac37b92/p/include" "C:/Users/Chris/.conan2/p/b/openee0c7adac37b92/p/include/OpenEXR" "C:/Users/Chris/.conan2/p/imath80c97b7d55ab8/p/include" "C:/Users/Chris/.conan2/p/imath80c97b7d55ab8/p/include/Imath" "C:/Users/Chris/.conan2/p/b/libticda5b3ec6448b/p/include" "C:/Users/Chris/.conan2/p/libde712e34aa8080e/p/include" "C:/Users/Chris/.conan2/p/libjp0a77fd78bf747/p/include" "C:/Users/Chris/.conan2/p/jbigfe9119c355d4c/p/include" "C:/Users/Chris/.conan2/p/zstdf1d2b6566f015/p/include" "C:/Users/Chris/.conan2/p/quirc4a07504dcabda/p/include" "C:/Users/Chris/.conan2/p/b/ffmpec1a16c03ef516/p/include" "C:/Users/Chris/.conan2/p/xz_utc437dae9165b5/p/include" "C:/Users/Chris/.conan2/p/libicb4e788959979c/p/include" "C:/Users/Chris/.conan2/p/b/freet5780cbac4dc94/p/include" "C:/Users/Chris/.conan2/p/b/freet5780cbac4dc94/p/include/freetype2" "C:/Users/Chris/.conan2/p/b/libpn6757b9ecec583/p/include" "C:/Users/Chris/.conan2/p/bzip2390e62dbed9cd/p/include" "C:/Users/Chris/.conan2/p/brotl79757a5cae055/p/include" "C:/Users/Chris/.conan2/p/brotl79757a5cae055/p/include/brotli" "C:/Users/Chris/.conan2/p/openj58733c81470a1/p/include" "C:/Users/Chris/.conan2/p/openj58733c81470a1/p/include/openjpeg-2.5" "C:/Users/Chris/.conan2/p/openhfd27db7edc5da/p/include" "C:/Users/Chris/.conan2/p/vorbib3b87ba3196b8/p/include" "C:/Users/Chris/.conan2/p/ogg0603e0d7ed2e4/p/include" "C:/Users/Chris/.conan2/p/opus8462564dcd469/p/include" "C:/Users/Chris/.conan2/p/opus8462564dcd469/p/include/opus" "C:/Users/Chris/.conan2/p/libx2023aa9caac2a2/p/include" "C:/Users/Chris/.conan2/p/libx2997b103fcf89a/p/include" "C:/Users/Chris/.conan2/p/libvp2ea497d07acf7/p/include" "C:/Users/Chris/.conan2/p/libmpb8490c605ee04/p/include" "C:/Users/Chris/.conan2/p/libfda79a2c8bbcda3/p/include" "C:/Users/Chris/.conan2/p/libweb2503c6aa238e/p/include" "C:/Users/Chris/.conan2/p/b/opensc09aa5a637f10/p/include" "C:/Users/Chris/.conan2/p/zlib4a799e276690b/p/include" "C:/Users/Chris/.conan2/p/libao1ef0c9c4f4b07/p/include" "C:/Users/Chris/.conan2/p/dav1d9fbc52b90fc14/p/include" "C:/Users/Chris/.conan2/p/symen0456211a49424/p/include" "C:/Users/Chris/.conan2/p/gmp0780613777525/p/include" "C:/Users/Chris/.conan2/p/armad7dab5bafc28b6/p/include" "C:/Users/Chris/.conan2/p/openb191c4c53bb898/p/include" "C:/Users/Chris/.conan2/p/openb191c4c53bb898/p/include/openblas")



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
