#include <stdio.h>
#include "cuboid.h"
#include "ui.h"

int main()
{
   double l, w, h;
   
   l = getLength();
   w = getWidth();
   h = getHeight();

   showResults(makeCuboid(l,w,h));
}

