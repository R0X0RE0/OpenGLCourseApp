#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

out vec4 vColor;
out vec2 texCoord;
out vec3 Normal;
out vec3 FragPos;


in vec4 color;



uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()  {
	gl_Position = projection * view * model * vec4(pos, 1.0);
	vColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
	
	texCoord = tex;

	Normal = mat3(transpose(inverse(model))) * norm;
	
	FragPos = (model * vec4(pos, 1.0)).xyz;
	vec3 a = vec3(1, 2, 3);
}