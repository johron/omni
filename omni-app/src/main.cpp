#include <thread>
#include "omni-lib/src/omni.h"
#include "omni-lib/src/engine/render_commands.h"

static const char* vertex_shader_text =
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";
static const char* fragment_shader_text =
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";

int main(int argc, char** argv) {
	omni::engine engine;
	omni::window window(800, 600, "sample window");

	omni::vertex_shader v_shader(vertex_shader_text);
	omni::fragment_shader f_shader(fragment_shader_text);
	omni::shader_program program(v_shader, f_shader);

	struct vertex_data {
		float x;
		float y;
		float r;
		float g;
		float b;
	};

	vertex_data data[3] ={
		{ -0.5f, -0.5f, 1.f, 0.f, 0.f },
		{ 0.5f, -0.5f, 0.f, 1.f, 0.f },
		{ 0.f,  0.5f, 0.f, 0.f, 1.f }
	};

	omni::vertex_buffer v_buffer(data);


	const auto mvp_location = glGetUniformLocation(program.m_id, "MVP");
	const auto vpos_location = glGetAttribLocation(program.m_id, "vPos");
	const auto vcol_location = glGetAttribLocation(program.m_id, "vCol");

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 2));


	omni::command_list<omni::render_command> commands;
	commands.reserve(128);

	while (!window.should_close()) {
		engine.process_events();

 		commands.clear();
		commands.emplace_back<omni::commands::viewport>(0, 0, 800, 600);
		commands.emplace_back<omni::commands::clear_color>(0.2f, 0.03f, 0.3f, 1.0f);
 		commands.emplace_back<omni::commands::clear>(GL_COLOR_BUFFER_BIT);

		float ratio(800/600);

		auto projection = glm::perspective(glm::radians(60.0f), ratio, 0.1f, 100.0f);
		auto view = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		auto model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0, 0, 1));

		const auto mvp = projection * view * model;

		commands.emplace_back<omni::commands::use_program>(program.m_id);
		commands.emplace_back<omni::commands::uniform_data>(program.m_id, "MVP", mvp);
		commands.emplace_back<omni::commands::draw_arrays>(GL_TRIANGLES, 0, 3);
		commands.visit(omni::command_runner());


		window.swap_buffers();
	}

	return 0;
}