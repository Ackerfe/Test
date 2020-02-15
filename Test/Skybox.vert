#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 Perspective;
uniform mat4 CameraMatrix;
uniform mat4 ModelMatrix;

out vec3 TexCoord0;
out vec3 VertexWorldPosition;
out vec3 VertexCameraNormal;
out vec4 viewSpace;

void main()
{
	vec4 pos = Perspective * CameraMatrix * vec4(vertexPosition, 1.0);

	gl_Position = pos.xyww;

	VertexWorldPosition = (ModelMatrix * vec4(vertexPosition, 1.0)).xyz;
	VertexCameraNormal = (CameraMatrix * ModelMatrix * vec4(vertexNormal, 0)).xyz;
	viewSpace = CameraMatrix * ModelMatrix * vec4(vertexPosition,1.0);
	TexCoord0 = vertexPosition;
}