#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertNormal_in;

// Specify the Uniforms of the vertex shader
uniform mat4 modelTransform; //for example
uniform mat4 projectionTransform;
uniform mat4 transformation;
uniform mat3 normalTransform;

uniform vec4 lightPos;
//uniform vec3 color;

// Specify the output of the vertex stage
out vec3 vertNormal;
varying vec3 v_Color;

void main()
{
    // gl_Position is the output (a vec4) of the vertex shader
    // Currently without any transformation
    gl_Position = projectionTransform * modelTransform * transformation * vec4(vertCoordinates_in, 1.0);
    vertNormal = normalTransform*vertNormal_in;


    // http://www.learnopengles.com/tag/gouraud-shading/


    vec4 lightPosition = projectionTransform * modelTransform * transformation * lightPos;
    float distance = length(lightPosition - gl_Position);
    vec4 lightVector = normalize(lightPosition - gl_Position);

    // Calculate the dot product of the light vector and vertex normal. If the normal and light vector are
    // pointing in the same direction then it will get max illumination.
    float diffuse = max(dot(vertNormal, vec3(lightVector)), 0.1);

    // Attenuate the light based on distance.
    //diffuse = diffuse * (1.0 / (1.0 + (0.25 * distance * distance)));

    // Multiply the color by the illumination level. It will be interpolated across the triangle.
    vec3 color = vec3(0.7,0.5,0.1);
    v_Color = color * diffuse;

}
