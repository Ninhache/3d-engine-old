#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextCoord;

out vec2 textCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main() {

    gl_Position = projection * view * model * vec4(aPos + aNormal * 0.07, 1.0f);

    //Vertex in world coordinates to make lightning calculations
    fragPos = vec3(model * vec4(aPos, 1.0f));

    textCoord = aTextCoord;
    //Transforming normal vectors to world coordinates
    normal = normalMatrix * aNormal;
}