#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 vcolor;

uniform float u_cubeYAngleRotation;
uniform float u_cubeXAngleRotation;

uniform vec3 u_cubeAbsolutePosition;

uniform float u_Xshift;
uniform float u_Zshift;

uniform float u_viewXangle;
uniform float u_viewYangle;

const float mirrorNearPlane = 20.0;
const float mirrorFarPlane = 500.0;
const float mirrorHalfLength = 20.0;

out vec3 fcolor;

void main()
{ 
   //obracamy obiekt wokół włsnej osi Y
   float x1 = position.x * cos(u_cubeYAngleRotation) - position.z * sin(u_cubeYAngleRotation);
   float z1 = position.x * sin(u_cubeYAngleRotation) + position.z * cos(u_cubeYAngleRotation);
   float y1 = position.y;

   //obracamy obiekt wokół włsnej osi X
   float y2 = y1 * cos(u_cubeXAngleRotation) - z1 * sin(u_cubeXAngleRotation);
   float z2 = y1 * sin(u_cubeXAngleRotation) + z1 * cos(u_cubeXAngleRotation);
   float x2 = x1;

   //przesowamy do pozycji absolutnej 
   float AbsoluteX = x2 + u_cubeAbsolutePosition.x;
   float AbsoluteY = y2 + u_cubeAbsolutePosition.y;
   float AbsoluteZ = z2 + u_cubeAbsolutePosition.z;

   AbsoluteX = AbsoluteX + u_Xshift;
   AbsoluteZ = AbsoluteZ + u_Zshift;

   //obracamy kamere wokół osi Y
   float viewdRotatedX = AbsoluteX * cos(u_viewYangle) - AbsoluteZ * sin(u_viewYangle);
   float viewdRotatedZ = AbsoluteX * sin(u_viewYangle) + AbsoluteZ * cos(u_viewYangle);
   float viewdRotatedY = AbsoluteY;

   //obracamy kamere wokół osi X
   float viewdRotatedY2 = viewdRotatedY * cos(u_viewXangle) - viewdRotatedZ * sin(u_viewXangle);
   float viewdRotatedZ2 = viewdRotatedY * sin(u_viewXangle) + viewdRotatedZ * cos(u_viewXangle);
   float viewdRotatedX2 = viewdRotatedX;

   if (viewdRotatedZ2 <= mirrorNearPlane) {
      gl_Position = vec4(0, 0, -2, 0); // wyrzucamy punkt
      return;
   }
 
   //robimy projekcje na wspolzedne 2D monitora
   float projectedX = mirrorNearPlane * viewdRotatedX2 / viewdRotatedZ2;
   float projectedY = mirrorNearPlane * viewdRotatedY2 / viewdRotatedZ2;

   float finalX = projectedX / mirrorHalfLength;
   float finalY = projectedY / mirrorHalfLength;

   //normaluzujemy obiekty ze wspolzedna z na przedzial [-1, 1] do zbuffora
   float depthBuffer = (viewdRotatedZ2 - 20.0) / (500.0 - 20.0);
   depthBuffer = depthBuffer * 2.0 - 1.0;

   gl_Position = vec4(finalX, finalY, depthBuffer, 1);

   fcolor = vcolor;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec3 fcolor;

void main()
{
   color = vec4(fcolor, 1.0);
};