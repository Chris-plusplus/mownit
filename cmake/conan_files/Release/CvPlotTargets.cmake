# Load the debug and release variables
file(GLOB DATA_FILES "${CMAKE_CURRENT_LIST_DIR}/CvPlot-*-data.cmake")

foreach(f ${DATA_FILES})
    include(${f})
endforeach()

# Create the targets for all the components
foreach(_COMPONENT ${cvplot_COMPONENT_NAMES} )
    if(NOT TARGET ${_COMPONENT})
        add_library(${_COMPONENT} INTERFACE IMPORTED)
        message(${CvPlot_MESSAGE_MODE} "Conan: Component target declared '${_COMPONENT}'")
    endif()
endforeach()

if(NOT TARGET CvPlot::CvPlot)
    add_library(CvPlot::CvPlot INTERFACE IMPORTED)
    message(${CvPlot_MESSAGE_MODE} "Conan: Target declared 'CvPlot::CvPlot'")
endif()
# Load the debug and release library finders
file(GLOB CONFIG_FILES "${CMAKE_CURRENT_LIST_DIR}/CvPlot-Target-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()