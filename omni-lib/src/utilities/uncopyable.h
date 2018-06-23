#pragma once

namespace util {
	class uncopyable {
	public:
		uncopyable() = default;
		uncopyable(const uncopyable& other) = delete;
		uncopyable(uncopyable&& other) = delete;
		virtual ~uncopyable() = default;

		uncopyable& operator=(const uncopyable& other) = delete;
		uncopyable& operator=(uncopyable&& other) = delete;
	};
}
