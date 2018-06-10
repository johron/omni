#pragma once
#include "window.h"

namespace omni {
	class engine : public util::uncopyable {
	public:
		engine();
		~engine();

		void process_events();
	};
}