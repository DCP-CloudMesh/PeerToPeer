cmake_minimum_required(VERSION 3.12)

project(CloudMesh)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")

if(LOCAL)
    add_compile_definitions(LOCAL=1)
else()
    add_compile_definitions(NOLOCAL=1)
endif()

set(SRC_DIR src)

file(GLOB_RECURSE SRCS ${SRC_DIR}/*.cpp)

add_executable(bootstrap ${SRCS} main.cpp)
target_compile_definitions(bootstrap PRIVATE BOOTSTRAP=1)
target_link_libraries(bootstrap PRIVATE nlohmann_json::nlohmann_json)
set_target_properties(bootstrap PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)

add_executable(provider ${SRCS} main.cpp)
target_compile_definitions(provider PRIVATE PROVIDER=1)
target_link_libraries(provider PRIVATE nlohmann_json::nlohmann_json)
set_target_properties(provider PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)

add_executable(requester ${SRCS} main.cpp)
target_compile_definitions(requester PRIVATE REQUESTER=1)
target_link_libraries(requester PRIVATE nlohmann_json::nlohmann_json)
set_target_properties(requester PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)
