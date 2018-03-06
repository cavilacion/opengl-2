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

// Specify the output of the vertex stage
varying vec3 vertNormal;
varying vec3 lightVector;

void main()
{
    // gl_Position is the output (a vec4) of the vertex shader
    // Currently without any transformation
    gl_Position = projectionTransform * modelTransform * transformation * vec4(vertCoordinates_in, 1.0);
    vertNormal = normalTransform*vertNormal_in;

    lightVector = vec3(normalize(lightPos - gl_Position));

    //v = vec3(gl_ModelViewMatrix * gl_Vertex);
    //N = normalize(gl_NormalMatrix * gl_Normal);
}



