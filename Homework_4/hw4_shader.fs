#version 410 core                                                 

uniform sampler2D tex;
in vec3 pass_Color;
in vec2 vs_tex_coord;                                               
out vec4 color;                                                   
void main(void)                                                   
{                                                                 
    color = texture(tex, vs_tex_coord)+vec4(pass_Color, 1.0);                               
} 