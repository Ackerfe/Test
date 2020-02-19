#version 330 core
layout(location = 0) out vec4 out_color;

in vec3 TexCoord0;
in vec3 VertexCameraNormal;
in vec4 viewSpace;
in vec3 VertexWorldPosition;

uniform samplerCube cubemapTexture;
uniform vec3 LightPosition;
uniform mat4 ModelCameraMatrix;



const vec3 DiffuseLight = vec3(0.01, 0.01, 0.01);
const vec3 RimColor = vec3(0.3, 0.3, 0.5);

const float FogDensity = 0.005;


void main()
{
	vec4 colour = texture(cubemapTexture, TexCoord0);
	vec4 fogColor = vec4(0.67451, 0.25098,0.74118, 1.0);
	vec3 L = normalize( LightPosition - VertexWorldPosition);
	vec3 V = normalize( LightPosition - VertexWorldPosition);
 
	//diffuse lighting
	vec3 diffuse = DiffuseLight * max(0, dot(L,VertexCameraNormal));
 
	//rim lighting
	float rim = 1 - max(dot(V, VertexCameraNormal), 0.0);
	rim = smoothstep(0.6, 1.0, rim);
	vec3 finalRim = RimColor * vec3(rim, rim, rim);
	//get all lights and texture
	vec3 lightColor = finalRim  + vec3(colour);
 
	vec4 finalColor = vec4(0, 0, 0, 0);
 
	//distance
	float dist = 0;
	float fogFactor = 0;
 

	//range based
	dist = length(viewSpace);

 
	// 20 - fog starts; 80 - fog ends
	fogFactor = (800 - dist)/(800 - 2000);
	fogFactor = clamp( fogFactor, 0.0, 1.0 );
 
	//if you inverse color in glsl mix function you have to
	 //put 1.0 - fogFactor
	 finalColor = mix(colour, fogColor, vec4(fogFactor));
 
	//show fogFactor depth(gray levels)
	//fogFactor = 1 - fogFactor;
	//out_color = vec4( fogFactor, fogFactor, fogFactor,1.0 );
	out_color = vec4(finalColor);
}