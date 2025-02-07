from conan import ConanFile
from conan.tools.cmake import CMakeToolchain

class Mownit(ConanFile):
    name = "Mownit"
    settings = "build_type"
    
    def requirements(self):
        self.requires("armadillo/12.6.4")
        
    generators = "CMakeDeps", "CMakeToolchain"