#version 330 core

out vec4 FragColor;
in vec2 textCoord;

uniform sampler2D screenTexture;
uniform float time;
uniform vec2 mouseFocus;

struct ChromaticAberation_t{
    float redOff, greenOff, blueOff;
};


struct Effects_t{
    bool bloom, chromaticAberation;
};

uniform ChromaticAberation_t cAberation;
uniform Effects_t effects;

void main() {

    if(effects.chromaticAberation){
        vec2 direction = textCoord - vec2(0.0);

        FragColor.r = texture(screenTexture, textCoord - (direction * cAberation.redOff)).r;
        FragColor.g = texture(screenTexture, textCoord - (direction * cAberation.greenOff)).g;
        FragColor.ba = texture(screenTexture, textCoord - (direction * cAberation.blueOff)).ba;
    }
    else{
        FragColor = texture(screenTexture, textCoord);
    }
}