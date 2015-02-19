varying vec3 normal;
varying vec3 ec_pos;
uniform sampler2D Texture0;

#define MAX_LIGHTS 8
#define NUM_LIGHTS 4

void main()
{
	//vec4 color = vec4(0.3, 0.7, 1.0, 1.0);
	
    vec4 color = texture2D( Texture0 , vec2( gl_TexCoord[0] ) );
    vec3 viewVec = normalize( -ec_pos );
    float diff = 0.0;
    int i;
    for(i = 0; i < NUM_LIGHTS; i++){
        vec3 light = vec3(gl_LightSource[i].position[0], gl_LightSource[i].position[1], gl_LightSource[i].position[2] );
        vec3 lightdir = light - ec_pos;
        vec3 reflectVec = normalize(reflect( -lightdir, normal ));
	
        //Diffuse intensity
        float diffAux = max( dot(normalize(lightdir), normalize(normal)), 0.0);
        //Specular intensity
        float spec = 0.0;
	
        //Specular intensity
        if (diffAux > 0.0)
        {
            spec = max(dot(reflectVec, viewVec), 0.0);
            //The specular highlight only gets smaller when
            //raised to some power.
            //Leaving it out gives a nice big highlight.
            //spec = pow(spec, 16.0);
        }   
	
        diff +=  diffAux * 0.6 + spec * 0.4;
    }
	
	//Diffuse intensity
	if (diff > 0.90)
		diff = 1.1;
	else if (diff > 0.5)
		diff = 0.7;
	else 
		diff = 0.5;
    
    color *= vec4 ( diff, diff, diff, 1.0 );
	
	gl_FragColor = color;
}