#include "precompiledHeader.h"
#include "JanModule.h"

extern Mesh cube;
void JanModule::start()
{
	transform.setPosition(0.0f, -1.0f, -3.0f);

}

void JanModule::stop()
{

}

void JanModule::renderDebug()
{
	Transform modelT;
	modelT.setPosition(glm::vec3(0, 0, -3));
	modelT.setScale(1.0f);



	//modelT.setPosition(glm::vec3(0, 1, -3));
	//Engine::get().setModelObjectConstants(modelT.asMatrix(), glm::vec4(1, 0, 0, 1));
	//quad.render();

	//modelT.setPosition(glm::vec3(0, -0.5, -1));
	//modelT.setScale(2.5);
	
	glm::vec3 euler = modelT.getEulerAngles();
	modelT.setEulerAngles(euler.x + glfwGetTime() * 25, euler.y, euler.z);

	modelT.setPosition(glm::vec3(5, 0, 5));
	Engine::get().setModelObjectConstants(modelT.asMatrix(), glm::vec4(1, 1, 1, 1.0f));
	cube.activateAndRender();

	modelT.setEulerAngles(euler.x, euler.y + glfwGetTime() * 25, euler.z);

	modelT.setPosition(glm::vec3(-5, 0, 5));
	Engine::get().setModelObjectConstants(modelT.asMatrix(), glm::vec4(1, 1, 1, 1.0f));
	cube.activateAndRender();

	modelT.setEulerAngles(euler.x, euler.y, euler.z + glfwGetTime() * 25);

	//modelT.setRotation(glm::identity<glm::mat4>());
	modelT.setPosition(glm::vec3(0, 0, 5));
	Engine::get().setModelObjectConstants(modelT.asMatrix(), glm::vec4(1, 1, 1, 1.0f));
	cube.activateAndRender();

}
void JanModule::update(float elapsed)
{

}

JanModule::JanModule()
{
}


JanModule::~JanModule()
{
}