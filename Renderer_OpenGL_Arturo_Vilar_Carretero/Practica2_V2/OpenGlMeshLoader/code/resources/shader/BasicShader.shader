#shader vertex
#version 330 core

uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;
uniform sampler2D displacement_texture;
uniform bool is_displacement = false;
uniform float displacement_up = 3;

layout (location = 0) in vec3 vertex_coordinates;
layout (location = 1) in vec2 tex_coord;

out vec2 v_TexCoord;

void main()
{
   v_TexCoord = tex_coord;

   vec4 deformed_position = vec4(vertex_coordinates.x, vertex_coordinates.y + texture(displacement_texture, v_TexCoord).x * displacement_up, vertex_coordinates.z, 1);

   if (is_displacement)  
   {
	   gl_Position = projection_matrix * model_view_matrix * vec4(deformed_position.xyz, 1.0);
   }

   else 
   {
	   gl_Position = projection_matrix * model_view_matrix * vec4(vertex_coordinates, 1.0);
   }
};


#shader fragment
#version 330 core

out vec4 fragment_color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
    fragment_color = texColor;
};