#version 330 core
layout(location = 0) out vec4 out_color;
in vec2 UV;
in vec3 VertexWorldPosition;
in vec3 VertexToCamera;
in vec3 LightToCamera;
in vec3 VertexCameraNormal;
in vec4 viewSpace;

uniform sampler2D myTextureSampler;
uniform vec3 LightPosition;
uniform mat4 ModelCameraMatrix;
uniform vec3 LightColour;
uniform float LightIntensity;

uniform vec3 eye_position;

//can pass them as uniforms
const vec3 DiffuseLight = vec3(0.01, 0.01, 0.01);
const vec3 RimColor = vec3(0.3, 0.3, 0.5);
const vec3 fogColor = vec3(0.33333, 0.10588,0.19215);
const float FogDensity = 0.5;


void main()
{
	vec3 MaterialDiffuseColour = texture(myTextureSampler, UV).rgb;
	vec3 MaterialAmbientColour = vec3(0.5,0.5,0.5) * MaterialDiffuseColour;
	vec3 MaterialSpecularColour = vec3(0.3,0.3,0.3);

	float distance1 = length(eye_position - VertexWorldPosition);

	vec3 vertexCameraNormal = normalize(VertexCameraNormal);
	vec3 pixelToLight = normalize(LightToCamera);
	float cosTheta = clamp( dot(vertexCameraNormal,pixelToLight),0,1);

	vec3 pixelToCamera = normalize(VertexToCamera);
	vec3 reflectionDirection = reflect(-pixelToLight,vertexCameraNormal);
	float cosAlpha = clamp( dot(pixelToCamera,reflectionDirection), 0,1);

	vec3 L = normalize( LightPosition - VertexWorldPosition);
	vec3 V = normalize( LightPosition - VertexWorldPosition);

	//diffuse lighting
	vec3 diffuse = DiffuseLight * max(0, dot(L,VertexCameraNormal));
 
	//rim lighting
	float rim = 1 - max(dot(V, VertexCameraNormal), 0.0);
	rim = smoothstep(0.6, 1.0, rim);
	vec3 finalRim = RimColor * vec3(rim, rim, rim);
	//get all lights and texture
	vec3 lightColor = finalRim  + MaterialDiffuseColour;
 
	vec3 finalColor = vec3(0, 0, 0);
 
	//distance
	float dist = 0;
	float fogFactor = 0;
 

	//range based
	dist = length(viewSpace);

 
	// 20 - fog starts; 80 - fog ends
	fogFactor = log((dist * FogDensity))/8;
	fogFactor = clamp( fogFactor, 0.0, 1.0 );
 
	//if you inverse color in glsl mix function you have to
	 //put 1.0 - fogFactor
	 finalColor = mix(MaterialDiffuseColour, fogColor, fogFactor);
 
	//show fogFactor depth(gray levels)
	//fogFactor = 1 - fogFactor;
	//out_color = vec4( fogFactor, fogFactor, fogFactor,1.0 );
	out_color = vec4(finalColor, 1);
	
	//colour = vec4(MaterialAmbientColour +
	//MaterialDiffuseColour * LightColour * LightIntensity * cosTheta / (distance*distance) +
	//MaterialSpecularColour * LightColour * LightIntensity * pow(cosAlpha,5) /  (distance*distance), 1);
}