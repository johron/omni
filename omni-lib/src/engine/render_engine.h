#pragma once

namespace {
	void error_callback(int error, const char* description) {
		throw std::runtime_error(std::to_string(error) + ":" + description);
	}
}

namespace omni {
	class render_engine : public util::uncopyable {
	public:
		render_engine() {
			glfwSetErrorCallback(&error_callback);

			if (!glfwInit()) {
				throw std::runtime_error("Failed to initialize glfw");
			}
		}

		~render_engine() {
			glfwTerminate();
		}

		void process_events() {
			glfwPollEvents();
		}

	private:
		std::thread m_render_thread;
	};
}
