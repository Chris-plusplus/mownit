from conan import ConanFile
from conan.tools.cmake import CMakeToolchain

class Mownit(ConanFile):
    name = "Mownit"
    settings = "build_type"
    
    def requirements(self):
        self.requires("jasper/4.2.0", override=True)
        self.requires("cvplot/1.2.2")
        self.requires("opencv/4.8.1", override=True)
        self.requires("symengine/0.11.2")
        
    generators = "CMakeDeps", "CMakeToolchain"