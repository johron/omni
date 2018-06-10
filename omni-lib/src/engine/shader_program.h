#pragma once

namespace omni {
	class shader_program {
	public:
		template <class... Args>
		shader_program(Args... args)
			: m_id(glCreateProgram()) {
			attach_shader(std::forward<Args>(args)...);
			glLinkProgram(m_id);

			int success(-1);
			glGetProgramiv(m_id, GL_LINK_STATUS, &success);
			if (!success) {
				char buffer[512];
				glGetProgramInfoLog(m_id, 512, NULL, buffer);
				throw std::runtime_error(buffer);
			}
		}

		const GLuint m_id;

	private:
		template <class T, class... Args>
		void attach_shader(T&& shader, Args... tail) {
			attach_shader(std::forward<T>(shader));
			attach_shader(std::forward<Args>(tail)...);
		}

		template <class T>
		void attach_shader(T&& shader) {
			glAttachShader(m_id, shader.m_id);
		}
	};
}