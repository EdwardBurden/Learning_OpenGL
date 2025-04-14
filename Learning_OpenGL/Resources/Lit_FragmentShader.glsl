#version 330 core

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Material {
 sampler2D texture_diffuse1;
 sampler2D texture_diffuse2;
 sampler2D texture_diffuse3;
 sampler2D texture_specular1;
 sampler2D texture_specular2;
    float shininessAmount;
};

#define NR_POINT_LIGHTS 4  

vec3 CalculateSpotLight(SpotLight light, Material material, vec3 sampledDiffuseColor, vec3 sampledSpecularColor, vec3 normal, vec3 worldPos, vec3 viewDir) {
    float distance = length(light.position - worldPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    vec3 result = vec3(0);
    vec3 ambient = sampledDiffuseColor * light.ambient;
    vec3 lightDir = normalize(light.position - worldPos);
    float theta = dot(lightDir, normalize(-light.direction));
    if (theta > light.outerCutOff) {
        float epsilon = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

        vec3 lightDir = normalize(light.position - worldPos);
        float normLightDot = dot(normal, lightDir);
        float diffAmount = max(normLightDot, 0.0);
        vec3 diffuse = (diffAmount * sampledDiffuseColor) * light.diffuse;

        // Specular
        vec3 specular = vec3(0.0);
        if (normLightDot >= 0.0) {
            vec3 reflectDir = reflect(-lightDir, normal);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininessAmount);
            specular = (spec * sampledSpecularColor) * light.specular;
        }
        return ambient + ((diffuse + specular) * intensity * attenuation);

    } else  // else, use ambient light so scene isn't completely dark outside the spotlight.
        result = sampledDiffuseColor * light.ambient;
    return result;
}

vec3 CalculatePointLight(PointLight light, Material material, vec3 sampledDiffuseColor, vec3 sampledSpecularColor, vec3 normal, vec3 worldPos, vec3 viewDir) {
    float distance = length(light.position - worldPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));



    // Ambient
    vec3 ambient = sampledDiffuseColor * light.ambient;

    // Diffuse
    vec3 lightDir = normalize(light.position - worldPos);
    float normLightDot = dot(normal, lightDir);
    float diffAmount = max(normLightDot, 0.0);
    vec3 diffuse = (diffAmount * sampledDiffuseColor) * light.diffuse;

    // Specular
    vec3 specular = vec3(0.0);
    if (normLightDot >= 0.0) {
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininessAmount);
        specular = (spec * sampledSpecularColor) * light.specular;
    }
    return vec3(ambient + diffuse + specular) * attenuation;
}

vec3 CalculateDirectionalLight(DirectionalLight light, Material material, vec3 sampledDiffuseColor, vec3 sampledSpecularColor, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    // Ambient
    vec3 ambient = sampledDiffuseColor * light.ambient;

    // Diffuse
    float normLightDot = dot(normal, lightDir);
    float diffAmount = max(normLightDot, 0.0);
    vec3 diffuse = (diffAmount * sampledDiffuseColor) * light.diffuse;

    // Specular
    vec3 specular = vec3(0.0);
    if (normLightDot >= 0.0) {
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininessAmount);
        specular = (spec * sampledSpecularColor) * light.specular;
    }
    return ambient + diffuse + specular;
}

in vec2 TexCoords;
in vec3 Normal;
in vec3 WorldPos;

uniform SpotLight spotLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirectionalLight directionLight;
uniform Material material;
uniform vec3 lightColor;
uniform vec3 viewPos;

out vec4 FragColor;

void main() {
//FragColor = vec4(TexCoords , 0 , 1);
    vec3 sampledDiffuse = vec3(texture(material.texture_diffuse1, TexCoords));
     FragColor = vec4(sampledDiffuse, 1);
 /* vec3 lightDir = normalize(-directionLight.direction);
   float normLightDot = dot(Normal, lightDir);
    float diffAmount = max(normLightDot, 0.0);
    vec3 diffuse = diffAmount * directionLight.diffuse;
     FragColor = vec4(Normal,1);
     *
     vec3 sampledDiffuse = vec3(texture(material.texture_diffuse1, TexCoords));
     FragColor = vec4(sampledDiffuse, 1);
  /*  vec3 sampledDiffuse = vec3(texture(material.texture_diffuse1, TexCoords));
    vec3 sampledSpecular = vec3(texture(material.texture_specular1, TexCoords));
    vec3 viewDir = normalize(viewPos - WorldPos);
    vec3 norm = normalize(Normal);
 vec3 result = vec3(0.0);
      result = CalculateDirectionalLight(directionLight, material, sampledDiffuse, sampledSpecular, norm, viewDir);

      for(int i = 0; i < NR_POINT_LIGHTS; i++){
  	result += max( CalculatePointLight(pointLights[i], material, sampledDiffuse, sampledSpecular, norm,WorldPos, viewDir) , vec3(0));
}
    result += CalculateSpotLight(spotLight, material, sampledDiffuse, sampledSpecular, norm, WorldPos, viewDir);
    FragColor = vec4(result, 1);*/
    // FragColor = vec4(1);
}