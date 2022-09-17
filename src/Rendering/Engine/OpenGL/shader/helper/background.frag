#version 440

in vec2 texCoord;

uniform vec3 uColor0;
uniform vec3 uColor1;

out vec3 FragColor;

void main(void) 
{
    FragColor = mix(uColor0, uColor1, texCoord.y);
}

