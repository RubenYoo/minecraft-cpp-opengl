#shader vertex
#version 330                                                                        
                                                                                    
layout (location = 0) in vec3 Position;                                             
                                                                                    
uniform mat4 u_MVP;                                                                  
                                                                                    
void main()                                                                         
{                                                                                   
    gl_Position = u_MVP * vec4(Position, 1.0);                                       
}

#shader fragment
#version 330

uniform uint u_ObjectIndex;

out uvec3 FragColor;

void main()
{
   FragColor = uvec3(u_ObjectIndex, 0.0, 0.0);
}