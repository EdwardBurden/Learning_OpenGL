#version 330 core

struct Material {
    sampler2D diffuseMap;
    sampler2D specularMap;
    float shininessAmount;
};

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}; 

in vec2 TexCoords;
in vec3 Normal;
in vec3 WorldPos;  

uniform Light light;  
uniform Material material;
uniform vec3 lightColor; 
uniform vec3 viewPos;

out vec4 FragColor;

void main()
{

    vec3 sampledDiffuse = vec3(texture(material.diffuseMap, TexCoords));
     vec3 sampledSpecular = vec3(texture(material.specularMap, TexCoords));

    //Ambient
    vec3 ambient = sampledDiffuse * light.ambient;

    //Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - WorldPos); 
    float normLightDot = dot(norm, lightDir);
    float diffAmount = max(normLightDot, 0.0);
    vec3 diffuse = (diffAmount * sampledDiffuse) * light.diffuse;

    //Specular
    vec3 specular = vec3(0.0);
    if(normLightDot >= 0.0)
    {
        vec3 viewDir = normalize(viewPos - WorldPos);
        vec3 reflectDir = reflect(-lightDir, norm); 
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininessAmount);
        specular =  (spec * sampledSpecular) * light.specular;  
    }
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}