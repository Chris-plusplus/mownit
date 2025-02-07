message(STATUS "Conan: Using CMakeDeps conandeps_legacy.cmake aggregator via include()")
message(STATUS "Conan: It is recommended to use explicit find_package() per dependency instead")

find_package(CvPlot)
find_package(symengine)
find_package(Armadillo)

set(CONANDEPS_LEGACY  CvPlot::CvPlot  symengine::symengine  Armadillo::Armadillo )