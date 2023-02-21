#version 460 core

layout (location=0) in vec3 aPos;

out vec3 textCoords;

uniform mat4 projection;
uniform mat4 view;

void main(){
	
	//inverting z because cubemaps uses left handed coordinate sytem
	textCoords = vec3(aPos.xy, -aPos.z);

	gl_Position = projection * view * vec4(aPos,1.0);
}