#pragma once

namespace omni {
	namespace util {
		class uncopyable {
		public:
			uncopyable() = default;
			virtual ~uncopyable() = default;

			uncopyable(const uncopyable& other) = delete;
			uncopyable& operator=(const uncopyable& other) = delete;
		};
	}
}