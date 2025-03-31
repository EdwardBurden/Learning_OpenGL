#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
//layout (location = 1) in vec3 aColor; // the position variable has attribute position 0
layout (location = 1) in vec2 aTextureCoord; // the position variable has attribute position 0

//out vec4 ourColor; // specify a color output to the fragment shader
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
   // gl_Position = transform * vec4(aPos, 1.0f);
    //gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
  //  ourColor = vec4(aColor, 1); // set the output variable to a dark-red color
    TexCoord = aTextureCoord;
}