#version 330

in vec4 vColor;
in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

struct DirectionalLight {
	vec3 color;
	float ambientIntensity;

	vec3 direction;
	float diffuseIntensity;

	vec3 reflection;
	vec3 viewPos;
	float specularIntensity;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;

void main() {
	
	vec4 ambientColor = vec4(directionalLight.color, 1.0f) * directionalLight.ambientIntensity;
	
	float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0f);
	vec4 diffuseColor = vec4(directionalLight.color, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;
	
	//vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	
	vec3 viewDir = normalize(directionalLight.viewPos - FragPos);
	vec3 reflectionDir = normalize(reflect(-directionalLight.direction, normalize(Normal)));
	float specularFactor = pow(max(dot(normalize(viewDir), normalize(directionalLight.reflection)), 0.0f), 32); 
	vec4 specularColor = vec4(directionalLight.color, 1.0f) * specularFactor * directionalLight.specularIntensity;
	
	color = texture(theTexture, texCoord) * (ambientColor + diffuseColor + specularColor);
}