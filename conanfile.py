from conans import ConanFile, CMake, tools


class FastCgiConan(ConanFile):
    name = "FastCgi"
    version = "0.1"
    license = "MIT"
    url = "https://github.com/Techpaw/FastCGI"
    description = "FastCgi implementation"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=True"
    generators = "cmake"
    exports_sources = "include/*"
    requires = "Boost.Asio/1.65.1@bincrafters/stable", \
               "Boost.Stacktrace/1.65.1@bincrafters/stable"

    def source(self):
        self.run("git clone https://github.com/Techpaw/FastCGI.git fastcgi")
        self.run("cd fastcgi && git checkout stable")

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="fastcgi")
        cmake.build()

    def package(self):
        self.copy("*.hpp", dst="include", src="fastcgi/include")
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["fastcgi"]
