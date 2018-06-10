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

		struct uniform_data {
			struct set_uniform {
				template <typename Location>
				set_uniform(const Location& location)
					: m_location(std::visit(get_location(), location)) { }

				template <typename T>
				void operator()(const T& data) { static_assert(false, && "Unknown type"); }

				template <> void operator()(const GLint& data) { glUniform1i(m_location, data); }
				template <> void operator()(const glm::mat4& data) { glUniformMatrix4fv(m_location, 1, GL_FALSE, glm::value_ptr(data)); }

				const GLint m_location;
			};

			using data_holder = std::variant<
				GLint, 
				glm::mat4>;

			struct static_location { 
				static_location(GLint location)
					: m_location(location) { }

				GLint get() const { return m_location; }

				const GLint m_location;
			};

			struct program_location { 
				program_location(GLint program, std::string_view name)
					: m_program(program)
					, m_name(name) { }

				GLint get() const { return glGetUniformLocation(m_program, m_name.c_str()); }

				const GLint m_program;
				const std::string m_name;
			};

			using location_holder = std::variant<
				static_location,
				program_location>;

			struct get_location {
				template <typename T>
				GLint operator()(const T& data) {
					return data.get();
				}
			};

			template <typename T>
			uniform_data(GLuint location, T&& data)
				: m_data(std::forward<T>(data)) 
				, m_location(std::in_place_type_t<static_location>{}, location) { }

			template <typename T>
			uniform_data(GLint program, std::string_view name, T&& data)
				: m_data(std::forward<T>(data))
				, m_location(std::in_place_type_t<program_location>{}, program, name) { }


			void apply() {
				std::visit(set_uniform(m_location), m_data);
			}

			data_holder m_data;
			location_holder m_location;
		};
	}

	using render_command = std::variant<
		commands::viewport, 
		commands::clear,
		commands::clear_color,
		commands::uniform_data,
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