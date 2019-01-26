#ifndef CUBOID_H
#define CUBOID_H

typedef struct{
   double l, w, h;
} Cuboid;

double getVolume(Cuboid cuboid);
double getSurfaceArea(Cuboid cuboid);
Cuboid makeCuboid(double l, double w, double h);

#endif
