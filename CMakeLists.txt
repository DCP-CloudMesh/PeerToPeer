cmake_minimum_required(VERSION 3.12)

project(CloudMesh)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if(LOCAL)
    add_compile_definitions(LOCAL=1)
else()
    add_compile_definitions(NOLOCAL=1)
endif()

set(SRC_DIR src)

file(GLOB_RECURSE SRCS ${SRC_DIR}/*.cpp)

add_executable(provider ${SRCS} main.cpp)
target_compile_definitions(provider PRIVATE PROVIDER=1)
target_link_libraries(provider PRIVATE nlohmann_json::nlohmann_json)

add_executable(requester ${SRCS} main.cpp)
target_compile_definitions(requester PRIVATE REQUESTER=1)
target_link_libraries(requester PRIVATE nlohmann_json::nlohmann_json)

# Optionally, you can uncomment and use the following lines for individual compilation units:
# foreach(SRC ${SRCS})
#     get_filename_component(FILE_NAME ${SRC} NAME_WE)
#     add_executable(${FILE_NAME} ${SRC})
#     set_target_properties(${FILE_NAME} PROPERTIES
#         RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}
#     )
# endforeach()

# Optionally, you can uncomment the following lines if you want to create a library
# add_library(your_library_name ${SRCS})
# target_include_directories(your_library_name PUBLIC ${SRC_DIR})
# set_target_properties(your_library_name PROPERTIES
#     ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib
# )

# Optionally, you can uncomment the following lines for individual compilation units with a library:
# foreach(SRC ${SRCS})
#     get_filename_component(FILE_NAME ${SRC} NAME_WE)
#     add_executable(${FILE_NAME} ${SRC})
#     target_link_libraries(${FILE_NAME} PRIVATE your_library_name)
#     set_target_properties(${FILE_NAME} PROPERTIES
#         RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}
#     )
# endforeach()

# Optionally, you can add an installation target
# install(TARGETS ${TARGET} DESTINATION bin)
