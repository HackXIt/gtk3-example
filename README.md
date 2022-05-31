# GTK3 Example project using VSCode

This project is a basis and example for a GUI application written in C, using the google gtest library for unit-tests.

It's made to help fellow students, struggling with getting a proper build-environment running themselves. 
They can compare with their own versions and learn a few tricks, which are used in this basis.

I'd like to mention, that I am by no means an expert but this is what I've made and it is working very well for me.
I've used this in the provided Ubuntu Virtual machine, as well as in my personal WSL2 Debian environment.
But results may vary, depending on the operating system or distribution.
(Most definitly it **will not work** on Windows!)

# Pre-requisites for this repository to work

In order to use this repository, you need to install some packages first.
These packages are REQUIRED for building the repository with the given build-environments.

```sh
$ sudo apt install build-essential make cmake libpthread-stubs0-dev gcovr libgtk-3-dev
```

**NOTE:** ___The provided links might not be applicable to your distribution or version. They are my personal reference from when I created this repository.___

| Package               | Why?                                            | Reference                                                  |
|-----------------------|-------------------------------------------------|------------------------------------------------------------|
| build-essential       | Necessary build-tools for C/C++, including make | https://packages.debian.org/bullseye/build-essential       |
| cmake                 | For using the provided CMakeLists               | https://packages.debian.org/bullseye/cmake                 |
| libpthread-stubs0-dev | Library for PThread (required for GTK)          | https://packages.debian.org/bullseye/libpthread-stubs0-dev |
| gcovr                 | Library for Google Test Coverage                | https://packages.debian.org/bullseye/gcovr                 |
| libgtk-3-dev          | Library for GTK3                                | https://packages.debian.org/bullseye/libgtk-3-dev          |

Additionally, you will need to create the following build directories:

```sh
$ mkdir build cmake-build
```

# Information about the Makefile

- [ ] Write short make guide, specific to this repository

## References for Makefile

- https://makefiletutorial.com/
- https://www.gnu.org/software/make/manual/html_node/index.html

# Information about the CMakeLists

- [ ] Write short cmake guide, specific to this repository

## References for CMakeLists

- https://cmake.org/cmake/help/latest/guide/tutorial/index.html
- http://derekmolloy.ie/hello-world-introductions-to-cmake/
- https://cmake.org/cmake/help/latest/manual/cmake.1.html

# Information about the modules (GTest & CodeCoverage)

- [ ] Add references for GTest & CodeCoverage 

# Information about VS-Code specific configurations

- [ ] Add information about the VS code configuration, specific to this project
- [ ] Add reference-links for vs-code configuration

## Recommended Extensions for development

- [ ] Add list of recommended extension for C/C++ development

## Workspace file

- [ ] Add information about the provided workspace-file

## C/C++ Properties

- [ ] Add information about the provided C/C++ properties file