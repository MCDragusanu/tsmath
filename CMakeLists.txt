cmake_minimum_required(VERSION 3.0)
project(lin_alg)

# Specify the build folder (modify "build" to your desired name)
set(CMAKE_BUILD_TYPE DEBUG)  # Optional: Set build type (e.g., DEBUG, RELEASE)
set(BUILD_FOLDER "build")     # Change "build" to your preferred name

# Find all source files
file(GLOB source_files "*.cpp")

# Create the build folder if it doesn't exist
make_directory(${BUILD_FOLDER})

# Add an executable target that links all source files
add_executable(lin_alg_exe ${source_files})

# Set the build directory. This ensures the build results go to the specified folder.
set_target_properties(lin_alg_exe PROPERTIES OUTPUT_DIRECTORY ${BUILD_FOLDER})
