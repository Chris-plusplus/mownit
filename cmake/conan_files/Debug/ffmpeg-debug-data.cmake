########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

list(APPEND ffmpeg_COMPONENT_NAMES ffmpeg::avutil ffmpeg::swscale ffmpeg::swresample ffmpeg::postproc ffmpeg::avcodec ffmpeg::avformat ffmpeg::avfilter ffmpeg::avdevice)
list(REMOVE_DUPLICATES ffmpeg_COMPONENT_NAMES)
if(DEFINED ffmpeg_FIND_DEPENDENCY_NAMES)
  list(APPEND ffmpeg_FIND_DEPENDENCY_NAMES LibLZMA Iconv freetype BZip2 OpenJPEG openh264 Vorbis Opus libx264 libx265 libvpx libmp3lame fdk-aac WebP OpenSSL ZLIB libaom-av1 dav1d)
  list(REMOVE_DUPLICATES ffmpeg_FIND_DEPENDENCY_NAMES)
else()
  set(ffmpeg_FIND_DEPENDENCY_NAMES LibLZMA Iconv freetype BZip2 OpenJPEG openh264 Vorbis Opus libx264 libx265 libvpx libmp3lame fdk-aac WebP OpenSSL ZLIB libaom-av1 dav1d)
endif()
set(LibLZMA_FIND_MODE "NO_MODULE")
set(Iconv_FIND_MODE "NO_MODULE")
set(freetype_FIND_MODE "NO_MODULE")
set(BZip2_FIND_MODE "NO_MODULE")
set(OpenJPEG_FIND_MODE "NO_MODULE")
set(openh264_FIND_MODE "NO_MODULE")
set(Vorbis_FIND_MODE "NO_MODULE")
set(Opus_FIND_MODE "NO_MODULE")
set(libx264_FIND_MODE "NO_MODULE")
set(libx265_FIND_MODE "NO_MODULE")
set(libvpx_FIND_MODE "NO_MODULE")
set(libmp3lame_FIND_MODE "NO_MODULE")
set(fdk-aac_FIND_MODE "NO_MODULE")
set(WebP_FIND_MODE "NO_MODULE")
set(OpenSSL_FIND_MODE "NO_MODULE")
set(ZLIB_FIND_MODE "NO_MODULE")
set(libaom-av1_FIND_MODE "NO_MODULE")
set(dav1d_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(ffmpeg_PACKAGE_FOLDER_DEBUG "C:/Users/Chris/.conan2/p/b/ffmpec23b4f5a10e85/p")
set(ffmpeg_BUILD_MODULES_PATHS_DEBUG )


set(ffmpeg_INCLUDE_DIRS_DEBUG )
set(ffmpeg_RES_DIRS_DEBUG )
set(ffmpeg_DEFINITIONS_DEBUG )
set(ffmpeg_SHARED_LINK_FLAGS_DEBUG )
set(ffmpeg_EXE_LINK_FLAGS_DEBUG )
set(ffmpeg_OBJECTS_DEBUG )
set(ffmpeg_COMPILE_DEFINITIONS_DEBUG )
set(ffmpeg_COMPILE_OPTIONS_C_DEBUG )
set(ffmpeg_COMPILE_OPTIONS_CXX_DEBUG )
set(ffmpeg_LIB_DIRS_DEBUG "${ffmpeg_PACKAGE_FOLDER_DEBUG}/lib")
set(ffmpeg_BIN_DIRS_DEBUG )
set(ffmpeg_LIBRARY_TYPE_DEBUG STATIC)
set(ffmpeg_IS_HOST_WINDOWS_DEBUG 1)
set(ffmpeg_LIBS_DEBUG avdevice avfilter avformat avcodec postproc swresample swscale avutil)
set(ffmpeg_SYSTEM_LIBS_DEBUG ole32 psapi strmiids uuid oleaut32 shlwapi gdi32 vfw32 secur32 mfplat mfuuid user32 bcrypt)
set(ffmpeg_FRAMEWORK_DIRS_DEBUG )
set(ffmpeg_FRAMEWORKS_DEBUG )
set(ffmpeg_BUILD_DIRS_DEBUG )
set(ffmpeg_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(ffmpeg_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${ffmpeg_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${ffmpeg_COMPILE_OPTIONS_C_DEBUG}>")
set(ffmpeg_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${ffmpeg_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${ffmpeg_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${ffmpeg_EXE_LINK_FLAGS_DEBUG}>")


set(ffmpeg_COMPONENTS_DEBUG ffmpeg::avutil ffmpeg::swscale ffmpeg::swresample ffmpeg::postproc ffmpeg::avcodec ffmpeg::avformat ffmpeg::avfilter ffmpeg::avdevice)
########### COMPONENT ffmpeg::avdevice VARIABLES ############################################

set(ffmpeg_ffmpeg_avdevice_INCLUDE_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avdevice_LIB_DIRS_DEBUG "${ffmpeg_PACKAGE_FOLDER_DEBUG}/lib")
set(ffmpeg_ffmpeg_avdevice_BIN_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avdevice_LIBRARY_TYPE_DEBUG STATIC)
set(ffmpeg_ffmpeg_avdevice_IS_HOST_WINDOWS_DEBUG 1)
set(ffmpeg_ffmpeg_avdevice_RES_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avdevice_DEFINITIONS_DEBUG )
set(ffmpeg_ffmpeg_avdevice_OBJECTS_DEBUG )
set(ffmpeg_ffmpeg_avdevice_COMPILE_DEFINITIONS_DEBUG )
set(ffmpeg_ffmpeg_avdevice_COMPILE_OPTIONS_C_DEBUG "")
set(ffmpeg_ffmpeg_avdevice_COMPILE_OPTIONS_CXX_DEBUG "")
set(ffmpeg_ffmpeg_avdevice_LIBS_DEBUG avdevice)
set(ffmpeg_ffmpeg_avdevice_SYSTEM_LIBS_DEBUG ole32 psapi strmiids uuid oleaut32 shlwapi gdi32 vfw32)
set(ffmpeg_ffmpeg_avdevice_FRAMEWORK_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avdevice_FRAMEWORKS_DEBUG )
set(ffmpeg_ffmpeg_avdevice_DEPENDENCIES_DEBUG ffmpeg::avutil ffmpeg::avfilter ffmpeg::swscale ffmpeg::avformat ffmpeg::avcodec ffmpeg::swresample ffmpeg::postproc)
set(ffmpeg_ffmpeg_avdevice_SHARED_LINK_FLAGS_DEBUG )
set(ffmpeg_ffmpeg_avdevice_EXE_LINK_FLAGS_DEBUG )
set(ffmpeg_ffmpeg_avdevice_NO_SONAME_MODE_DEBUG FALSE)

# COMPOUND VARIABLES
set(ffmpeg_ffmpeg_avdevice_LINKER_FLAGS_DEBUG
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${ffmpeg_ffmpeg_avdevice_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${ffmpeg_ffmpeg_avdevice_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${ffmpeg_ffmpeg_avdevice_EXE_LINK_FLAGS_DEBUG}>
)
set(ffmpeg_ffmpeg_avdevice_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${ffmpeg_ffmpeg_avdevice_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${ffmpeg_ffmpeg_avdevice_COMPILE_OPTIONS_C_DEBUG}>")
########### COMPONENT ffmpeg::avfilter VARIABLES ############################################

set(ffmpeg_ffmpeg_avfilter_INCLUDE_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avfilter_LIB_DIRS_DEBUG "${ffmpeg_PACKAGE_FOLDER_DEBUG}/lib")
set(ffmpeg_ffmpeg_avfilter_BIN_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avfilter_LIBRARY_TYPE_DEBUG STATIC)
set(ffmpeg_ffmpeg_avfilter_IS_HOST_WINDOWS_DEBUG 1)
set(ffmpeg_ffmpeg_avfilter_RES_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avfilter_DEFINITIONS_DEBUG )
set(ffmpeg_ffmpeg_avfilter_OBJECTS_DEBUG )
set(ffmpeg_ffmpeg_avfilter_COMPILE_DEFINITIONS_DEBUG )
set(ffmpeg_ffmpeg_avfilter_COMPILE_OPTIONS_C_DEBUG "")
set(ffmpeg_ffmpeg_avfilter_COMPILE_OPTIONS_CXX_DEBUG "")
set(ffmpeg_ffmpeg_avfilter_LIBS_DEBUG avfilter)
set(ffmpeg_ffmpeg_avfilter_SYSTEM_LIBS_DEBUG )
set(ffmpeg_ffmpeg_avfilter_FRAMEWORK_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avfilter_FRAMEWORKS_DEBUG )
set(ffmpeg_ffmpeg_avfilter_DEPENDENCIES_DEBUG ffmpeg::avutil ffmpeg::swscale ffmpeg::avformat ffmpeg::avcodec ffmpeg::swresample ffmpeg::postproc Freetype::Freetype)
set(ffmpeg_ffmpeg_avfilter_SHARED_LINK_FLAGS_DEBUG )
set(ffmpeg_ffmpeg_avfilter_EXE_LINK_FLAGS_DEBUG )
set(ffmpeg_ffmpeg_avfilter_NO_SONAME_MODE_DEBUG FALSE)

# COMPOUND VARIABLES
set(ffmpeg_ffmpeg_avfilter_LINKER_FLAGS_DEBUG
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${ffmpeg_ffmpeg_avfilter_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${ffmpeg_ffmpeg_avfilter_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${ffmpeg_ffmpeg_avfilter_EXE_LINK_FLAGS_DEBUG}>
)
set(ffmpeg_ffmpeg_avfilter_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${ffmpeg_ffmpeg_avfilter_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${ffmpeg_ffmpeg_avfilter_COMPILE_OPTIONS_C_DEBUG}>")
########### COMPONENT ffmpeg::avformat VARIABLES ############################################

set(ffmpeg_ffmpeg_avformat_INCLUDE_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avformat_LIB_DIRS_DEBUG "${ffmpeg_PACKAGE_FOLDER_DEBUG}/lib")
set(ffmpeg_ffmpeg_avformat_BIN_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avformat_LIBRARY_TYPE_DEBUG STATIC)
set(ffmpeg_ffmpeg_avformat_IS_HOST_WINDOWS_DEBUG 1)
set(ffmpeg_ffmpeg_avformat_RES_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avformat_DEFINITIONS_DEBUG )
set(ffmpeg_ffmpeg_avformat_OBJECTS_DEBUG )
set(ffmpeg_ffmpeg_avformat_COMPILE_DEFINITIONS_DEBUG )
set(ffmpeg_ffmpeg_avformat_COMPILE_OPTIONS_C_DEBUG "")
set(ffmpeg_ffmpeg_avformat_COMPILE_OPTIONS_CXX_DEBUG "")
set(ffmpeg_ffmpeg_avformat_LIBS_DEBUG avformat)
set(ffmpeg_ffmpeg_avformat_SYSTEM_LIBS_DEBUG secur32)
set(ffmpeg_ffmpeg_avformat_FRAMEWORK_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avformat_FRAMEWORKS_DEBUG )
set(ffmpeg_ffmpeg_avformat_DEPENDENCIES_DEBUG ffmpeg::avutil ffmpeg::avcodec ffmpeg::swresample BZip2::BZip2 OpenSSL::SSL)
set(ffmpeg_ffmpeg_avformat_SHARED_LINK_FLAGS_DEBUG )
set(ffmpeg_ffmpeg_avformat_EXE_LINK_FLAGS_DEBUG )
set(ffmpeg_ffmpeg_avformat_NO_SONAME_MODE_DEBUG FALSE)

# COMPOUND VARIABLES
set(ffmpeg_ffmpeg_avformat_LINKER_FLAGS_DEBUG
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${ffmpeg_ffmpeg_avformat_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${ffmpeg_ffmpeg_avformat_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${ffmpeg_ffmpeg_avformat_EXE_LINK_FLAGS_DEBUG}>
)
set(ffmpeg_ffmpeg_avformat_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${ffmpeg_ffmpeg_avformat_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${ffmpeg_ffmpeg_avformat_COMPILE_OPTIONS_C_DEBUG}>")
########### COMPONENT ffmpeg::avcodec VARIABLES ############################################

set(ffmpeg_ffmpeg_avcodec_INCLUDE_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avcodec_LIB_DIRS_DEBUG "${ffmpeg_PACKAGE_FOLDER_DEBUG}/lib")
set(ffmpeg_ffmpeg_avcodec_BIN_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avcodec_LIBRARY_TYPE_DEBUG STATIC)
set(ffmpeg_ffmpeg_avcodec_IS_HOST_WINDOWS_DEBUG 1)
set(ffmpeg_ffmpeg_avcodec_RES_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avcodec_DEFINITIONS_DEBUG )
set(ffmpeg_ffmpeg_avcodec_OBJECTS_DEBUG )
set(ffmpeg_ffmpeg_avcodec_COMPILE_DEFINITIONS_DEBUG )
set(ffmpeg_ffmpeg_avcodec_COMPILE_OPTIONS_C_DEBUG "")
set(ffmpeg_ffmpeg_avcodec_COMPILE_OPTIONS_CXX_DEBUG "")
set(ffmpeg_ffmpeg_avcodec_LIBS_DEBUG avcodec)
set(ffmpeg_ffmpeg_avcodec_SYSTEM_LIBS_DEBUG mfplat mfuuid strmiids)
set(ffmpeg_ffmpeg_avcodec_FRAMEWORK_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avcodec_FRAMEWORKS_DEBUG )
set(ffmpeg_ffmpeg_avcodec_DEPENDENCIES_DEBUG ffmpeg::avutil ffmpeg::swresample ZLIB::ZLIB LibLZMA::LibLZMA Iconv::Iconv openjp2 openh264::openh264 vorbis::vorbis Opus::opus libx264::libx264 libx265::libx265 libvpx::libvpx libmp3lame::libmp3lame FDK-AAC::fdk-aac libwebp::libwebp libaom-av1::libaom-av1 dav1d::dav1d)
set(ffmpeg_ffmpeg_avcodec_SHARED_LINK_FLAGS_DEBUG )
set(ffmpeg_ffmpeg_avcodec_EXE_LINK_FLAGS_DEBUG )
set(ffmpeg_ffmpeg_avcodec_NO_SONAME_MODE_DEBUG FALSE)

# COMPOUND VARIABLES
set(ffmpeg_ffmpeg_avcodec_LINKER_FLAGS_DEBUG
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${ffmpeg_ffmpeg_avcodec_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${ffmpeg_ffmpeg_avcodec_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${ffmpeg_ffmpeg_avcodec_EXE_LINK_FLAGS_DEBUG}>
)
set(ffmpeg_ffmpeg_avcodec_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${ffmpeg_ffmpeg_avcodec_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${ffmpeg_ffmpeg_avcodec_COMPILE_OPTIONS_C_DEBUG}>")
########### COMPONENT ffmpeg::postproc VARIABLES ############################################

set(ffmpeg_ffmpeg_postproc_INCLUDE_DIRS_DEBUG )
set(ffmpeg_ffmpeg_postproc_LIB_DIRS_DEBUG "${ffmpeg_PACKAGE_FOLDER_DEBUG}/lib")
set(ffmpeg_ffmpeg_postproc_BIN_DIRS_DEBUG )
set(ffmpeg_ffmpeg_postproc_LIBRARY_TYPE_DEBUG STATIC)
set(ffmpeg_ffmpeg_postproc_IS_HOST_WINDOWS_DEBUG 1)
set(ffmpeg_ffmpeg_postproc_RES_DIRS_DEBUG )
set(ffmpeg_ffmpeg_postproc_DEFINITIONS_DEBUG )
set(ffmpeg_ffmpeg_postproc_OBJECTS_DEBUG )
set(ffmpeg_ffmpeg_postproc_COMPILE_DEFINITIONS_DEBUG )
set(ffmpeg_ffmpeg_postproc_COMPILE_OPTIONS_C_DEBUG "")
set(ffmpeg_ffmpeg_postproc_COMPILE_OPTIONS_CXX_DEBUG "")
set(ffmpeg_ffmpeg_postproc_LIBS_DEBUG postproc)
set(ffmpeg_ffmpeg_postproc_SYSTEM_LIBS_DEBUG )
set(ffmpeg_ffmpeg_postproc_FRAMEWORK_DIRS_DEBUG )
set(ffmpeg_ffmpeg_postproc_FRAMEWORKS_DEBUG )
set(ffmpeg_ffmpeg_postproc_DEPENDENCIES_DEBUG ffmpeg::avutil)
set(ffmpeg_ffmpeg_postproc_SHARED_LINK_FLAGS_DEBUG )
set(ffmpeg_ffmpeg_postproc_EXE_LINK_FLAGS_DEBUG )
set(ffmpeg_ffmpeg_postproc_NO_SONAME_MODE_DEBUG FALSE)

# COMPOUND VARIABLES
set(ffmpeg_ffmpeg_postproc_LINKER_FLAGS_DEBUG
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${ffmpeg_ffmpeg_postproc_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${ffmpeg_ffmpeg_postproc_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${ffmpeg_ffmpeg_postproc_EXE_LINK_FLAGS_DEBUG}>
)
set(ffmpeg_ffmpeg_postproc_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${ffmpeg_ffmpeg_postproc_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${ffmpeg_ffmpeg_postproc_COMPILE_OPTIONS_C_DEBUG}>")
########### COMPONENT ffmpeg::swresample VARIABLES ############################################

set(ffmpeg_ffmpeg_swresample_INCLUDE_DIRS_DEBUG )
set(ffmpeg_ffmpeg_swresample_LIB_DIRS_DEBUG "${ffmpeg_PACKAGE_FOLDER_DEBUG}/lib")
set(ffmpeg_ffmpeg_swresample_BIN_DIRS_DEBUG )
set(ffmpeg_ffmpeg_swresample_LIBRARY_TYPE_DEBUG STATIC)
set(ffmpeg_ffmpeg_swresample_IS_HOST_WINDOWS_DEBUG 1)
set(ffmpeg_ffmpeg_swresample_RES_DIRS_DEBUG )
set(ffmpeg_ffmpeg_swresample_DEFINITIONS_DEBUG )
set(ffmpeg_ffmpeg_swresample_OBJECTS_DEBUG )
set(ffmpeg_ffmpeg_swresample_COMPILE_DEFINITIONS_DEBUG )
set(ffmpeg_ffmpeg_swresample_COMPILE_OPTIONS_C_DEBUG "")
set(ffmpeg_ffmpeg_swresample_COMPILE_OPTIONS_CXX_DEBUG "")
set(ffmpeg_ffmpeg_swresample_LIBS_DEBUG swresample)
set(ffmpeg_ffmpeg_swresample_SYSTEM_LIBS_DEBUG )
set(ffmpeg_ffmpeg_swresample_FRAMEWORK_DIRS_DEBUG )
set(ffmpeg_ffmpeg_swresample_FRAMEWORKS_DEBUG )
set(ffmpeg_ffmpeg_swresample_DEPENDENCIES_DEBUG ffmpeg::avutil)
set(ffmpeg_ffmpeg_swresample_SHARED_LINK_FLAGS_DEBUG )
set(ffmpeg_ffmpeg_swresample_EXE_LINK_FLAGS_DEBUG )
set(ffmpeg_ffmpeg_swresample_NO_SONAME_MODE_DEBUG FALSE)

# COMPOUND VARIABLES
set(ffmpeg_ffmpeg_swresample_LINKER_FLAGS_DEBUG
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${ffmpeg_ffmpeg_swresample_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${ffmpeg_ffmpeg_swresample_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${ffmpeg_ffmpeg_swresample_EXE_LINK_FLAGS_DEBUG}>
)
set(ffmpeg_ffmpeg_swresample_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${ffmpeg_ffmpeg_swresample_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${ffmpeg_ffmpeg_swresample_COMPILE_OPTIONS_C_DEBUG}>")
########### COMPONENT ffmpeg::swscale VARIABLES ############################################

set(ffmpeg_ffmpeg_swscale_INCLUDE_DIRS_DEBUG )
set(ffmpeg_ffmpeg_swscale_LIB_DIRS_DEBUG "${ffmpeg_PACKAGE_FOLDER_DEBUG}/lib")
set(ffmpeg_ffmpeg_swscale_BIN_DIRS_DEBUG )
set(ffmpeg_ffmpeg_swscale_LIBRARY_TYPE_DEBUG STATIC)
set(ffmpeg_ffmpeg_swscale_IS_HOST_WINDOWS_DEBUG 1)
set(ffmpeg_ffmpeg_swscale_RES_DIRS_DEBUG )
set(ffmpeg_ffmpeg_swscale_DEFINITIONS_DEBUG )
set(ffmpeg_ffmpeg_swscale_OBJECTS_DEBUG )
set(ffmpeg_ffmpeg_swscale_COMPILE_DEFINITIONS_DEBUG )
set(ffmpeg_ffmpeg_swscale_COMPILE_OPTIONS_C_DEBUG "")
set(ffmpeg_ffmpeg_swscale_COMPILE_OPTIONS_CXX_DEBUG "")
set(ffmpeg_ffmpeg_swscale_LIBS_DEBUG swscale)
set(ffmpeg_ffmpeg_swscale_SYSTEM_LIBS_DEBUG )
set(ffmpeg_ffmpeg_swscale_FRAMEWORK_DIRS_DEBUG )
set(ffmpeg_ffmpeg_swscale_FRAMEWORKS_DEBUG )
set(ffmpeg_ffmpeg_swscale_DEPENDENCIES_DEBUG ffmpeg::avutil)
set(ffmpeg_ffmpeg_swscale_SHARED_LINK_FLAGS_DEBUG )
set(ffmpeg_ffmpeg_swscale_EXE_LINK_FLAGS_DEBUG )
set(ffmpeg_ffmpeg_swscale_NO_SONAME_MODE_DEBUG FALSE)

# COMPOUND VARIABLES
set(ffmpeg_ffmpeg_swscale_LINKER_FLAGS_DEBUG
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${ffmpeg_ffmpeg_swscale_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${ffmpeg_ffmpeg_swscale_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${ffmpeg_ffmpeg_swscale_EXE_LINK_FLAGS_DEBUG}>
)
set(ffmpeg_ffmpeg_swscale_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${ffmpeg_ffmpeg_swscale_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${ffmpeg_ffmpeg_swscale_COMPILE_OPTIONS_C_DEBUG}>")
########### COMPONENT ffmpeg::avutil VARIABLES ############################################

set(ffmpeg_ffmpeg_avutil_INCLUDE_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avutil_LIB_DIRS_DEBUG "${ffmpeg_PACKAGE_FOLDER_DEBUG}/lib")
set(ffmpeg_ffmpeg_avutil_BIN_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avutil_LIBRARY_TYPE_DEBUG STATIC)
set(ffmpeg_ffmpeg_avutil_IS_HOST_WINDOWS_DEBUG 1)
set(ffmpeg_ffmpeg_avutil_RES_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avutil_DEFINITIONS_DEBUG )
set(ffmpeg_ffmpeg_avutil_OBJECTS_DEBUG )
set(ffmpeg_ffmpeg_avutil_COMPILE_DEFINITIONS_DEBUG )
set(ffmpeg_ffmpeg_avutil_COMPILE_OPTIONS_C_DEBUG "")
set(ffmpeg_ffmpeg_avutil_COMPILE_OPTIONS_CXX_DEBUG "")
set(ffmpeg_ffmpeg_avutil_LIBS_DEBUG avutil)
set(ffmpeg_ffmpeg_avutil_SYSTEM_LIBS_DEBUG user32 bcrypt)
set(ffmpeg_ffmpeg_avutil_FRAMEWORK_DIRS_DEBUG )
set(ffmpeg_ffmpeg_avutil_FRAMEWORKS_DEBUG )
set(ffmpeg_ffmpeg_avutil_DEPENDENCIES_DEBUG )
set(ffmpeg_ffmpeg_avutil_SHARED_LINK_FLAGS_DEBUG )
set(ffmpeg_ffmpeg_avutil_EXE_LINK_FLAGS_DEBUG )
set(ffmpeg_ffmpeg_avutil_NO_SONAME_MODE_DEBUG FALSE)

# COMPOUND VARIABLES
set(ffmpeg_ffmpeg_avutil_LINKER_FLAGS_DEBUG
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${ffmpeg_ffmpeg_avutil_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${ffmpeg_ffmpeg_avutil_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${ffmpeg_ffmpeg_avutil_EXE_LINK_FLAGS_DEBUG}>
)
set(ffmpeg_ffmpeg_avutil_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${ffmpeg_ffmpeg_avutil_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${ffmpeg_ffmpeg_avutil_COMPILE_OPTIONS_C_DEBUG}>")