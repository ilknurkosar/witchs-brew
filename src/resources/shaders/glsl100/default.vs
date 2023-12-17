#version 100

attribute vec3 vertexPosition;
attribute vec2 vertexTexCoord;
attribute vec4 vertexColor;

varying vec2 fragTexCoord;
varying vec4 fragColor;
varying highp vec4 fragLightCoord;

uniform mat4 mvp;
uniform mat4 ivp;
uniform mat4 lightMat;

void main()
{
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;
    gl_Position = mvp*vec4(vertexPosition, 1.0);
    fragLightCoord = lightMat*ivp*gl_Position;
}