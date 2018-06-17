#include "render_engine.h"
#include <iostream>

void error_callback(int error, const char* description) {
	throw std::runtime_error(std::to_string(error) + ":" + description);
}

namespace omni {
	render_engine::render_engine() {
		glfwSetErrorCallback(&error_callback);

		if (!glfwInit()) {
			error_callback(0, "Failed to initialize glfw");
		}

		m_render_thread = std::thread(std::bind(&render_engine::render_callback, this));
	}

	render_engine::~render_engine() {
		m_render_thread_active = false;
		m_render_thread.join();
		glfwTerminate();
	}

	void render_engine::process_events() { 
		glfwPollEvents();
	}

	void render_engine::process_commands() { 
		m_current_list.visit(omni::command_runner());
	}

	render_engine::render_commands& render_engine::command_queue() {
		return m_current_list;
	}

	void render_engine::render_callback() { 
		m_render_thread_active = true;
		OutputDebugString("render begin\n");
		

		while (m_render_thread_active) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		OutputDebugString("render end\n");
	}
}
