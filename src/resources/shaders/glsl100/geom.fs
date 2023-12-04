#version 100
precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec3 fragPosition;
varying vec2 fragTexCoord;
varying vec3 fragNormal;
varying vec4 shadowPos;

// Input uniform values
uniform sampler2D texture0; //albedo
uniform sampler2D texture1; //shadowmap
uniform vec4 colDiffuse; //tint
uniform vec3 lightPos;
uniform vec3 lightDir;
uniform float lightCutoff;
uniform vec3 viewPos;

// Also shouldn't be hardcoded
const float lightRadius = 4.0;
const vec3 ambient = vec3(0.25);
const float spotSoftness = 0.65;

float ShadowCalc(vec4 p, float bias)
{
    vec3 projCoords = p.xyz / p.w;
    projCoords = projCoords * 0.5 + 0.5;
    projCoords.z = projCoords.z - bias;
	float depth = projCoords.z;

	float texDepth = texture2D(texture1, projCoords.xy).r;
	float shadow = step(depth, texDepth);

	if(projCoords.z > 1.0 || projCoords.x > 1.0 || projCoords.y > 1.0)
        shadow = 1.0;

    return shadow;
}

void main()
{
    vec4 texelColor = texture2D(texture0, fragTexCoord)*colDiffuse;
	vec3 lightRaw = lightPos - fragPosition;
	vec3 lightVec = normalize(lightRaw);
	float lightDistSqr = dot(lightRaw, lightRaw);
	vec3 viewVec = normalize(viewPos - fragPosition);
	vec3 h = normalize(lightVec + viewVec);

	float attenuation = float(clamp(1.0 - lightDistSqr/(lightRadius*lightRadius), 0.0, 1.0));
    attenuation *= attenuation;

	float NdL = max(0.0, dot(lightVec, fragNormal));
	float NdH = max(0.0, dot(h, fragNormal));
	float theta = dot(-lightVec, normalize(lightDir));
	float epsilon = lightCutoff - spotSoftness;
	float spot = clamp((theta - lightCutoff) / epsilon, 0.0, 1.0);

	float diff = NdL * attenuation;

	float bias = max(0.001 * (1.0 - NdL), 0.0001);
   	diff *= ShadowCalc(shadowPos, bias) * spot;

	float spec = pow(NdH, 64.0) * diff;

//	gl_FragColor = vec4( vec3((texelColor.rgb * diff + spec) + texelColor.rgb * ambient),1.0);
	gl_FragColor = vec4( texelColor.rgb,1.0);
}