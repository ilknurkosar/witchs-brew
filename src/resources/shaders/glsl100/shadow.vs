#version 100
precision mediump float;

// Input vertex attributes
attribute vec3 vertexPosition;

// Input uniform values
uniform mat4 mvp;

varying vec3 fragPosition;

void main()
{
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}