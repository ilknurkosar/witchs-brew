#version 100
precision mediump float;     // Precision required for OpenGL ES2 (WebGL)

varying vec2 fragTexCoord;
varying vec4 fragColor;
varying highp vec4 fragLightCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform vec4 colDiffuse;

const vec3 ambient = vec3(0.15);

float ShadowCalc(vec4 p, float bias)
{
    highp vec3 projCoords = p.xyz / p.w;
    projCoords = projCoords * 0.5 + 0.5;
    projCoords.z = projCoords.z - bias;
	highp float depth = projCoords.z;

	float texDepth = texture2D(texture1, projCoords.xy).r;
	float shadow = step(depth, texDepth);

	if(projCoords.z > 1.0 || projCoords.x > 1.0 || projCoords.y > 1.0)
        shadow = 1.0;

    return shadow;
}

void main()
{
    vec4 texelColor = texture2D(texture0, fragTexCoord);
    vec4 color = texelColor*colDiffuse*fragColor;
   float shadow = ShadowCalc(fragLightCoord,0.005);
   gl_FragColor = vec4(color.rgb*(vec3(shadow) + ambient), 1.0);
//    gl_FragColor = vec4(vec3(0.5 - fragLightCoord.z), 1.0);
}