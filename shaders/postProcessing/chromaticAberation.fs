#version 330 core

out vec4 FragColor;
in vec2 textCoord;

uniform sampler2D screenTexture;
uniform float time;
uniform vec2 mouseFocus;

void main()
{ 
    float redOff = 0.009, greenOff = 0.006, blueOff = -0.002;

    vec2 direction = textCoord - vec2(0.0);

    FragColor.r = texture(screenTexture, textCoord - (direction * redOff)).r;
    FragColor.g = texture(screenTexture, textCoord - (direction * greenOff)).g;
    FragColor.ba = texture(screenTexture, textCoord - (direction * blueOff)).ba;
}