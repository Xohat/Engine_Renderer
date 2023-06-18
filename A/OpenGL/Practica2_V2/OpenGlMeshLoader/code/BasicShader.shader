#vertex shader
#version 330\n

uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;

layout (location = 0) in vec3 vertex_coordinates;
layout (location = 1) in vec3 vertex_color;

out vec3 front_color;

void main()
{
   gl_Position = projection_matrix * model_view_matrix * vec4(vertex_coordinates, 1.0);
   front_color = vertex_color;
};


#fragment shader
#version 330\n

in  vec3    front_color;
out vec4 fragment_color;

void main()
{
    fragment_color = vec4(front_color, 1.0);
};