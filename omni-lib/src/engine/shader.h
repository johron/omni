#pragma once
#include <string>

namespace omni {
	template <GLenum TYPE>
	class shader {
	public:
		static constexpr bool check_for_errors = true;

		shader(const char* content) : m_id(glCreateShader(TYPE)) {
			glShaderSource(m_id, 1, &content, nullptr);
			glCompileShader(m_id);

			if (check_for_errors) {
				int success(-1);
				glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
				if (!success) {
					char buffer[512];
					glGetShaderInfoLog(m_id, 512, nullptr, buffer);
					throw std::runtime_error(buffer);
				}
			}
		}

		~shader() = default;

		const GLuint m_id;
	};

	using vertex_shader = shader<GL_VERTEX_SHADER>;
	using fragment_shader = shader<GL_FRAGMENT_SHADER>;
}  // namespace omni