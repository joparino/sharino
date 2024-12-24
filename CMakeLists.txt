cmake_minimum_required (VERSION 3.8)

project ("sharino")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable (sharino "main.cpp" "src/fft.h" "src/fft.cpp" "src/wav.h" "src/wav.cpp" "src/sharino.h" "src/sharino.cpp")
