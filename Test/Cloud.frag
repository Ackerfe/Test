#version 330 core

in vec2 UV;
in vec3 VertexWorldPosition;
in vec3 VertexToCamera;
in vec3 VertexCameraNormal;

uniform sampler2D myTextureSampler;
uniform mat4 ModelCameraMatrix;
uniform float transparency;


out vec4 colour;

void main()
{
	vec3 MaterialDiffuseColour = texture(myTextureSampler, UV).rgb;

	vec3 vertexCameraNormal = normalize(VertexCameraNormal);

	colour = vec4(MaterialDiffuseColour, transparency);
}