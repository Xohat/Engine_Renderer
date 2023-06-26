Recorte

        for (int * indices = original_indices.data (), * end = indices + original_indices.size (); indices < end; indices += 3)
        {
            if (is_frontface (transformed_vertices.data (), indices))
            {
                // Se establece el color del polígono a partir del color de su primer vértice:

                rasterizer.set_color (original_colors[*indices]);

				// Intento recorte
				
				int clipped_indices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
				vec4 clipped_vertices[10];
				
				int n = clip_polygon(display_vertices.data (), indices, indices + 3, clipped_vertices)	;

				if(n >= 3)
				{
					// Se rellena el polígono:
					rasterizer.fill_convex_polygon_z_buffer 
					(
						clipped_vertices,
						clipped_indices,
						clipped_indices + n					
					);
				}			
            }
        }
		
	//Tema clip_polygon
	
	using Color = vec3
	
	int clip_polygon(const vec4 * vertices, const int * first_index, 
				     const int * last_index, vec4 * clipped_polygon)
	{
		int number_of_vertices;
		
		number_of_vertices = clip_polygon_with_line(?);
		number_of_vertices = clip_polygon_with_line(?);
		number_of_vertices = clip_polygon_with_line(?);
		number_of_vertices = clip_polygon_with_line(?);
		
		return number_of_vertices;
	}
	
	int clip_polygon_with_line(const vec4 * vertices, const int * first_index, 
							   const int * last_index, float a, float b, float c, 
							   vec4 * clipped_polygon)
	{
		for (int * index = first_index; index < last_index; ++index)
		{
			//[*index] = [index[0]]
			vec4 & vertex0 = vertices[index[0]];
			vec4 & vertex1 = vertices[index < last_index - 1 ? index[1] : first_index];
			
			//Comprobar en que lado de la línea
		}
	}
	
	inline int point_line_side (float a, float b, float c, const vec4 & point0)
	{
		return (a * point.x + b * point.y + c) < 0 ? -1 : +1;
	}
	
	//Punto de interseccion entre dos líneas	
	Intersection mesh::line_line_intersection(float a, float b, float c,
								              const vec4 & point0, const vec4 point1,
							                  const Color & color0, const Color & color1)
	{
		// Dada ecuación general de una recta y paramétrica 
		// de otra recta como se calcula el punto de intersección
		
		//Sale de la ecuación paramétrica de la recta
		float t = ?;
		
		float x = point0.x + (point1.x - point0.x) * t;
		float y = point0.y + (point1.y - point0.y) * t;
		float z = point0.z + (point1.z - point0.z) * t;
		
		//Tema iluminación
		float r = color0.r + (color1.r - color0.r) * t;
		float g = color0.g + (color1.g - color0.g) * t;
		float b = color0.b + (color1.b - color0.b) * t;
		
		return { true, vec4(x, y, z, 1.f), vec3(r, g, b) };
	}
	
	
	//Tema iluminación
	struct Intersection
	{
		bool intersected;
		vec4 point;
		vec3 color;
	}	

Camara

class Entity
{
	float scale;
	quat rotation   //Rotacion general
	vec3 position;
	
public:

	Matrix44 get_transform_matrix ()
	{
		Matrix44 identity(1);
		Matrix44 scaling     = glm::scale       (identity, glm:vec3(scale, scale, scale));
		Matrix44 rotation_y  = rotate_around_y  (identity, angle);

		// X, Y, Z axises distance (Arriba izquierda es el 0,0)
		Matrix44 translation = translate        (identity, position);

		// Creación de la matriz de transformación unificada:
		return translation * rotation_y * scaling;
		//return parent.getTransformMatrix * translation * rotation_y * scaling;
	}
};

class Model : public Entity
{
	...
	
public:
	
	void render(Rasterizer & rasterizer, Camera & camera)
	{
		// Creación de la matriz de transformación unificada:
		Matrix44 transformation = 
			camera.get_projection_matrix() * 
			camera.get_transform_matrix_inverse() *	
			//Un parent iria aqui en medio
			this->get_transform_matrix();
	}
};

class Camera : public Entity
{
	Matrix44 projection;
	
public:
	
	Matrix44 get_projection_matrix() const 
	{
		return projection;
	}
	
	Matrix44 get_transform_matrix_inverse () const
	{
		return glm::inverse (get_transform_matrix());
	}
}

Iluminación

DE class Model : public Entity

	void render(Rasterizer & rasterizer, Camera & camera)
	{
		// Creación de la matriz de transformación unificada:
		Matrix44 model_view_matrix = 
			camera.get_projection_matrix() * 
			this->get_transform_matrix();
			
		// Creación de la matriz de transformación unificada:
		Matrix44 model_projection_matrix = 
			camera.get_projection_matrix() * 
			model_view_matrix;
			
		for (int i = 0 < i < number_of_vertices; ++i)
		{
			vec4 p = model_view_matrix * original_vertices[i]; //< Valor 1 en original vertices
			vec4 n = model_view_matrix * original_normals [i]; //< Valor 0 en las normales			
			vec4 l = (model_view_matrix * light.position) - p;
			
			float diffuse_intensity = clamp (normalize (n) * normalize(l), 0.f, 1.f);
					
			
			transformed_colors[i] = material_color * intensity;
			
			vec4 & transformed_vertex = transformed_vertices[i] = transform_matrix * original
			
			float divisor = 1.f / transformed_vertex.w;
			
			transformed_vertex *= divisor;
		}
	}