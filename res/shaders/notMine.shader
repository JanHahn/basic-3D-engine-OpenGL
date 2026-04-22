#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vcolor;

uniform float u_angle;
uniform float u_anglee;
uniform float distance;

uniform float u_Xshift;
uniform float u_Zshift;

out vec3 fcolor;

void main()
{
    // 1. Rotacja wokół osi Y (u_angle)
    float x1 = position.x * cos(u_angle) - position.z * sin(u_angle);
    float z1 = position.x * sin(u_angle) + position.z * cos(u_angle);
    float y1 = position.y;

    // 2. Rotacja wokół osi X (u_anglee)
    float y2 = y1 * cos(u_anglee) - z1 * sin(u_anglee);
    float z2 = y1 * sin(u_anglee) + z1 * cos(u_anglee);
    float x2 = x1;
    float fovDistance = 0.5; 
    float zOffset = z2 + distance; 

    // Jeśli dodałeś u_aspect w C++, użyj go tutaj:
    // float projectedX = (fovDistance * x2 / zOffset) / u_aspect;
    float projectedX = fovDistance * x2 / zOffset;
    float projectedY = fovDistance * y2 / zOffset; 

    // gl_Position.z musi być w przedziale [-1, 1]. 
    // zOffset * 0.1 to tylko wizualny trik, ale do prostego testu wystarczy.
    gl_Position = vec4(projectedX + u_shift, projectedY, z2, 1);

    fcolor = vcolor;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec3 fcolor;

void main()
{
   color = vec4(fcolor, 1.0);
};