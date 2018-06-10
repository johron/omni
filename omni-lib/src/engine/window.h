#pragma once

namespace omni {
	class window {
	public:
		window(uint16_t width, uint16_t height, const std::string& title = "unnamed window");
		~window();
		
		bool should_close() const;
		void request_close();

		void input_callback(int key, int scancode, int action, int modifiers);
		void swap_buffers();

	private:
		GLFWwindow* m_window;
	};
}