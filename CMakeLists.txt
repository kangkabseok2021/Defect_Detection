cmake_minimum_required(VERSION 3.10)
project(QualityInspection)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include directories
include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Source files
set(SOURCES
    src/ImageProcessor.cpp
    src/BlobDetector.cpp
    src/EdgeDefectDetector.cpp
    src/Inspector.cpp
    src/DetectionStrategy.cpp
    main.cpp
)

# Create executable
add_executable(QualityInspection ${SOURCES})

# Link libraries
target_link_libraries(QualityInspection ${OpenCV_LIBS})

# Set output directory
set_target_properties(QualityInspection PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)