#version 330 core

// Define constants
#define M_PI 3.141593
uniform sampler2D samplerUniform;

// Specify the inputs to the fragment shader
// These must have the same type and name!
in vec3 vertNormal;
in vec3 v_Color;
in vec2 vertUV;

// Specify the Uniforms of the fragment shaders
// uniform vec3 lightPosition; // for example

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;

void main()
{
    //fColor = vec4(normalize(vertNormal), 1.0)/2;
    vec4 textureColor = texture2D(samplerUniform, vertUV);
    fColor = vec4(v_Color, 1.0);
}
