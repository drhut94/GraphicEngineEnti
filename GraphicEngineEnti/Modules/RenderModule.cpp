#include "precompiledHeader.h"
#include "RenderModule.h"
#include "../Render/Mesh/primitives.h"


extern Mesh quad;
bool RenderModule::init() 
{
	if (!initOpenGL()) return false;
	initRender();
	glEnable(GL_DEPTH_TEST);	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}


void RenderModule::render()
{
	

	


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		for (auto& module : Engine::get().getActiveModules())
		{
			module->renderDebug();
		}
	
		

		glfwSwapBuffers(window->getWindowGL());
		glfwPollEvents();
	
	
}
void RenderModule::destroy()
{
	glfwDestroyWindow(window->getWindowGL());
	glfwTerminate();
	delete window;
	exit(EXIT_SUCCESS);
}

WindowGLFW * RenderModule::getCtxWindow()
{
	return window;
}

void RenderModule::initRender()
{
	createPrimitives();


	Shader vertex, fragment;

	vertex.init("Shader/data/vertexShader.vs", GL_VERTEX_SHADER);
	fragment.init("Shader/data/fragmentShader.fs", GL_FRAGMENT_SHADER);
	program = glCreateProgram();
	glAttachShader(program, vertex.getId());
	glAttachShader(program, fragment.getId());
	glLinkProgram(program);

	GLuint  vpos_location, vcol_location;
	mvp_location = glGetUniformLocation(program, "MVP");
	vpos_location = glGetAttribLocation(program, "vPos");
	vcol_location = glGetAttribLocation(program, "vCol");


	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE,
		sizeof(VtxPosColor), (void*)0);
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 4, GL_FLOAT, GL_FALSE,
		sizeof(VtxPosColor), (void*)(sizeof(float) * 3));

	glfwGetFramebufferSize(window->getWindowGL(),
		&w, &h);

	


	glClearColor(0.21176470588235294, 0.7019607843137254
		, 0.8705882352941177, 1);

	glViewport(0, 0, w, h);
}

RenderModule::RenderModule(WindowGLFW * w)
{
	assert(w);
	window = w;


}
 static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (key == GLFW_KEY_Q)
	{
	}
}

bool RenderModule::initOpenGL() const
{

	//TODO: ERROR CALLBACK DEVELOPMENT



	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	if (window->getWindowGL() == nullptr)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
		return false;
	}

	
	glfwSetKeyCallback(window->getWindowGL(),key_callback);

	glfwMakeContextCurrent(window->getWindowGL());

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);


	return true;


}

RenderModule::~RenderModule()
{
}

void RenderModule::setModelObjectConstants(const glm::mat4 model, const glm::vec4 color)
{

	mvp = Engine::get().getCamera()->getViewProjection() * model;
	glUseProgram(program);
	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const glm::float32*) & mvp);
	glUniform4fv(glGetUniformLocation(program, "uColor"), 1, (const glm::float32*) &color);
	
}

bool RenderModule::attachShader(GLuint & shaderId)
{
	//Check if shader have been already compiled
	glAttachShader(program, shaderId);

	return true;
}

void RenderModule::useProgram()
{
	glLinkProgram(program);
}
