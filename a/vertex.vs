#version 330

attribute vec3 vertexPosition;
attribute vec2 vertexTexCoord;            
attribute vec4 vertexColor;

uniform mat4 mvp;        

out vec2 fragTexCoord;             
out vec4 fragColor;       

uniform float time;

void main()                        
{             
    fragTexCoord = vertexTexCoord; 
    fragColor = vertexColor;
    vec4 pos = vec4(vertexPosition, 1.0);
    pos.y += sin(pos.x / (10.0f * time));
    gl_Position = mvp * pos; 
}