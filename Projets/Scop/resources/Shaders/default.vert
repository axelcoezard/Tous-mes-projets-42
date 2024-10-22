#version 110

attribute vec3 vPosition;
attribute vec2 vTexture;
attribute vec3 vNormal;

varying vec3 fPosition;
varying vec2 fTexture;
varying vec3 fNormal;
varying vec3 lightDirection;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPosition;

void main() {
	vec4 worldPosition = view * model * vec4(vPosition, 1.0);
	gl_Position = projection * worldPosition;

	fPosition = vec3(worldPosition);
	fTexture = vTexture;
	fNormal = vec3(view * model * vec4(vNormal, 0.0));
	lightDirection = vec3(view * vec4(lightPosition, 1.0)) - vec3(worldPosition);
}
