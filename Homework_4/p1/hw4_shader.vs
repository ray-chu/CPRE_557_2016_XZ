#version 410 core                                                 
                                                                  
uniform mat4 projectionMatrix;                                    
uniform mat4 viewMatrix;                                          
uniform mat4 modelMatrix;

in vec3 in_Position;
                                                                  
in vec2 in_tex_coord;
in vec3 in_Color;

out vec2 vs_tex_coord;
out vec3 pass_Color;
                                                                  
void main(void)                                                   
{                                                                 
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);  
    vs_tex_coord = in_tex_coord;
    pass_Color = in_Color;
}                                                                 