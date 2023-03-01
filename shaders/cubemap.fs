#version 460 core

out vec4 FragColor;

in vec3 textCoords;
uniform samplerCube skybox;

void main(){
	FragColor = texture(skybox, textCoords);
}