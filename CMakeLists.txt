cmake_minimum_required(VERSION 3.10)
project(tsmathlib)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files for the library
file(GLOB LIB_SOURCES "src/*.cpp")

# Create the static library target
add_library(tsmath STATIC ${LIB_SOURCES})

# Add include directories for the library
target_include_directories(tsmath PUBLIC include)

# Optionally, add compile options or definitions
# target_compile_options(mylib PRIVATE -Wall)

# Install library and header files (optional)
install(TARGETS tsmath DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)