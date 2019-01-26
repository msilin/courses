#include <assert.h>

double sphereVolume(double radius, double pi)
{
   double v;
   v = pi * (4.0 / 3.0) * radius * radius * radius;
   assert(radius > 0);
   return v;
}