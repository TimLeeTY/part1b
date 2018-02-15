
set yrange [0:1]
set term png size 800,800 
set output "plot2.png"
unset key
plot 'out.txt' u 1:7  w l, 