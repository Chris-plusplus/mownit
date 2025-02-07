# Load the debug and release variables
file(GLOB DATA_FILES "${CMAKE_CURRENT_LIST_DIR}/module-Armadillo-*-data.cmake")

foreach(f ${DATA_FILES})
    include(${f})
endforeach()

# Create the targets for all the components
foreach(_COMPONENT ${armadillo_COMPONENT_NAMES} )
    if(NOT TARGET ${_COMPONENT})
        add_library(${_COMPONENT} INTERFACE IMPORTED)
        message(${Armadillo_MESSAGE_MODE} "Conan: Component target declared '${_COMPONENT}'")
    endif()
endforeach()

if(NOT TARGET Armadillo::Armadillo)
    add_library(Armadillo::Armadillo INTERFACE IMPORTED)
    message(${Armadillo_MESSAGE_MODE} "Conan: Target declared 'Armadillo::Armadillo'")
endif()
if(NOT TARGET armadillo)
    add_library(armadillo INTERFACE IMPORTED)
    set_property(TARGET armadillo PROPERTY INTERFACE_LINK_LIBRARIES Armadillo::Armadillo)
endif()
if(NOT TARGET armadillo::armadillo)
    add_library(armadillo::armadillo INTERFACE IMPORTED)
    set_property(TARGET armadillo::armadillo PROPERTY INTERFACE_LINK_LIBRARIES Armadillo::Armadillo)
endif()
# Load the debug and release library finders
file(GLOB CONFIG_FILES "${CMAKE_CURRENT_LIST_DIR}/module-Armadillo-Target-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()