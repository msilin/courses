#include <stdio.h>

int main()
{
   double l, w, h, v, sa;
   char nl;
   printf("Enter the length of the cuboid: ");
   scanf("%lf", &l);
   printf("Enter the  width of the cuboid: ");
   scanf(" %lf", &w);
   printf("Enter the height of the cuboid: ");
   scanf(" %lf", &h);
   v = l * w * h;
   sa = 2 * (l*w + w*h + h*l ); 
   printf("V=%.2f SA=%.2f (Cuboid: L=%.2f W=%.2f H=%.2f)\n", v, sa, l, w, h);
   return 0;
}
