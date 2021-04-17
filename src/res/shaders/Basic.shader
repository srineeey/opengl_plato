#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec4 color;


uniform mat4 u_MVP;

out vec4 v_Color;


void main()
{
    gl_Position = u_MVP*position;
    v_Color = color;
}

    #shader fragment
    #version 330 core

in vec4 v_Color;

layout(location = 0) out vec4 color;

uniform vec4 u_Color;


void main()
{
    color = v_Color;
    //    color = u_Color;
    //    color = vec4(1.0, 0.5, 0.0, 0.0);
}