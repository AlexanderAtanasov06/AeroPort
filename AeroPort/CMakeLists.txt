cmake_minimum_required(VERSION 3.20)
project(AeroPort LANGUAGES CXX)

if(MSVC)
    add_compile_options(/std:c++latest /permissive- /Zc:__cplusplus)
endif()

file(GLOB ROOT_SOURCES CONFIGURE_DEPENDS "*.cpp" "*.h")
file(GLOB AIRPLANE_SOURCES CONFIGURE_DEPENDS "airplanes/*.cpp" "airplanes/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${ROOT_SOURCES} ${AIRPLANE_SOURCES})

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include")
    target_include_directories(${PROJECT_NAME} PRIVATE include)
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/airplanes")
    target_include_directories(${PROJECT_NAME} PRIVATE airplanes)
endif()