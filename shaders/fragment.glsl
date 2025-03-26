#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 Color;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform bool useTexture;
uniform vec3 overrideColor;

// Material properties
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

// Light properties
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
    // Ambient
    vec3 ambient = light.ambient * material.ambient;
    
    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // Specular - Phong
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);
    
    // Blinn-Phong
    // vec3 halfwayDir = normalize(lightDir + viewDir);  
    // float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    // vec3 specular = light.specular * (spec * material.specular);
    
    vec3 result = (ambient + diffuse + specular);
    
    if (useTexture) {
        FragColor = texture(ourTexture, TexCoord) * vec4(result * Color, 1.0);
    } else {
        FragColor = vec4(result * overrideColor * Color, 1.0);
    }
}
