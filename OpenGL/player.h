#ifndef PLAYER_H_

#define PLAYER_H_

#include "physicsObject.h"

class Player :public physicsObject
{
	GLFWwindow* window;
	bool running = false;
	bool animWalkTrigger = false;
	bool animIdleTrigger = false;
	int height;
	int width;
	int iters = 0;
	double cooldown = 5;
	bool collisionTest = false;
public:
	glm::vec3 location;
	int lives = 3;
	Player(modelImporter* importer, Physics* phys, GLFWwindow* _window) :physicsObject("resources/bartek/bartek.gltf", importer, phys, glm::vec3(0.1,0.1,0.1))
	{
		this->model.animations["breathing"].setUp(true);
		this->model.animations["running"].setUp(true);
		this->model.playAnimation("breathing");
		this->window = _window;
		this->disableRotation();
		this->model.linOffset.y += 0.3;
		this->model.scale = glm::vec3(0.05, 0.05, 0.05);
		this->body->setLinearDamping(5);

	}

	void process(float dt, Shader& shader, Camera& camera)
	{
		this->getInfoFromPhys();
		ingameObject::process(dt, shader, camera);

		bool w =  glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
		bool a = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
		bool s = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
		bool d = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);
		bool space = (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);
		bool keyboardInput = w || a || s || d;


		if (keyboardInput)
		{
			glm::vec3 temp = glm::vec3(0, 0, 0);
			if (w)
			{

				temp += camera.Orientation;
			}

			if (a)
			{
				temp += -glm::normalize(glm::cross(camera.Orientation, camera.Up));;

			}

			if (s)
			{
				temp += -camera.Orientation;

			}

			if (d)
			{
				temp += glm::normalize(glm::cross(camera.Orientation, camera.Up));;
			}

			
			if (temp.x != 0 && temp.z != 0)
			{
				this->running = true;

				temp = glm::normalize(temp);
				Vector3 vec(temp.x, 0, temp.z);
				glm::vec3 temp1 = glm::vec3(temp.x, 0, temp.z);
				glm::vec3 test = glm::vec3(1, 0, 0);

				float angle = acos(glm::dot(test, temp1) / (glm::length(test) * glm::length(temp1)));

				if (temp.z > 0)
				{
					angle = 8 * acos(1) - angle;
				}

				glm::quat rot = glm::angleAxis(angle, glm::vec3(0.f, 1.f, 0.f));

				this->model.rotation = rot;

				vec = vec * (glm::length(temp)) / vec.length();
				body->setLinearVelocity(Vector3(0, this->body->getLinearVelocity().y, 0));
				body->applyLocalForceAtCenterOfMass(vec * 200);
			}
			else
			{
				this->running = false;
			}


		}
		else
		{
			this->running = false;
		}

		if (space)
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


		if (cooldown < 6)
		{
			cooldown += dt;
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



		location = this->model.translation;

		if (this->running)
		{
			if (this->animWalkTrigger)
			{
				this->animWalkTrigger = false;
				this->model.playAnimation("running");
			}
			if (!this->animIdleTrigger)
			this->animIdleTrigger = true;
		}
		else
		{
			if (this->animIdleTrigger)
			{
				this->animIdleTrigger = false;
				this->model.playAnimation("breathing");
			}
			if (!this->animWalkTrigger)
				this->animWalkTrigger = true;
		}
	}
	void getInfoFromPhys()
	{
		InfoPack pack = this->phys->getInfoOnBody(this->body);

		this->model.translation = pack.position;


	}
	void collidedWith(Body* bd) 
	{
		if (this->body->getLinearVelocity().y < -0.1)
			((physicsObject*)(bd->getUserData()))->collidedWithPlayer();
	}

	void collidedWithMonster()
	{
		
		if(lives > 0 && cooldown > 5 && this->body->getLinearVelocity().y >= -0.1)
		{
			lives--;
			std::cout << "Straci³eœ ¿ycie!" << std::endl;
			cooldown = 0;
		}
		
	}

	bool isDead()
	{
		return lives == 0;
	}

};
#endif 