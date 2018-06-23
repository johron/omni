#pragma once
#include <thread>
#include "window.h"
#include "render_commands.h"
#include <atomic>

namespace omni {
	class render_engine : public util::uncopyable {
	public:
		render_engine();
		~render_engine();

		void process_events();
		void process_commands();

		using render_commands = command_list<render_command>;
		render_commands& command_queue();

	private:
		void render_callback();

		std::thread m_render_thread;
		std::atomic<bool> m_render_thread_active;

		render_commands m_current_list;
		render_commands m_process_list;

	};
}