#version 330 core

out vec4 FragColor;
in vec2 textCoord;

uniform sampler2D screenTexture;
uniform float time;

void main()
{ 
    vec2 coord = textCoord;


    //split screen
    float halfSx = step(0.5,textCoord.x);
    float halfSy = step(0.5,textCoord.y);
    //In two on x
    //coord.x = halfSx > 0 ? coord.x-0.5 : coord.x;
    //In two on y
    //coord.y = halfSy > 0 ? coord.y-0.5 : coord.y;
    
    //"absorbtion" effect (requires split on x)
    //coord.x = smoothstep(0.001,0.5,coord.x);
    
    //wavy effect
    coord.x += sin(textCoord.y * 4*2*3.14159 + time) / 100;
    
    FragColor = texture(screenTexture,coord);
}