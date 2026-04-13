#shader vertex
#version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aTexCoord;

    out vec2 TexCoord;

    uniform mat4 model;
    uniform mat4 view; 
    uniform mat4 projection; 

    void main()
    {
    gl_Position= projection * view * model * vec4(aPos,1.0);
        TexCoord= vec2(aTexCoord.x, aTexCoord.y);
    }
#shader fragment1
#version 330 core 
   out vec4 FragColor;

   in vec2 TexCoord;

   uniform sampler2D texture1;
   uniform sampler2D texture2;

   uniform vec3 objectColor;
   uniform vec3 lightColor;

   void main()
    {
       FragColor = mix(mix(texture(texture1, TexCoord), texture(texture2, TexCoord) , 0.5), vec4(lightColor *objectColor , 1.0), 0.5);
}

#shader fragment2
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0); // set all 4 vector values to 1.0
}
