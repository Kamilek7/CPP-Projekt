#ifndef PLAYER_H_

#define PLAYER_H_

#include "physicsObject.h"

class Player :public physicsObject
{
	GLFWwindow* window;
	int height;
	int width;

	int iters = 0;
	bool collisionTest = false;
public:
	Player(modelImporter* importer, Physics* phys, GLFWwindow* _window) :physicsObject("resources/bartek/untitled.gltf", importer, phys)
	{
		this->window = _window;
		this->disableRotation();
		this->model.linOffset.y += 0.25;
		this->model.scale = glm::vec3(0.5, 0.5, 0.5);
		this->body->setLinearDamping(5);

	}
	void process(float dt, Shader& shader, Camera& camera)
	{
		this->getInfoFromPhys();
		ingameObject::process(dt, shader, camera);


		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{

			glm::vec3 temp = camera.Orientation;
			Vector3 vec(temp.x, 0, temp.z);

			glm::vec3 temp1 = glm::vec3(temp.x, 0, temp.z);
			glm::vec3 test = glm::vec3(1,0,0);

			float angle = acos(glm::dot(test, temp1) / (glm::length(test) * glm::length(temp1)));

			if (temp.z > 0)
			{
				angle = 8 * acos(1) - angle;
			}

			glm::quat rot = glm::angleAxis(angle, glm::vec3(0.f, 1.f, 0.f));

			this->model.rotation = rot;

			vec = vec * (glm::length(temp)) / vec.length();
			body->applyLocalForceAtCenterOfMass(vec*10);
			

		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			glm::vec3 temp = -glm::normalize(glm::cross(camera.Orientation, camera.Up));;
			Vector3 vec(temp.x, 0, temp.z);
			vec = vec * (glm::length(temp)) / vec.length();
			body->applyLocalForceAtCenterOfMass(vec * 10);

		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			glm::vec3 temp = -camera.Orientation;
			Vector3 vec(temp.x, 0, temp.z);
			vec = vec * (glm::length(temp)) / vec.length();
			body->applyLocalForceAtCenterOfMass(vec * 10);

		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			glm::vec3 temp = glm::normalize(glm::cross(camera.Orientation, camera.Up));;
			Vector3 vec(temp.x, 0, temp.z);
			vec = vec * (glm::length(temp)) / vec.length();
			body->applyLocalForceAtCenterOfMass(vec * 10);
		}

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			if (abs(body->getLinearVelocity().y) < 0.1)
			{
				if (!collisionTest)
				{
					collisionTest = true;
				}
				else if (iters < 5)
				{
					iters += 1;
				}
				else if (iters >= 5)
				{
					collisionTest = false;
					iters = 0;
					Vector3 vec(0, 1.0, 0);
					body->applyLocalForceAtCenterOfMass(vec * 700);
				}
			}
			else
			{
				iters = 0;
				collisionTest = false;
			}

		}

		camera.Position = this->model.translation;

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
	void getInfoFromPhys()
	{
		InfoPack pack = this->phys->getInfoOnBody(this->body);

		this->model.translation = pack.position;


	}
};
#endif 
