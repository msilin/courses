num=0
input=0

for (( i=1; i<=8; i++))
do
   input="-special $i"
   a.out  $(<$input) >> his.o
   b.out  $(<$input) >> my.o
done

   diff -q my.o his.o