cmake_minimum_required(VERSION 3.10)
project(BridgeRepair)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/Main.cpp
    src/ArgumentParser.cpp
    src/FileReader.cpp
)

set(HEADERS
    src/ArgumentParser.hpp
    src/CalibrationCalculator.hpp
    src/FileReader.hpp
)

add_executable(BridgeRepair ${SOURCES} ${HEADERS})
