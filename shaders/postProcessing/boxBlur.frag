#version 330 core

out vec4 FragColor;
in vec2 textCoord;

int boxSize = 3;
uniform sampler2D texture0;

void main() {
	
	for(int i = -boxSize; i <= boxSize; i++){
		for(int j=-boxSize; j <= boxSize; j++){
			FragColor+=texture(texture0, textCoord.xy + vec2(i,j) / textureSize(texture0,0));
		}
	}
	FragColor /= pow(boxSize*2+1,2);
}