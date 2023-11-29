#version 330 core
out vec4 FragColor;
uniform vec3 objColor;
void main()
{
	FragColor = vec4(objColor.xyz, 1.0);
}
