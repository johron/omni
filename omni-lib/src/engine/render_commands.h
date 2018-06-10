#pragma once

namespace omni {
	namespace commands {
		struct viewport {
			viewport(GLint x, GLint y, GLsizei width, GLsizei height)
				: m_x(x), m_y(y), m_width(width), m_height(height) { }

			void apply() {
				glViewport(m_x, m_y, m_width, m_height);
			}

			const GLint m_x;
			const GLint m_y;
			const GLsizei m_width;
			const GLsizei m_height;
		};

		struct clear {
			clear(GLbitfield mask)
				: m_mask(mask) { }

			void apply() {
				glClear(m_mask);
			}

			const GLbitfield m_mask;
		};

		struct clear_color {
			clear_color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
				: m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) { }

			void apply() {
				glClearColor(m_red, m_green, m_blue, m_alpha);
			}

			const GLfloat m_red;
			const GLfloat m_green;
			const GLfloat m_blue;
			const GLfloat m_alpha;
		};

		struct use_program {
			use_program(GLuint program)
				: m_program(program) { }

			void apply() {
				glUseProgram(m_program);
			}

			const GLuint m_program;
		};

		/*
		struct uniform_data {
			struct visitor {
				visitor(GLint location)
					: m_location(location) { }

				template <typename T>
				void operator()(T&& data) { static_assert(false, && "Unknown type"); }

				template <>
				void operator()(const glm::mat4& data) { 
					glUniformMatrix4fv(m_location, 1, GL_FALSE, glm::value_ptr(data)); 
				}

				const GLint m_location;
			};

			using data = std::variant<
				GLint, glm::mat4>;

			template <typename T>
			uniform_data(GLuint program, T&& data) { }

			void apply() {
				std::visit(visitor(m_location), m_data);
			}

			GLint m_location;
			data m_data;
		};
		*/
	}

	using render_command = std::variant<
		commands::viewport, 
		commands::clear,
		commands::clear_color,
		//commands::uniform_data,
		commands::use_program>;

	struct command_runner {
		template <typename T>
		void operator()(T& command) const {
			command.apply();
		}
	};

	template <typename T>
	class command_list {
	public:
		command_list() = default;
		~command_list() = default;

		template <typename Command, typename... Args>
		void emplace_back(Args&&... args) {
			m_commands.emplace_back(std::in_place_type_t<Command>{}, std::forward<Args>(args)...);
		}

		void reserve(size_t size) {
			m_commands.reserve(size);
		}

		void clear() {
			m_commands.clear();
		}

		template <typename Visitor>
		void visit(Visitor&& visitor) {
			for (auto& cmd : m_commands) {
				std::visit(visitor, cmd);
			}
		}

		void swap(command_list<T>& other) noexcept {
			std::swap(m_commands, other.m_commands);
		}

	private:
		std::vector<T> m_commands;

	};
}