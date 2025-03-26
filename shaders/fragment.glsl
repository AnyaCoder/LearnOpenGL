#version 330 core
out vec4 FragColor;

in vec3 Color;
in vec2 TexCoord;
uniform sampler2D ourTexture;
uniform bool useTexture;
uniform vec3 overrideColor;

void main()
{
    if (useTexture) {
        FragColor = texture(ourTexture, TexCoord) * vec4(Color, 1.0);
    } else {
        FragColor = vec4(overrideColor * Color, 1.0);
    }
}
