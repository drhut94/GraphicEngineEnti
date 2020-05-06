#pragma once
#include "Modules/Module.h"
#include "Render/Mesh/primitives.h"
#include "Geometry/Transform.h"
#include "Modules/RenderModule.h"
#include "Render/Camera/Camera.h"

class JanModule : public Module
{
private:
	Transform quad1, quad2, quad3, cubetransform;
	Camera* cam;
	Camera* cam2;
	GLFWwindow* window;
	glm::vec3 pos;
	glm::vec3 front = glm::vec3(0, 0, -1);

	glm::vec3 target = glm::vec3(0, 0, -1);
	float newAngle = 0.0f;
	float newPitch = 0.0f;
public:

	virtual void start() override;
	virtual void stop() override;
	virtual void renderDebug() override;
	virtual void update(float elapsed)override;

	void cameraController();


	JanModule();
	~JanModule();
};

