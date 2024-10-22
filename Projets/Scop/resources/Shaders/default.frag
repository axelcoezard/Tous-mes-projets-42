#version 110

varying vec3 fPosition;
varying vec2 fTexture;
varying vec3 fNormal;
varying vec3 lightDirection;

uniform sampler2D Texture0;
uniform vec3 lightColor;
uniform float textureOpacity;

void main() {

	// ambient light
	float ambient  = 0.5;

	// diffuse light
	vec3 unitNormal = normalize(fNormal);
	vec3 unitLightDirection = normalize(lightDirection);
	float diffuse = 0.1 * max(dot(unitNormal, unitLightDirection), 0.0);

	// specular light
	vec3 viewDirection = normalize(-fPosition);
	vec3 reflectDirection = reflect(-lightDirection, unitNormal);
	float specular = 0.05 * max(dot(viewDirection, reflectDirection), 0.0);

	float brightness = max(ambient + diffuse + specular, 1.0);

	if (textureOpacity > 0.0) {
		gl_FragColor = vec4(brightness * lightColor, 1.0) * texture2D(Texture0, fTexture);
	} else {
		gl_FragColor = vec4(brightness * lightColor, 1.0) * vec4(0.45, 0.45, 0.45, 1.0);
	}
}
