#include <stdio.h>
#include "cuboid.h"

double getVolume(Cuboid cuboid)
{
   return cuboid.l * cuboid.w * cuboid.h;
}
double getSurfaceArea(Cuboid cuboid)
{
   return 2 * (cuboid.l*cuboid.w + cuboid.w*cuboid.h + cuboid.h*cuboid.l); 
}
Cuboid makeCuboid(double l, double w, double h)
{
   Cuboid cuboid; 

   cuboid.l = l;
   cuboid.w = w;
   cuboid.h = h;

   return cuboid;
}

