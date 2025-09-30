cmake_minimum_required(VERSION 3.16)
project(BeamAnalyzerCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Qt and OpenCV configuration ===
set(Qt6_DIR "D:/Software/Qt/6.5.3/msvc2019_64/lib/cmake/Qt6")
set(OpenCV_DIR "D:/Software/include/opencv/build/x64/vc16/lib")

find_package(Qt6 COMPONENTS Quick Qml QuickControls2 REQUIRED)
find_package(OpenCV REQUIRED)

# === QML import path fix ===
set(QML_IMPORT_PATH "D:/Software/Qt/6.5.3/msvc2019_64/qml" CACHE STRING "QML import path")
set(QML2_IMPORT_PATH "D:/Software/Qt/6.5.3/msvc2019_64/qml" CACHE STRING "QML2 import path")

# === Include source files ===
add_executable(BeamAnalyzerCpp
    src/main.cpp
    src/qml_backend/CameraProvider.cpp
    src/qml_backend/AnalyzerBridge.cpp
    src/qml_backend/BeamData.cpp
    src/core/BeamAnalyzer.cpp
    src/core/M2Calculator.cpp
)

target_include_directories(BeamAnalyzerCpp PRIVATE src)

target_link_libraries(BeamAnalyzerCpp PRIVATE
    Qt6::Quick Qt6::Qml Qt6::QuickControls2
    ${OpenCV_LIBS}
)

# === Resource ===
qt_add_resources(BeamAnalyzerCpp "qml_resources"
    PREFIX "/gui"
    FILES
        src/gui/BeamAnalyzerApp.qml
)

# === Output directory ===
set_target_properties(BeamAnalyzerCpp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

message(STATUS "Qt6 path: ${Qt6_DIR}")
message(STATUS "OpenCV path: ${OpenCV_DIR}")
