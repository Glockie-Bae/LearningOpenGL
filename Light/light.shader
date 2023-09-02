#shader vertex 
#version 330 core 
layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec3 aNormal; 

out vec3 FragPos; 
out vec3 Normal; 

uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection; 

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}


#shader fragment 
#version 330 core 
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 camreaPos;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //Specular Highlight
    float specLightStrength = 0.5f;

    vec3 camreaDir = normalize(camreaPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(reflectDir, camreaDir), 0.0), 32);
    vec3 specLight = spec * specLightStrength * lightColor;

            
    vec3 result = (ambient + diffuse + specLight) * objectColor;
    FragColor = vec4(result, 1.0);
} 
