#its kind shit file i need to rework it

cmake_minimum_required(VERSION 3.10.0)
project(TEKKO VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set sfml dir
set(SFML_DIR "C:/Users/artem/Desktop/c_projects/cmake/sfml/SFML-3.1.0/lib/cmake/SFML")
find_package(SFML 3.1.0 COMPONENTS Graphics Window System REQUIRED)

#setting source files

set(SOURCES src/main.cpp src/Player.cpp src/utils/Math.cpp)
set(HEADERS src/headers/Player.hpp src/headers/utils/Math.hpp)

add_executable(TEKKO ${SOURCES} ${HEADERS})

target_link_libraries(TEKKO PRIVATE SFML::Graphics SFML::Window SFML::System)

# add dlls
add_custom_command(TARGET TEKKO POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_RUNTIME_DLLS:TEKKO>
    $<TARGET_FILE_DIR:TEKKO>
    COMMAND_EXPAND_LISTS
)

include(CTest)
enable_testing()

