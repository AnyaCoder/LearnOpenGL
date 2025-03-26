#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 Color;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform bool useTexture;
uniform bool useLighting;
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
    vec3 result;
    
    if (useLighting) {
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
        
        result = (ambient + diffuse + specular) * Color;
    } else {
        result = Color;
    }
    
    if (useTexture) {
        FragColor = texture(ourTexture, TexCoord) * vec4(result, 1.0);
    } else {
        FragColor = vec4(result * overrideColor, 1.0);
    }
}
