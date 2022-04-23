#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in mat4 instanceModel;

out vec4 vertColor;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * instanceModel * vec4(aPosition, 1.0f);
	vertColor = aColor;
}