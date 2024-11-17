#include "camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::update(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0);

	glm::vec3 transformedPos = Position;
	transformedPos.y += 0.5;
	view = glm::lookAt(transformedPos - Orientation, transformedPos, Up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);
	cameraMatrix = projection * view;
}

void Camera::matrix(Shader shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.program, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));

}