
#version 330 core

struct DirectionalLight
{
	vec3 direction;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
};

struct PointLight
{
	vec3 position;
    float constant;
	float linear;
	float quadratic;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float cutOff;
    float outerCutOff;
    float constant;
	float linear;
	float quadratic;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
};


uniform float shininess;

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec3 FragPos;  

uniform sampler2D texture1;
uniform vec3 viewPos;

#define NB_DIRECTIONAL_LIGHTS 5 
uniform DirectionalLight directionalLights[NB_DIRECTIONAL_LIGHTS];
uniform int nbDirLight;

#define NB_POINT_LIGHTS 5  
uniform PointLight pointLights[NB_POINT_LIGHTS];
uniform int nbPointLight;

#define NB_SPOT_LIGHTS 5 
uniform SpotLight spotLights[NB_SPOT_LIGHTS];
uniform int nbSpotLight;


vec3 CalcDirLight(DirectionalLight light, vec3 ourColor, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(ourColor, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, ourColor);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 ambient  = light.ambientColor  * vec3(texture(texture1, TexCoord));
    vec3 diffuse  = light.diffuseColor  * diff * vec3(texture(texture1, TexCoord));
    vec3 specular = light.specularColor * spec * vec3(texture(texture1, TexCoord));
    return (ambient + diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
    light.quadratic * (distance * distance));    
    vec3 ambient  = light.ambientColor  * vec3(texture(texture1, TexCoord));
    vec3 diffuse  = light.diffuseColor  * diff * vec3(texture(texture1, TexCoord));
    vec3 specular = light.specularColor * spec * vec3(texture(texture1, TexCoord));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
     vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    vec3 ambient = light.ambientColor * vec3(texture(texture1, TexCoord));
    vec3 diffuse = light.diffuseColor * diff * vec3(texture(texture1, TexCoord));
    vec3 specular = light.specularColor * spec * vec3(texture(texture1, TexCoord));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
} 

void main()
{
    vec3 norm = normalize(ourColor);
    vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result ;
    for(int i = 0; i < nbDirLight; i++)
       result += CalcDirLight(directionalLights[i], norm, viewDir);
	for(int i = 0; i < nbPointLight; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
	for(int i = 0; i < nbSpotLight; i++)
       result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
};
