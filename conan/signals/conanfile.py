from conans import ConanFile, CMake, tools


class SignalsConan(ConanFile):
    name = "signals"
    version = "1.0"
    license = "MIT"
    author = "TheWisp"
    url = "https://github.com/TheWisp/signals"
    description = "The low-latency signal-slot library for C++"
    topics = ("low-latency", "slots", "signals")
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"

    def source(self):
        self.run("git clone https://github.com/TheWisp/signals.git")

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="signals")

    def package(self):
        self.copy("signals.hpp", dst="include", src="signals")

    def package_info(self):
        self.cpp_info.libs = ["signals"]

