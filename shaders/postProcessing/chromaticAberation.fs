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
    bool reinhard;
    float gamma;
};

struct Effects_t{
    bool bloom, chromaticAberation, blur, hdr;
};

uniform ChromaticAberation_t cAberation;
uniform Hdr_t hdr_t;
uniform Bloom_t bloom_t;
uniform Effects_t effects;


void bloom() {
    vec4 blurColor = FragColor;
    const int kernel_size = 2;
    for (int i = -kernel_size; i <= kernel_size; i++) {
        for (int j = -kernel_size; j <= kernel_size; j++) {
            vec2 offset = vec2(float(i), float(j)) / vec2(textureSize(texture0, 0));
            blurColor += texture2D(texture0, textCoord + offset);
        }
    }

    vec4 originalColor = texture2D(texture0, textCoord);
    vec4 bloomColor = originalColor + (blurColor / (kernel_size * kernel_size + 1));

    FragColor = FragColor + (bloomColor * bloom_t.intensity);
}

void main() {

    vec3 hdrColor = texture(texture0, textCoord).rgb;
    if (effects.hdr) {
        vec3 result;
        if (hdr_t.reinhard) {
            result = hdrColor / (hdrColor + vec3(1.0));
        } else {
            result = vec3(1.0) - exp(-hdrColor * hdr_t.exposure);
        }
        
        result = pow(result, vec3(1.0 / hdr_t.gamma));
        FragColor = vec4(result, 1.0);
    } else {
        FragColor = texture(texture0, textCoord);
    }

    if (effects.chromaticAberation) {
        vec2 direction = textCoord - vec2(0.0);

        FragColor.r = texture(texture0, textCoord - (direction * cAberation.redOff)).r;
        FragColor.g = texture(texture0, textCoord - (direction * cAberation.greenOff)).g;
        FragColor.ba = texture(texture0, textCoord - (direction * cAberation.blueOff)).ba;
    }
    
    if (effects.blur) {
        FragColor = texture(texture1, textCoord);
    }

    if (effects.bloom) {
        bloom();
    }
}