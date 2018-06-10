#pragma once

namespace omni {
	template <int TYPE>
	class buffer {
	public:
		template <typename T>
		buffer(const T& data)
			: m_id(generateBuffer()) {
			glBindBuffer(TYPE, m_id);
			glBufferData(TYPE, sizeof(data), data, GL_STATIC_DRAW);
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