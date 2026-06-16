cmake_minimum_required(VERSION 3.20)
project(AeroPort LANGUAGES CXX)

if(MSVC)
    add_compile_options(/std:c++latest /permissive- /Zc:__cplusplus)
endif()

file(GLOB ROOT_SOURCES CONFIGURE_DEPENDS "*.cpp" "*.h")
file(GLOB AIRPLANE_SOURCES CONFIGURE_DEPENDS "airplanes/*.cpp" "airplanes/*.h")
file(GLOB TICKET_SOURCES CONFIGURE_DEPENDS "tickets/*.cpp" "tickets/*.h")
file(GLOB USER_SOURCES CONFIGURE_DEPENDS "users/*.cpp" "users/*.h")
file(GLOB CORE_SOURCES CONFIGURE_DEPENDS "core/*.cpp" "core/*.h")
file(GLOB INFRASTRUCTURE_SOURCES CONFIGURE_DEPENDS "infrastructure/*.cpp" "infrastructure/*.h")
file(GLOB VISITOR_SOURCES CONFIGURE_DEPENDS "visitor/*.cpp" "visitor/*.h")
file(GLOB OPERATIONS_SOURCES CONFIGURE_DEPENDS "operations/*.cpp" "operations/*.h")
file(GLOB AIRLINE_SOURCES CONFIGURE_DEPENDS "airline/*.cpp" "airline/*.h")

add_executable(${PROJECT_NAME} 
${SOURCES} 
${ROOT_SOURCES} 
${AIRPLANE_SOURCES} 
${TICKET_SOURCES}
${USER_SOURCES}
${CORE_SOURCES}
${INFRASTRUCTURE_SOURCES}
${VISITOR_SOURCES}
${OPERATIONS_SOURCES}
${AIRLINE_SOURCES}
)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include")
    target_include_directories(${PROJECT_NAME} PRIVATE include)
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/airplanes")
    target_include_directories(${PROJECT_NAME} PRIVATE airline operations airplanes tickets users core infrastructure visitor)
endif()