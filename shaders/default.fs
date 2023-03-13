#version 460 core
out vec4 FragColor;

in vec2 textCoord;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D diffuseMap0;
uniform sampler2D diffuseMap1;
uniform sampler2D specularMap0;

struct PointLight{
    vec3 lightColor, lightPos;
    float constant, linear, quadratic;
    float ambiantStr, specularStr;
    bool active;
};

struct DirLight{
    vec3 lightDir, lightColor;
    float ambiantStr;
    float specularStr;
    bool activated;
};

#define MAX_LIGHTS 4
uniform PointLight pLights[MAX_LIGHTS];
uniform DirLight dLight[MAX_LIGHTS];
uniform bool hasDiffuse;

uniform vec3 viewPos;
vec3 pointLight(PointLight plight, vec3 normalN);
vec3 directionalLight(DirLight light, vec3 normalN);

void main() {
    
    vec3 normalN = normalize(normal);
    vec3 lightOutput = vec3(0.0);

    for(int i = 0; i < MAX_LIGHTS; i++){
        if(pLights[i].active == true){
            lightOutput += pointLight(pLights[i], normalN);
        }
        lightOutput += directionalLight(dLight[i], normalN);
    }
    
    FragColor = vec4(lightOutput,1.0);
}

vec3 pointLight(PointLight pLight, vec3 normalN){
    
    vec3 diffuseTexture;
    if(hasDiffuse){
        diffuseTexture = vec3(texture(diffuseMap0,textCoord));
    }
    else{
        diffuseTexture = vec3(1.0);
    }
    //vector which points from the fragment position to the light source
    vec3 lightDirection = normalize(pLight.lightPos - fragPos);
    
    //calculate the diffuse impact on a fragment, the greater the angle between the normal and the lightDirection
    //the darker the it will get    
    float diffuseShading = max(dot(normalN, lightDirection),0.0);
    
    /* Specular */
    /*reflect function expects the first vector to point from the light source toward the fragPos
     but ours points towards the light source from fragPos (because we did lightPos - fragPos and not the other way around
     so we negate it*/
    vec3 reflectDirection = reflect(-lightDirection, normalN);
    vec3 viewDirection = normalize(viewPos - fragPos);
    float specAmount = pow(max(dot(viewDirection,reflectDirection),0.0),32);
    /* --------- */
    
    float distance = length(pLight.lightPos - fragPos);
    float attenuation = 1.0 / (pLight.constant + pLight.linear * distance + pLight.quadratic * (distance * distance));

    vec3 ambiant = pLight.ambiantStr * diffuseTexture * attenuation;
    vec3 specular = pLight.specularStr * specAmount * pLight.lightColor * vec3(texture(specularMap0, textCoord)) * attenuation;
    vec3 diffuse = diffuseShading * pLight.lightColor * diffuseTexture * attenuation;
    
    //ambiant and diffuse lightning
    return (ambiant + diffuse + specular);
}

vec3 directionalLight(DirLight light, vec3 normalN){

    vec3 diffuseTexture;
    if(hasDiffuse){
        diffuseTexture = vec3(texture(diffuseMap0,textCoord));
    }
    else{
        diffuseTexture = vec3(1.0,1.0,1.0);
    }

    vec3 lightDir = normalize(-light.lightDir);
    float diffuseShading = max(dot(normalN,lightDir),0.0);


    vec3 viewDirection = normalize(viewPos - fragPos);
    vec3 reflectDirection = reflect(-lightDir,normalN);
    float specAmount = pow(max(dot(viewDirection,reflectDirection),0.0),32);
    
    vec3 specular = light.specularStr * specAmount * vec3(texture(specularMap0,textCoord));
    vec3 diffuse = diffuseShading * light.lightColor * diffuseTexture;
    vec3 ambiant = light.ambiantStr * diffuseTexture;

    return (ambiant + diffuse + specular);
}