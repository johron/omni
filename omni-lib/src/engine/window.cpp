#include "window.h"

namespace {
	void window_input(GLFWwindow* window, int key, int scancode, int action, int modifiers) {
		auto user_window = static_cast<omni::window*>(glfwGetWindowUserPointer(window));
		if (user_window) {
			user_window->input_callback(key, scancode, action, modifiers);
		} else {
			throw std::logic_error("Unable to process window input");
		}

	}
}

namespace omni {
	window::window(uint16_t width, uint16_t height, const std::string& title) 
		: m_window(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr)) {
		if (!m_window) {
			throw std::runtime_error("Failed to initialize glfw window");
		}

		glfwSetWindowUserPointer(m_window, this);
		glfwSetKeyCallback(m_window, ::window_input);

		// needs to be handled differently to support multiple windows 
		glfwMakeContextCurrent(m_window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			throw std::runtime_error("Failed to initialize GLAD");
		}
	}

	window::~window() {
		glfwDestroyWindow(m_window);
	}

	bool window::should_close() const {
		return glfwWindowShouldClose(m_window);
	}

	void window::request_close() {
		glfwSetWindowShouldClose(m_window, GLFW_TRUE);
	}

	void window::input_callback(int key, int scancode, int action, int modifiers) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			request_close();
		}
	}

	void window::swap_buffers() {
		glfwSwapBuffers(m_window);
	}

}