cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)
PROJECT(Bridge C CXX)

find_package(OpenGL REQUIRED)

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_HOME_DIRECTORY}
    )

include_directories(
    include
    src
)

set( ADDITIONAL_LIBS 
    -lGLU 
    -pthread
    -lrt
    -lXinerama
    -lXrandr
    -lXxf86vm
    -lXi
    -lXcursor
    -lfreetype 
    -lX11 
    -lm
    -lGL
    -ldl
)

set(LIBRARIES
  ${ADDITIONAL_LIBS}  
)

add_executable(main.exe main.cpp include/glad/glad.c)

target_link_libraries(main.exe ${PROJECT_SOURCE_DIR}/lib/libglfw3.a ${LIBRARIES})