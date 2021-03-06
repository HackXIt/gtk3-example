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
$ sudo apt install build-essential make cmake libpthread-stubs0-dev gcovr libgtk-3-dev libgtest-dev
```

**NOTE:** ___The provided links might not be applicable to your distribution or version. They are my personal reference from when I created this repository.___

| Package               | Why?                                            | Reference                                                  |
|-----------------------|-------------------------------------------------|------------------------------------------------------------|
| build-essential       | Necessary build-tools for C/C++, including make | https://packages.debian.org/bullseye/build-essential       |
| cmake                 | For using the provided CMakeLists               | https://packages.debian.org/bullseye/cmake                 |
| libpthread-stubs0-dev | Library for PThread (required for GTK/GTest)    | https://packages.debian.org/bullseye/libpthread-stubs0-dev |
| gcovr                 | Library for Google Test Coverage                | https://packages.debian.org/bullseye/gcovr                 |
| libgtk-3-dev          | Library for GTK3                                | https://packages.debian.org/bullseye/libgtk-3-dev          |
| libgtest-dev          | Gooogle's framework for writing C tests         | https://packages.debian.org/bullseye/libgtest-dev          |

Additionally, you will need to create the following build directories:

```sh
$ mkdir build cmake-build
```

After creating those directories, you need to copy the directory `modules` into `cmake-build`:

```sh
$ cp modules cmake-build
```

Here's a full example for copy-paste:

```
sudo apt install build-essential make cmake libpthread-stubs0-dev gcovr libgtk-3-dev libgtest-dev
mkdir build cmake-build
cp modules cmake-build
```

# Building the project

The project contains two seperate build-systems, which is why we also create two different build directories.
The purpose of this is solely to demonstrate differences in the two build systems and also to seperate them without conflict.
It might also be wrong to call them build-systems, but for simplicity-sake I'll do so.

`make` and `cmake` are Tools, which keep track of changes in source-files and will rebuild only necessary parts of our program, without having to compile the whole project again.
**CMake** is actually a tool, which generates a Makefile for us. The tool itself is just another abstraction, attempting to make things easier for the programmer.

In order for the build-system to work, your project structure needs to look like so:

 - `./src/` => contains all translation-units, meaning source-files. That's the *code*.(*.c)
 - `./inc/` => contains all header-files, which are preprocessor files. Look it up. (*.h)
 - `./tests/` => contains all unit-testfiles, which basically is source-code for testing other code. (*.cxx)
 - `./build/` => is the output-folder for the `make` build-system (without CMAKE)
 - `./cmake-build/` => is the output-folder for the `cmake` build-system

To build the project with the given build-systems, there exist the following targets to execute in terminal: *(All targets are executed via the given Makefile)*

| Target           | Purpose                                                                                           |
|------------------|---------------------------------------------------------------------------------------------------|
| make build       | Configures and builds the Cmake-Project                                                           |
| make cmake-clean | Executes the 'clean' target in the underlying CMake-Project                                       |
| make test        | Builds the CMake-Project and runs the test-target                                                 |
| make coverage    | Builds the CMake-Project and runs the coverage report target                                      |
| make testrun     | Runs the unit tests executable directly                                                           |
| make current     | Builds current version of project, using the given objects                                        |
| make clean       | Cleans the build directory of the Make-Project, basically deleting all object-files & executables |
| make doc         | Generate the doxygen-documentation, if an appropriate Doxyfile exists                             |

## Information about the Makefile

- [ ] Write short make guide, specific to this repository

Our first b

### References for Makefile

- https://makefiletutorial.com/
- https://www.gnu.org/software/make/manual/html_node/index.html

## Information about the CMakeLists

- [ ] Write short cmake guide, specific to this repository

### References for CMakeLists

- https://cmake.org/cmake/help/latest/guide/tutorial/index.html
- http://derekmolloy.ie/hello-world-introductions-to-cmake/
- https://cmake.org/cmake/help/latest/manual/cmake.1.html

# Information about the modules (GTest & CodeCoverage)

- [ ] Add references for GTest & CodeCoverage 

# Information about VS-Code specific configurations

- [ ] Add information about the VS code configuration, specific to this project
- [ ] Add reference-links for vs-code configuration

## Recommended Extensions for development

- [x] Add list of recommended extension for C/C++ development

- [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)
- [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)
- [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
- [Clang-Format](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format)
- [Makefile Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.makefile-tools)
- [Local History](https://marketplace.visualstudio.com/items?itemName=xyz.local-history)

## Workspace file

- [ ] Add information about the provided workspace-file

## C/C++ Properties

- [ ] Add information about the provided C/C++ properties file

# Troubleshooting

If you get the following error:

```bash
> ~/gtk3-example/build/
Program was started as ./current with 1 arguments.
Using Glade for the GUI...

(current:15402): Gtk-ERROR **: 11:21:23.889: failed to add UI: Failed to open file ???glade-example.glade???: No such file or directory
Trace/breakpoint trap
```

or alternatively when built with cmake:

```bash
> ~/gtk3-example/cmake-build/bin
Program was started as ./gtk3-example with 1 arguments.
Using Glade for the GUI...

(gtk3-example:16174): Gtk-ERROR **: 11:30:50.253: failed to add UI: Failed to open file ???glade-example.glade???: No such file or directory
Trace/breakpoint trap
```

It means, that the program can't find the resource file to parse. There is no path given in the source file, so it searches for that in your current working directory.
If that file isn't in your current working directory, because you maybe changed directories to the build folder, then it won't find it.

There's a Makefile target to copy the glade file into the build-folder:

`make resource`

You can avoid the error, by calling the program from the root directory, where the glade-file resides.

`./build/current`
or
`./cmake-build/bin/gtk3-example`
