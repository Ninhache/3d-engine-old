#version 330 core
out vec4 FragColor;

in vec2 textCoord;

uniform sampler2D screenTexture;
// uniform float exposure;

void main() {
    const float exposure = 1.5; 
    const float gamma = 2.2;
    vec3 hdrColor = texture(screenTexture, textCoord).rgb;

    // reinhard
    // vec3 result = hdrColor / (hdrColor + vec3(1.0));

    // exposure
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    // also gamma correct while we're at it       
    result = pow(result, vec3(1.0 / gamma));
    //FragColor = vec4(result, 1.0);
    FragColor = texture(screenTexture, textCoord);
}