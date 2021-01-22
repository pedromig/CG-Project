uniform vec3 camera;
uniform vec3 light_direction;

varying vec3 normal;
varying vec3 vertex;    

void main (void)  {  
    vec4 ambient_light  = vec4(0.6, 0.0, 0.0, 0.0);
    vec4 diffuse_light  = vec4(0.8, 0.2,  0.2, 1.0);
    vec4 specular_light = vec4(0.5, 0.5, 0.5, 1.0);

    vec4 material_ambient  = vec4(0.05, 0.05, 0.05, 1);
    vec4 material_diffuse  = vec4(0.4, 0.4, 0.4, 1);
    vec4 material_specular = vec4(0.774597, 0.774597, 0.774597, 1);

    float ka = 0.1;
    float kd = 0.6;
    float ks = 0.7;
    float s = 32.0;
    float n = 0.5;

    vec3 light = normalize(light_direction);

    vec3 v = normalize(camera - vertex);      
    vec3 r = normalize(2.0 * dot(light, normal) * normal - light);  

    // Light Intensity components calculation acording to the phong lighting model formulas
    float Iambient  = ka;    
    float Idiffuse  = kd * max(dot(normal, light), 0.0);    
    float Ispecular = ks * pow(max(dot(r, v), 0.0) , n * s);

    vec4 ambient_color  = ambient_light;
    vec4 diffuse_color  = diffuse_light * material_diffuse;
    vec4 specular_color = specular_light * material_specular;
  
    gl_FragColor = (ambient_color * Iambient) + (diffuse_color * Idiffuse) + (specular_color * Ispecular);   
}
