//Interpolates the vertex normal across the texture fragment
varying vec3 normal;
//Interpolate the texel position in eye space.
varying vec3 ec_pos;

#define MAX_LIGHTS 8
#define NUM_LIGHTS 3

void main()
{
    // Front color
    gl_FrontColor = gl_Color;
    
    // Textures coordinates
    gl_TexCoord[0] = gl_MultiTexCoord0;
    
	normal = normalize(gl_NormalMatrix * gl_Normal);
    
	ec_pos = vec3(gl_ModelViewMatrix * gl_Vertex);
	
	//Perform fixed transformation for the vertex
	gl_Position = ftransform();		
}
