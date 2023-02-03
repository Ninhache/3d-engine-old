#version 460 core
out vec4 FragColor;

in vec2 textCoord;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D diffuseMap0;
uniform sampler2D diffuseMap1;
uniform sampler2D specularMap0;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {

    float ambiantStrength = 0.1;
    float specularStength = 0.5;
    
    vec3 normalN = normalize(normal);
    //vector which points from the fragment position to the light source
    vec3 lightDirection = normalize(lightPos - fragPos);
    
    //calculate the diffuse impact on a fragment, the greater the angle between the normal and the lightDirection
    //the darker the it will get
    float lightIntensity = max(dot(normalN, lightDirection),0.0);
    
    //reflect function expects the first vector to point from the light source toward the fragPos
    //but ours points towards the light source from fragPos (because we did lightPos - fragPos and not the other way around
    //so we negate it
    vec3 reflectDirection = reflect(-lightDirection, normalN);
    vec3 viewDirection = normalize(viewPos - fragPos);
    float specAmount = pow(max(dot(viewDirection,reflectDirection),0.0),32);

    vec3 ambiant = ambiantStrength * vec3(texture(diffuseMap0,textCoord));
    vec3 specular = specularStength * specAmount * lightColor * vec3(texture(specularMap0, textCoord));
    vec3 diffuse = lightIntensity * lightColor * vec3(texture(diffuseMap0,textCoord));

    //ambiant and diffuse lightning
    vec3 lightning = (ambiant + diffuse + specular);
    
    FragColor = vec4(lightning,1.0);
}