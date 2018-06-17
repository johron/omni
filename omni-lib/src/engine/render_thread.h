#pragma once
#include <atomic>

namespace omni {
	class render_thread {
	public:
		render_thread()
			: m_active(true) { }



	private:
		std::atomic<bool> m_active;
	};
}