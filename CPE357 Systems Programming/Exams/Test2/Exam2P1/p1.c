void* memInsert(void *to, int toLength, 
   int atOffset, void *from, int fromLength)
{
   int i = fromLength;
   int j = toLength - atOffset;
   int k = toLength + fromLength;
   int l = atOffset+fromLength;
   while ( j-- > 0 )
   {
      ((char*)to)[--k] = ((char*)to)[l--];
   }
   while ( i-- > 0 )
   {      
      ((char*)to)[atOffset+i] = ((char*)from)[i];
   }
   return to;
}

int main()
{
   return 0;
}