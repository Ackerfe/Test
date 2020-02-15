
#version 330
layout(location = 0) out vec4 out_color;
 
uniform vec3 light_position;
uniform vec3 eye_position;
 
uniform sampler2D texture1;
 
//0 linear; 1 exponential; 2 exponential square
uniform int fogSelector;
//0 plane based; 1 range based

 
//can pass them as uniforms
const vec3 DiffuseLight = vec3(0.15, 0.05, 0.0);
const vec3 RimColor = vec3(0.2, 0.2, 0.2);
 
//from vertex shader
in vec3 VertexWorldPosition;
in vec3 VertexCameraNormal;
in vec4 viewSpace;
in vec2 texcoord;
 
const vec3 fogColor = vec3(0.5, 0.5,0.6);
const float FogDensity = 0.05;
 
void main(){
 
vec3 tex1 = texture(texture1, texcoord).rgb;
 
//get light an view directions
vec3 L = normalize( light_position - VertexWorldPosition);
vec3 V = normalize( eye_position - VertexWorldPosition);
 
//diffuse lighting
vec3 diffuse = DiffuseLight * max(0, dot(L,VertexCameraNormal));
 
//rim lighting
float rim = 1 - max(dot(V, VertexCameraNormal), 0.0);
rim = smoothstep(0.6, 1.0, rim);
vec3 finalRim = RimColor * vec3(rim, rim, rim);
//get all lights and texture
vec3 lightColor = finalRim + diffuse + tex1;
 
vec3 finalColor = vec3(0, 0, 0);
 
//distance
float dist = 0;
float fogFactor = 0;
 

//range based
dist = length(viewSpace);

 
 // 20 - fog starts; 80 - fog ends
 fogFactor = (80 - dist)/(80 - 20);
 fogFactor = clamp( fogFactor, 0.0, 1.0 );
 
 //if you inverse color in glsl mix function you have to
 //put 1.0 - fogFactor
 finalColor = mix(fogColor, lightColor, 1.0-fogFactor);
 
//show fogFactor depth(gray levels)
//fogFactor = 1 - fogFactor;
//out_color = vec4( fogFactor, fogFactor, fogFactor,1.0 );
out_color = vec4(finalColor, 1);
 
}