#SHADER VERTEX

#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 transform;

void main() {

	gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	TexCoord = aTexCoord;

}

#SHADER FRAGMENT

#version 330 core

in vec2 TexCoord;
out vec4 fragColour;

uniform sampler2D ourTexture;
uniform vec4 ourColour;

void main() {

	fragColour = ourColour * texture(ourTexture, vec2(TexCoord.x, TexCoord.y));

}