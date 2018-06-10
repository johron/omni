#include "engine.h"

void error_callback(int error, const char* description) {
	throw std::runtime_error(std::to_string(error) + ":" + description);
}

namespace omni {
	engine::engine() {
		glfwSetErrorCallback(&error_callback);

		if (!glfwInit()) {
			error_callback(0, "Failed to initialize glfw");
		}
	}

	engine::~engine() {
		glfwTerminate();
	}

	void engine::process_events() { 
		glfwPollEvents();
	}
}