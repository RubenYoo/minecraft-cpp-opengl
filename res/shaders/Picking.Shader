#shader vertex
#version 330                                                                        
                                                                                    
layout (location = 0) in vec3 Position;                                             
                                                                                    
uniform mat4 gWVP;                                                                  
                                                                                    
void main()                                                                         
{                                                                                   
    gl_Position = gWVP * vec4(Position, 1.0);                                       
}

#shader fragment
#version 330

uniform uint gObjectIndex;

out uvec3 FragColor;

void main()
{
   FragColor = uvec3(gObjectIndex, 0.0, 0.0);
}