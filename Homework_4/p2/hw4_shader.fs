#version 410 core                                                 

uniform sampler2D tex_gradient;
uniform sampler2D tex_landscape;
uniform sampler2D tex_animal;
in vec3 pass_Color;
in vec2 vs_tex_coord;                                               
out vec4 color;                                                   
void main(void)                                                   
{
	vec4 landscape_color=texture(tex_landscape, vs_tex_coord);
	vec4 animal_color;
	float eps=0.15f;
	vec3 black=vec3(0.0f,0.0f,0.0f);
	if(all(greaterThanEqual(landscape_color.rgb,black-eps))&&all(lessThanEqual(landscape_color.rgb,black+eps)))
	//if(all(greaterThanEqual(landscape_color.rgb,black-eps)))
		animal_color=vec4(0.0f,0.0f,0.0f,1.0f);
	else animal_color=0.4*texture(tex_animal, vs_tex_coord+vec2(0.1,0));
	color = animal_color+mix(texture(tex_gradient, vs_tex_coord),landscape_color,0.6);
	//color=animal_color;
} 