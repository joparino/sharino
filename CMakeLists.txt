cmake_minimum_required (VERSION 3.8)

project ("sharino")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable (sharino "main.cpp" "fft.h" "fft.cpp" "wav.h" "wav.cpp" "sharino.h" "sharino.cpp")
