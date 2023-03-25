#version 330 core

out vec4 FragColor;
in vec2 textCoord;

//raw scene texture
uniform sampler2D texture0;

//postProcessed scene's texture;
uniform sampler2D texture1;

struct ChromaticAberation_t {
    float redOff, greenOff, blueOff;
};

struct Bloom_t {
    float intensity;
};

struct Hdr_t {
    float exposure;
};

struct Effects_t{
    bool bloom, chromaticAberation, blur, hdr;
};

uniform ChromaticAberation_t cAberation;
uniform Effects_t effects;

void main() {

    FragColor = texture(texture0, textCoord);
    if (effects.chromaticAberation) {
        vec2 direction = textCoord - vec2(0.0);

        FragColor.r = texture(texture0, textCoord - (direction * cAberation.redOff)).r;
        FragColor.g = texture(texture0, textCoord - (direction * cAberation.greenOff)).g;
        FragColor.ba = texture(texture0, textCoord - (direction * cAberation.blueOff)).ba;
    }
    else if (effects.blur) {
        FragColor = texture(texture1, textCoord);
    }

    else if (effects.bloom) {
        FragColor.rgb = FragColor.rgb * 1.1; // TODO: CHANGE TO A REAL METHOD LOL
    }

    else if (effects.hdr) {
        FragColor = texture(texture1, textCoord);
    }
}