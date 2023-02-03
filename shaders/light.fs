#version 460 core
out vec4 Fragcolor;

uniform vec3 lightColor;

void main(){
	Fragcolor = vec4(lightColor,1.0);
}