#pragma once
#include "render_commands.h"

namespace omni {
	template <int TYPE>
	class buffer {
	public:
		template <typename T>
		buffer(const T& data)
			: m_id(generateBuffer()) {
			immediate_command<commands::bind_buffer>(TYPE, m_id);
			immediate_command<commands::buffer_data>(TYPE, sizeof(data), data, GL_STATIC_DRAW);
		}

		const GLuint m_id;
	private:
		GLuint generateBuffer() {
			GLuint buffer(-1);
			glGenBuffers(1, &buffer);
			return buffer;
		}
	};

	using vertex_buffer = buffer<GL_ARRAY_BUFFER>;

}