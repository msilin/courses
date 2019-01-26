#include <stdio.h>

double getLength();
double getWidth();
double getHeight();
double getVolume(double l, double w, double h);
double getSurfaceArea(double l, double w, double h);
double showResults(double l, double w, double h);

int main()
{
   double l, w, h;
   
   l = getLength();
   w = getWidth();
   h = getHeight();
   showResults(l,w,h);
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
double getVolume(double l, double w, double h)
{
   return l * w * h;
}
double getSurfaceArea(double l, double w, double h)
{
   return 2 * (l*w + w*h + h*l); 
}
double showResults(double l, double w, double h)
{
   printf("V=%.2f SA=%.2f (Cuboid: L=%.2f W=%.2f H=%.2f)\n",
      getVolume(l,w,h), getSurfaceArea(l,w,h), l, w, h);
}

