
//TRANSPARENCIAS

void Scene::render()
{
	glDisable 	(GL_BLEND);
	glDepthMask (GL_TRUE);
	
	glClear		(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// DIBUJAR TODAS LAS MALLAS OPACAS
	
	glEnable 	(GL_BLEND);
	glDepthMask (GL_FALSE);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// vec3 color = src.rgb * src.a + dst.rgb * (1 - src.a);
	
	// DIBUJAR TODAS LAS MALLAS TRANSPARENTES
	
		
}


