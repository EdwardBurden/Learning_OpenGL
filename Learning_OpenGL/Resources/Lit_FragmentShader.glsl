#version 330 core

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    sampler2D diffuseMap;
    sampler2D specularMap;
    float shininessAmount;
};


vec3 CalculateDirectionalLight(DirectionalLight light, Material material, vec3 sampledDiffuseColor,  vec3 sampledSpecularColor, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    //Ambient
    vec3 ambient = sampledDiffuseColor * light.ambient;

    //Diffuse
    float normLightDot = dot(normal, lightDir);
    float diffAmount = max(normLightDot, 0.0);
    vec3 diffuse = (diffAmount * sampledDiffuseColor) * light.diffuse;

    //Specular
    vec3 specular = vec3(0.0);
    if(normLightDot >= 0.0)
    {
        vec3 reflectDir = reflect(-lightDir, normal); 
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininessAmount);
        specular =  (spec * sampledSpecularColor) * light.specular;  
    }
    return ambient + diffuse + specular;
}




in vec2 TexCoords;
in vec3 Normal;
in vec3 WorldPos;  

uniform DirectionalLight directionLight;
uniform Material material;
uniform vec3 lightColor; 
uniform vec3 viewPos;

out vec4 FragColor;

void main()
{
    vec3 sampledDiffuse = vec3(texture(material.diffuseMap, TexCoords));
     vec3 sampledSpecular = vec3(texture(material.specularMap, TexCoords));
       vec3 viewDir = normalize(viewPos - WorldPos);
         vec3 norm = normalize(Normal);

      vec3 outcolor =    CalculateDirectionalLight(directionLight, material, sampledDiffuse, sampledSpecular,  norm ,viewDir  );
       FragColor = vec4(outcolor, 1.0);
}