#ifndef PLAYER_H_

#define PLAYER_H_

#include "physicsObject.h"

class Player :public physicsObject
{
	GLFWwindow* window;
	int height;
	int width;
public:
	Player(modelImporter* importer, Physics* phys, GLFWwindow* _window) :physicsObject("resources/bartek/untitled.gltf", importer, phys)
	{
		this->window = _window;
		this->disableRotation();
	}
	void process(float dt, Shader& shader, Camera& camera)
	{
		this->getInfoFromPhys();
		ingameObject::process(dt, shader, camera);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			glm::vec3 temp = camera.Orientation;
			Vector3 vec(temp.x, temp.y, temp.z);
			body->setLinearVelocity(vec);
		}
		camera.Position = this->model.translation;
		//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		//{
		//	Position += speed*dt * -glm::normalize(glm::cross(Orientation, Up));
		//}
		//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		//{
		//	Position += speed*dt * -Orientation;
		//}
		//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		//{
		//	Position += speed*dt * glm::normalize(glm::cross(Orientation, Up));
		//}
		//if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		//{
		//	Position += speed*dt * Up;
		//}
		//if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		//{
		//	Position += speed*dt * -Up;
		//}

		//camera.Position = this->model.translation;
		//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		//{


		//	if (firstClick)
		//	{
		//		glfwSetCursorPos(window, (width / 2), (height / 2));
		//		firstClick = false;
		//	}

		glfwGetWindowSize(window, &width, &height);
		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		float sensitivity = 100.0f;

		float rotX = sensitivity * (float)(mouseY - (height/ 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		glm::vec3 newOrientation = glm::rotate(camera.Orientation, glm::radians(-rotX), glm::normalize(glm::cross(camera.Orientation, camera.Up)));

		if (abs(glm::angle(newOrientation, camera.Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			camera.Orientation = newOrientation;
		}
		camera.Orientation = glm::rotate(camera.Orientation, glm::radians(-rotY), camera.Up);
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
};
#endif 
