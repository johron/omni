#pragma once

namespace omni {
	namespace commands {
		namespace util {
			struct uniform_location {
				uniform_location(GLint program, std::string_view name)
					: m_program(program), m_name(name) { }

				GLint get() const { return glGetUniformLocation(m_program, m_name.c_str()); }

				const GLint m_program;
				const std::string m_name;
			};

			struct attribute_location {
				attribute_location(GLint program, std::string_view name)
					: m_program(program), m_name(name) { }

				GLint get() const { return glGetAttribLocation(m_program, m_name.c_str()); }

				const GLint m_program;
				const std::string m_name;
			};

			struct fixed_location {
				fixed_location(GLint location)
					: m_location(location) { }

				GLint get() const { return m_location; }
				const GLint m_location;
			};

			struct get_location {
				template <typename T>
				GLint operator()(const T& data) {
					return data.get();
				}
			};
		}

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
			struct set_uniform_data {
				template <typename Location>
				set_uniform_data(const Location& location)
					: m_location(std::visit(util::get_location(), location)) { }

				template <typename T>
				void operator()(const T& data) { static_assert(false, && "Unknown type"); }

				template <> void operator()(const GLint& data) { glUniform1i(m_location, data); }
				template <> void operator()(const glm::mat4& data) { glUniformMatrix4fv(m_location, 1, GL_FALSE, glm::value_ptr(data)); }

				const GLint m_location;
			};

			using data_holder = std::variant<GLint, glm::mat4>;
			using location_holder = std::variant<util::fixed_location, util::uniform_location>;

			template <typename T>
			uniform_data(GLuint location, T&& data)
				: m_data(std::forward<T>(data))
				, m_location(std::in_place_type_t<util::fixed_location>{}, location) { }

			template <typename T>
			uniform_data(GLint program, std::string_view name, T&& data)
				: m_data(std::forward<T>(data))
				, m_location(std::in_place_type_t<util::uniform_location>{}, program, name) { }


			void apply() {
				std::visit(set_uniform_data(m_location), m_data);
			}

			data_holder m_data;
			location_holder m_location;
		};

		struct draw_arrays {
			draw_arrays(GLenum mode, GLint first, GLsizei count)
				: m_mode(mode), m_first(first), m_count(count) { }

			void apply() {
				glDrawArrays(m_mode, m_first, m_count);
			}

			const GLenum m_mode;
			const GLint m_first;
			const GLsizei m_count;
		};

		struct vertex_attrib_ptr {
			using location_holder = std::variant<util::fixed_location, util::attribute_location>;

			vertex_attrib_ptr(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
				: m_location(std::in_place_type_t<util::fixed_location>{}, index)
				, m_size(size), m_type(type), m_normalized(normalized), m_stride(stride), m_pointer(pointer) { }

			vertex_attrib_ptr(GLint program, std::string_view name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
				: m_location(std::in_place_type_t<util::attribute_location>{}, program, name)
				, m_size(size), m_type(type), m_normalized(normalized), m_stride(stride), m_pointer(pointer) { }

			void apply() {
				glVertexAttribPointer(std::visit(util::get_location(), m_location), m_size, m_type, m_normalized, m_stride, m_pointer);
			}

			const location_holder m_location;
			const GLint m_size;
			const GLenum m_type;
			const GLboolean m_normalized;
			const GLsizei m_stride;
			const GLvoid* m_pointer;
		};

		struct enable_vertex_attrib_array {
			using location_holder = std::variant<util::fixed_location, util::attribute_location>;
			enable_vertex_attrib_array(GLuint index)
				: m_location(std::in_place_type_t<util::fixed_location>{}, index) { }

			enable_vertex_attrib_array(GLint program, std::string_view name)
				: m_location(std::in_place_type_t<util::attribute_location>{}, program, name) { }

			void apply() {
				glEnableVertexAttribArray(std::visit(util::get_location(), m_location));
			}

			const location_holder m_location;
		};

		struct disable_vertex_attrib_array {
			using location_holder = std::variant<util::fixed_location, util::attribute_location>;
			disable_vertex_attrib_array(GLuint index)
				: m_location(std::in_place_type_t<util::fixed_location>{}, index) { }

			disable_vertex_attrib_array(GLint program, std::string_view name)
				: m_location(std::in_place_type_t<util::attribute_location>{}, program, name) { }

			void apply() {
				glDisableVertexAttribArray(std::visit(util::get_location(), m_location));
			}

			const location_holder m_location;
		};

		struct buffer_data {
			buffer_data(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
				: m_target(target), m_size(size), m_data(data), m_usage(usage) { }

			void apply() {
				glBufferData(m_target, m_size, m_data, m_usage);
			}

			const GLenum m_target;
			const GLsizeiptr m_size;
			const GLvoid* m_data;
			const GLenum m_usage;
		};

		struct bind_buffer {
			bind_buffer(GLenum target, GLuint buffer)
				: m_target(target), m_buffer(buffer) { }

			void apply() {
				glBindBuffer(m_target, m_buffer);
			}

			const GLenum m_target;
			const GLuint m_buffer;
		};
	}

	using render_command = std::variant<
		commands::viewport,
		commands::bind_buffer, 
		commands::buffer_data,
		commands::clear,
		commands::clear_color,
		commands::draw_arrays,
		commands::uniform_data,
		commands::use_program,
		commands::vertex_attrib_ptr,
		commands::enable_vertex_attrib_array,
		commands::disable_vertex_attrib_array>;

	template <typename Command>
	struct immediate_command {
		template <typename... Args>
		immediate_command(Args&&... args) {
			Command cmd(std::forward<Args>(args)...);
			cmd.apply();
		}
	};

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