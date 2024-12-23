#include "shaders.h"

std::string getContents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	throw(errno);
}

Shader::Shader(const char* vertFile, const char* fragFile, int lightNum)
{
	std::string vertexCode = getContents(vertFile);
	std::string fragCode = getContents(fragFile);

	// ta
	fragCode = std::string(fragCode.begin(), fragCode.begin() + 18) + "#define NR_LIGHTS " + std::to_string(lightNum) + "\n" + std::string(fragCode.begin() + 19, fragCode.end());

	const char* vertSource = vertexCode.c_str();
	const char* fragSource = fragCode.c_str();

	// Tworzymy i kompilujemy vertex shader (czyli jakby ksztalt naszego obiektu)
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertSource, NULL);
	glCompileShader(vertexShader);

	// Tworzymy i kompilujemy fragment shader ktory odpowiada za kolorki
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragSource, NULL);
	glCompileShader(fragmentShader);

	//int bufflen;
	//glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &bufflen);
	//GLchar* log_string = new char[bufflen + 1];
	//glGetShaderInfoLog(fragmentShader, bufflen, 0, log_string);
	//std::cout << log_string;

	// Ze skompilowanych shaderow tworzyny program ktory nam wszystko ladnie obsluzy - linkujemy wszystko razem
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	// Usuwamy dane o shaderze bo po utworzeniu programu ich nie potrzebujemy
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::on()
{
	glUseProgram(program);
}

void Shader::remove()
{
	glDeleteProgram(program);
}