#version 460 core
out vec4 FragColor;

in vec2 textCoord;

uniform sampler2D diffuseMap0;
uniform sampler2D diffuseMap1;
uniform sampler2D diffuseMap2;
uniform sampler2D diffuseMap3;

void main() {
    vec4 color;
    FragColor = texture(diffuseMap0, textCoord);
}