cmake_minimum_required(VERSION 3.25)

project(RetroFutureEngine)

add_executable(GuiMain
	src/cpp/engine.cpp
	src/cpp/engine.hpp)

target_sources(GuiMain
	PRIVATE
        src/cpp/main.cpp
        src/cpp/utils/files.cpp
        src/cpp/utils/files.hpp
        src/cpp/utils/log.cpp
        src/cpp/utils/log.hpp
		external/glad/src/gl.c
)

target_link_libraries(GuiMain
	PRIVATE
		glfw
)

target_include_directories(GuiMain
	PRIVATE
        external/glad/include
        src/cpp
)