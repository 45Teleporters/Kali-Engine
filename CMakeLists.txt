cmake_minimum_required(VERSION 3.23)

project(Kali)

add_executable(Kali)

target_sources(Kali
	PRIVATE
		${CMAKE_SOURCE_DIR}/src/main.cpp
		${CMAKE_SOURCE_DIR}/src/debug.h 
		${CMAKE_SOURCE_DIR}/src/shaders.h
		${CMAKE_SOURCE_DIR}/include/glad.h
		${CMAKE_SOURCE_DIR}/include/stb_image.h
		${CMAKE_SOURCE_DIR}/include/glfw3.h
		${CMAKE_SOURCE_DIR}/include/glfw3native.h
		${CMAKE_SOURCE_DIR}/include/khrplatform.h
)

target_link_libraries(Kali 
	${CMAKE_SOURCE_DIR}/libs/libglfw3.a
	${CMAKE_SOURCE_DIR}/libs/glad.c
)
