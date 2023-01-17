cmake_minimum_required(VERSION 3.10)

project(sfmlTEST)

set(SRC "${PROJECT_SOURCE_DIR}/source/main.cpp")

include_directories(
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/include
)

file(GLOB all_SRCS
	"${PROJECT_SOURCE_DIR}/include/*.h"
	"${PROJECT_SOURCE_DIR}/include/*.hpp"
	"${PROJECT_SOURCE_DIR}/source/*.c"
	"${PROJECT_SOURCE_DIR}/source/*.cpp"
)

link_directories(
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/include
)

add_executable(sfmlTEST ${all_SRCS})

find_package (SFML 2.5 COMPONENTS graphics audio network REQUIRED)

target_link_libraries(
	sfmlTEST
	PUBLIC
	sfml-system
	sfml-graphics
	sfml-audio
	sfml-network
)

target_compile_features(sfmlTEST PUBLIC cxx_std_17)
