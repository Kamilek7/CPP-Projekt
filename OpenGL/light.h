#ifndef LIGHT_H_

#define LIGHT_H_

class Light
{
public:
	glm::vec3 position;
	glm::vec4 color;

	int id;

	float intensity;

	Light(glm::vec3 pos, glm::vec4 col)
	{
		this->position = pos;
		this->color = col;
		static int count = 0;
		id = count;
		count++;
	}
	void process(Shader& shader)
	{

	}
};
#endif // !LIGHT_H_
