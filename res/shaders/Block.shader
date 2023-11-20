#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * position;
    v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoord;

//uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform vec3 u_BorderColor;
uniform float u_BorderThickness;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    FragColor = texColor;
    
    float borderFactorX = min(abs(fwidth(gl_FragCoord.x)), u_BorderThickness * 0.5);
    float borderFactorY = min(abs(fwidth(gl_FragCoord.y)), u_BorderThickness * 0.5);
    
    float borderFactor = 1.0 - smoothstep(0.5 - borderFactorX, 0.5 + borderFactorX, min(borderFactorX, borderFactorY));
    FragColor.rgb = mix(u_BorderColor, FragColor.rgb, borderFactor);
    
    FragColor.a = 1.0;

}