
#version 330
 
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUV;
 
uniform mat4 ModelMatrix, CameraMatrix, Perspective;
 
out vec3 VertexWorldPosition;
out vec3 VertexCameraNormal;
out vec2 texcoord;
out vec4 viewSpace;
 
void main(){
 
//used for lighting models
VertexWorldPosition = (ModelMatrix * vec4(vertexPosition,1)).xyz;
VertexCameraNormal = normalize(mat3(ModelMatrix) * vertexNormal);
texcoord = vertexUV;
 
//send it to fragment shader
viewSpace = CameraMatrix * ModelMatrix * vec4(vertexPosition,1);
gl_Position = Perspective * viewSpace;
 
}