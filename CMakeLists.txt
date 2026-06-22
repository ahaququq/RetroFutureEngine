cmake_minimum_required(VERSION 3.25)

project(RetroFutureEngine)

add_executable(GuiMain
	src/cpp/utils/files.cpp
	src/cpp/utils/files.hpp
	src/cpp/utils/log.cpp
	src/cpp/utils/log.hpp
	src/cpp/utils/gl.hpp
	src/cpp/utils/glm.hpp
	src/cpp/engine.cpp
	src/cpp/engine.hpp
	src/cpp/glfw_context.cpp
	src/cpp/glfw_context.hpp
	src/cpp/window.cpp
	src/cpp/window.hpp
	src/cpp/main.cpp
	src/cpp/graphics/shader.cpp
	src/cpp/graphics/shader.hpp
	src/cpp/graphics/program.cpp
	src/cpp/graphics/program.hpp
	src/cpp/graphics/buffer.cpp
	src/cpp/graphics/buffer.hpp
	src/cpp/objects/camera.cpp
	src/cpp/objects/camera.hpp
	src/cpp/transform/transform.cpp
	src/cpp/transform/transform.hpp
	src/cpp/transform/pos_transform.cpp
	src/cpp/transform/pos_transform.hpp
)

target_sources(GuiMain
	PRIVATE
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