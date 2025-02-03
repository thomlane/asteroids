#version 400

uniform sampler2D u_Texture;

in vec2 v_TexCoord;

out vec4 FragColor;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    FragColor = texColor;
    //FragColor.xyz = vec3(1,1,1);
};