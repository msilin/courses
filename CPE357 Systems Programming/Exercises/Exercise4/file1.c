#include <stdio.h>

typedef struct{
   double l, w, h;
} Cuboid;

double getLength();
double getWidth();
double getHeight();
double getVolume(Cuboid cuboid);
double getSurfaceArea(Cuboid cuboid);
double showResults(Cuboid cuboid);
Cuboid makeCuboid(double l, double w, double h);

int main()
{
   double l, w, h;
   
   l = getLength();
   w = getWidth();
   h = getHeight();
   showResults(makeCuboid(l,w,h));
}

double getLength()
{
   double l;
   printf("Enter the length of the cuboid: ");
   scanf("%lf", &l);
   return l;
}
double getWidth()
{
   double w;
   printf("Enter the  width of the cuboid: ");
   scanf(" %lf", &w);
   return w;
}
double getHeight()
{
   double h;
   printf("Enter the height of the cuboid: ");
   scanf(" %lf", &h);
   return h;
}
double getVolume(Cuboid cuboid)
{
   return cuboid.l * cuboid.w * cuboid.h;
}
double getSurfaceArea(Cuboid cuboid)
{
   return 2 * (cuboid.l*cuboid.w + cuboid.w*cuboid.h + cuboid.h*cuboid.l); 
}
double showResults(Cuboid cuboid)
{
   printf("V=%.2f SA=%.2f (Cuboid: L=%.2f W=%.2f H=%.2f)\n",
      getVolume(cuboid), getSurfaceArea(cuboid), cuboid.l, cuboid.w, cuboid.h);
}
Cuboid makeCuboid(double l, double w, double h)
{
   Cuboid cuboid; 

   cuboid.l = l;
   cuboid.w = w;
   cuboid.h = h;

   return cuboid;
}

