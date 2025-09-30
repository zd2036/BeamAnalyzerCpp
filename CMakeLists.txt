cmake_minimum_required(VERSION 3.16)
project(BeamAnalyzerCpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_CINOGY "Enable Cinogy SDK support" OFF)
option(USE_FUYU "Enable Fuyu motion stage support" OFF)

if(USE_CINOGY)
    add_definitions(-DUSE_CINOGY)
    include_directories("C:/Cinogy/SDK/include")
    link_directories("C:/Cinogy/SDK/lib")
    set(EXTRA_LIBS ${EXTRA_LIBS} CinogySDK.lib)
endif()

if(USE_FUYU)
    add_definitions(-DUSE_FUYU)
endif()

add_executable(zscan_demo
    src/zscan_demo.cpp
    src/BeamAnalyzer.cpp
    src/HardwareAbstraction.cpp
)

target_include_directories(zscan_demo PRIVATE include)
target_link_libraries(zscan_demo ${EXTRA_LIBS})
