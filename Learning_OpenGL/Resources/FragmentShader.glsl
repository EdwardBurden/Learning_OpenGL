#version 330 core
out vec4 FragColor;
  
//in vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
vec4 tex2sampled =  texture(texture2, TexCoord).rgba;
//FragColor = ourColor*tex2sampled.a;
FragColor = mix( texture(texture1, TexCoord).rgba , tex2sampled, tex2sampled.a * 1);
  // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
  //  FragColor = texture(texture2, TexCoord);
}