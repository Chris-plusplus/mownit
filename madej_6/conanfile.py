from conan import ConanFile
from conan.tools.cmake import CMakeToolchain

class Mownit(ConanFile):
    name = "Mownit"
    settings = "build_type"
    
    def requirements(self):
        pass
        
    generators = "CMakeDeps", "CMakeToolchain"