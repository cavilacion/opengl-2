#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the inputs to the fragment shader
// These must have the same type and name!
varying vec3 vertNormal;
varying vec3 lightVector;

// Specify the Uniforms of the fragment shaders
// uniform vec3 lightPosition; // for example
uniform vec4 lightPos;

// Specify the output of the fragment shader
// Usually a vec4 describing a color (Red, Green, Blue, Alpha/Transparency)
out vec4 fColor;

void main()
{
    // light properties
    vec4 diffuse = vec4(0.5,0.5,0.5,0.5);
    vec4 ambient = vec4(0.05,0.05,0.05,0.05);
    vec4 specular = vec4(0.01,0.01,0.01,0.01);

    // material properties
    float shininess = 0.1;

    vec3 L = normalize(vec3(lightPos) - lightVector);
    vec3 E = normalize(-lightVector); // we are in Eye Coordinates, so EyePos is (0,0,0)
    vec3 R = normalize(-reflect(L,vertNormal));

    //calculate Ambient Term:
    vec4 Iamb = ambient;

    //calculate Diffuse Term:
    vec4 Idiff = diffuse * max(dot(vertNormal,L), 0.0);
    Idiff = clamp(Idiff, 0.0, 1.0);

    // calculate Specular Term:
    vec4 Ispec = specular * pow(max(dot(R,E),0.0),0.3*shininess);
    Ispec = clamp(Ispec, 0.0, 1.0);

    // write Total Color:
    vec4 color = vec4(0.7,0.5,0.1,0.0);
    fColor = color + Iamb + Idiff + Ispec;

}
