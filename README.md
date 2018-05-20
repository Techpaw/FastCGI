[ ![Download](https://api.bintray.com/packages/techpaw/SolutionsForWeb/FastCgi%3Apandomic/images/download.svg) ](https://bintray.com/techpaw/SolutionsForWeb/FastCgi%3Apandomic/_latestVersion)

** NOTE that this lib is still under development**

## About
Yet another FastCgi protocol implementation.

## Installation
* Install [conan](https://docs.conan.io/en/latest/installation.html)
* Clone the repo
* Add `https://api.bintray.com/conan/bincrafters/public-conan`
to the repos list (`conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan`
* Add `https://api.bintray.com/conan/techpaw/SolutionsForWeb`
to the repos list (`conan remote add techpaw/SolutionsForWeb https://api.bintray.com/conan/techpaw/SolutionsForWeb`)
* Add `FastCgi/0.1@pandomic/experimental` to your `conanfile.txt`
* Run `conan install . --build=missing`
* Include necessary headers `#include <fastcgi/server.hpp>`
* That's it (ideally)