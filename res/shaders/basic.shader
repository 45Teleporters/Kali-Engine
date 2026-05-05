#shader vertex
#version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aTexCoord;
    layout (location = 2) in vec3 aNormal;

    out vec2 TexCoord;
    out vec3 Normal;
    out vec3 FragPos;

    uniform mat4 model;
    uniform mat4 view; 
    uniform mat4 projection; 

    void main()
    {
    gl_Position= projection * view * model * vec4(aPos,1.0);
    FragPos= vec3(model *vec4(aPos, 1.0));
        TexCoord= vec2(aTexCoord.x, aTexCoord.y);
        Normal= vec3(model *vec4(aNormal,1.0));
    }
#shader fragment1
#version 330 core 
   out vec4 FragColor;

   in vec2 TexCoord;
   in vec3 Normal;
   in vec3 FragPos;

   uniform sampler2D texture1;
   uniform sampler2D texture2;

   uniform vec3 lightPos;
   uniform vec3 objectColor;
   uniform vec3 lightColor;
   uniform float ambientStrength;
    
    vec3 norm= normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff= max(dot(norm, lightDir), 0.0);
    vec3 diffuse= diff*lightColor;
    vec3 ambient = lightColor * ambientStrength;
    vec3 result = (ambient +diffuse) * objectColor ;
    void main()
    {
       FragColor = mix(mix(texture(texture1, TexCoord), texture(texture2, TexCoord) , 0.5), vec4(result, 1.0), 0.5);
}

#shader fragment2
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0); // set all 4 vector values to 1.0
}
