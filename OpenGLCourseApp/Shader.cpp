#include "Shader.h"
#include <vector>

using namespace std;

Shader::Shader() {
	shaderID = 0;
	uniformModel = 0;
	uniformView = 0;
	uniformProjection = 0;
	uniformAmbientIntensity = 0;
	uniformAmbientColor = 0;
	uniformDiffuseIntensity = 0;
	uniformDirection = 0;
	uniformSpecularIntensity = 0;
	uniformSpecularReflection = 0;
	uniformSpecularView = 0;
	
}

void Shader::createFromString(const char* vertexCode, const char* fragmentCode) {
	compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const char* vertexLocation, const char* fragmentLocation){
	std::string vertexString = readFile(vertexLocation);
	std::string fragmentString = readFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	compileShader(vertexCode, fragmentCode);
}

std::string Shader::readFile(const char* fileLocation) {
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileLocation) { printf("Failed to read %s! File doesn't exist.", fileLocation);  return ""; }

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::compileShader(const char* vertexCode, const char* fragmentCode) {
	shaderID = glCreateProgram();

	//return error if shader not created
	if (!shaderID) {
		printf("Shader error! Not created\n");
		return;
	}
	//add shaders
	addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar elog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(elog), NULL, elog);
		printf("Error linking program: %s \n", elog);
		return;
	}
	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(elog), NULL, elog);
		printf("Error validating program: %s \n", elog);
		return;
	}
	
	

	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformView = glGetUniformLocation(shaderID, "view");
	uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.ambientIntensity");
	uniformAmbientColor = glGetUniformLocation(shaderID, "directionalLight.color");
	uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.diffuseIntensity");
	uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
	uniformSpecularReflection = glGetUniformLocation(shaderID, "directionalLight.reflection");
	uniformSpecularView = glGetUniformLocation(shaderID, "directionalLight.viewPos");
	uniformSpecularIntensity = glGetUniformLocation(shaderID, "directionalLight.specularIntensity");

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == 0) {
		glGetShaderInfoLog(shaderID, sizeof(elog), NULL, elog);
		printf("Error compiling shader: %s \n", elog);
		glDeleteShader(shaderID);
		return;
	}
}
GLuint Shader::getProjectionLocation() {
	return uniformProjection;
}
GLuint Shader::getModelLocation() {
	return uniformModel;
}
GLuint Shader::getViewLocation() {
	return uniformView;
}
GLuint Shader::getAmbientColorLocation() {
	return uniformAmbientColor;
}
GLuint Shader::getAmbientIntensityLocation() {
	return uniformAmbientIntensity;
}
GLuint Shader::getDiffuseIntensityLocation() {
	return uniformDiffuseIntensity;
}
GLuint Shader::getDirectionLocation() {
	return uniformDirection;
}
GLuint Shader::getSpecularReflectionLocation() {
	return uniformSpecularReflection;
}
GLuint Shader::getSpecularViewLocation() {
	return uniformSpecularView;
}
GLuint Shader::getSpecularIntensityLocation() {
	return uniformSpecularIntensity;
}
void Shader::useShader() {
	glUseProgram(shaderID);
}

void Shader::clearShader() {
	if (shaderID != 0) { glDeleteProgram(shaderID); shaderID = 0; }
	uniformModel = 0;
	uniformProjection = 0;
}

void Shader::addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar elog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(theShader, sizeof(elog), NULL, elog);
		printf("Error compiling the %d shader: %s \n", shaderType, elog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

Shader::~Shader() {
	clearShader();
}