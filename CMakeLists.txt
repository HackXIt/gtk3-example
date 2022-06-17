# Damit diese CMake-Datei funktioniert, muss die Projekt-Ordnerstruktur wie folgt sein:
# ./src/ => enthält ALLE Translations- bzw. Source-Dateien (*.c)
# ./inc/ => enthält ALLE Header-Dateien (*.h)
# ./tests/ => enthält ALLE Unit-Tests bzw. deren Source-Dateien (*.cxx)
# ./build/ => wird als Ausgabe-Ordner für MAKE-Builds verwendet (ohne CMAKE)
# ./cmake-build/ => wird als Ausgabe-Ordner für CMAKE-Builds verwendet 

# To build the project and NOT ruin the root-directory with build-files, please use the following:
# cd cmake-build && cmake .. && make

# The included 'Makefile' in the root-directory can be used instead to make this process easier
# make build -> for creating a build
# make test -> for creating a build and running `make test` in the build directory
# make coverage -> for creating a build and creating a coverage report from the unit_tests
# make testrun -> for creating a build and running the unit_tests executable
# make cmake-clean -> for cleaning the build directory `cmake-build`

cmake_minimum_required(VERSION 3.10.0)
# Hier den Projektnamen ändern bzw. angeben
project(gtk3-example C CXX)
set(CMAKE_BUILD_TYPE "Debug")
# To change the output folder of CMAKE itself, you need to change the settings of the extension
# Either that, or in command line you use the option -B to set the output folder of the build.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Testing-Funktionalität aktivieren (essenziell für gtest)
enable_testing()
find_package(PkgConfig REQUIRED) # To check for the GTK Module
# Anforderungen von GTK abfragen (installiert ?)
pkg_check_modules(GTK REQUIRED "gtk+-3.0")
# Threads ist ein weiteres Paket welches von GTK vorausgesetzt wird
find_package(Threads REQUIRED)

# Dieser Abschnitt ist notwendig für gtest & CodeCoverage
include(${CMAKE_CURRENT_SOURCE_DIR}/modules/GTest_ExternalProject.cmake)
include(GoogleTest)
include(${CMAKE_CURRENT_SOURCE_DIR}/modules/CodeCoverage.cmake)
append_coverage_compiler_flags()

# Hier wird der Pfad der Header-Dateien inkludiert, als auch die Header-Dateien von GTK
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc ${GTK_INCLUDE_DIRS})
# Verlinkung mit dem Pfad der GTK-Bibliothek
link_directories(${GTK_LIBRARY_DIRS})

# Das ist eine KURZFORM um alle *.c-Dateien in die Variable SRC_FILES zu speichern (als dependency)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
# Hier wird die letztlich ausführbare Datei angegeben, inklusive ihrer Abhängigkeiten (SRC_FILES)
add_executable(${PROJECT_NAME} ${SRC_FILES})
# Hier wird eine Bibliothek aus den vorhandenen SRC_FILES erstellt, diese wird nur für die Unit-Tests benötigt
add_library(${PROJECT_NAME}_library SHARED ${SRC_FILES})

# Hier werden die Abhängigkeiten für die EXECUTABLE festgelegt, da wir auch Unit-Tests haben
add_dependencies(${PROJECT_NAME}
    ${PROJECT_NAME}
    libgtest
    libgtest_main
)

# Erneut eine KURZFORM um alle *.cxx-Dateien in die Variable TEST_FILES zu speichern (als dependency)
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cxx)
# Hier wird die letztlich ausführbare Test-Datei angegeben, inklusive ihrer Abhängigkeiten (TEST_FILES)
add_executable(${PROJECT_NAME}_unit_tests ${TEST_FILES})
# Hier wird die Abhängigkeit dieser EXECUTABLE festgelegt, nämlich unser zuvor erstellte Bibliothek
add_dependencies(${PROJECT_NAME}_unit_tests
    ${PROJECT_NAME}_library
    libgtest
    libgtest_main
)

# Setzt die Variable WARNING_LEVELS_GCC (kurzform für Build-Flags des Release)
# Dies bitte nicht verwenden - es ist nur üblich für sogenannte "Releases" andere Build-Flags zu verwenden
set(WARNING_LEVELS_GCC
    -Werror
)
# Setzt die Variable WARNING_LEVELS_GCC_DEBUG (kurzform für Build-Flags des Entwicklers)
set(WARNING_LEVELS_GCC_DEBUG
	-Wall
	-Wextra
	-Wno-unused-parameter
	# -pedantic
	-Wno-write-strings
	-Wno-missing-field-initializers
	-g
)

# Verlinkt die Bibliotheken von GTK mit der zuvor festgelegten EXECUTABLE
target_link_libraries(${PROJECT_NAME} ${GTK_LDFLAGS})
# Setzt die Compiler-Optionen für die zuvor festgelegte EXECUTABLE
target_compile_options(${PROJECT_NAME} PRIVATE ${GTK_CFLAGS} ${WARNING_LEVELS_GCC_DEBUG})

# Verlinkt die Bibliotheken von GTK mit der zuvor festgelegten Test-EXECUTABLE
target_link_libraries(${PROJECT_NAME}_unit_tests libgtest libgtest_main ${GTK_LDFLAGS} ${PROJECT_NAME}_library)
# Setzt die Compiler-Optionen für die zuvor festgelegte Test-EXECUTABLE
target_compile_options(${PROJECT_NAME}_unit_tests PRIVATE ${GTEST_CFLAGS} ${WARNING_LEVELS_GCC_DEBUG} ${GTK_CFLAGS})

# Hier wird speziell festgelegt, dass es Unit-Tests gibt für den Coverage-Report und von was dieser abhängt
gtest_discover_tests(${PROJECT_NAME}_unit_tests)
setup_target_for_coverage_gcovr_html(
    NAME ${PROJECT_NAME}_coverage
    EXECUTABLE ctest -j ${PROCESSOR_COUNT}
    DEPENDENCIES ${PROJECT_NAME}_unit_tests
    EXCLUDE "${CMAKE_CURRENT_BINARY_DIR}/gtest/*")