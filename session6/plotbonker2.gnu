set term png size 1600,800 
set output "plot1.png"
t=413
set xrange[0:t]
set yrange [0:1]
unset key
balls=6
set multiplot layout 1,2
plot for [i=1:balls] 'out.txt' u 1:i+1  w l lc rgb "blue", for [i=1:balls] 'out.txt' u 1:i+balls+2 w l lc rgb "red", 'out.txt' u 1:balls+2 w l lc rgb "black" lw 4
set xrange[0:t]
set yrange[0:0.15]
plot for [i=1:4] 'out.txt' u 1:i+2*balls+2 w l
unset multiplot

set term png size 800,800 
set output "plot2.png"
set xrange[0:t]
set yrange[0:1]
unset key
plot 'out.txt' u 1:balls+2  w l, 


frames=100
N=floor(t*100/frames)
set term gif animate delay 15 size 1600, 800 
set output "point1.gif"
unset key
do for[k=1:frames]{
	set multiplot layout 1,2
	set yrange [0:1]
	set xrange [0:t]
	j=k*N
	plot for [i=1:balls] 'out.txt' u 1:i+1  every ::1::j w l lc rgb "blue", 'out.txt' u 1:balls+2 every ::1::j w l lc rgb "black" lw 4, for [i=1:balls] 'out.txt' u 1:i+balls+2  every ::1::j w l lc rgb "red"
	set xrange[0:t]
	set yrange[0:0.15]
	plot for [i=1:4] 'out.txt' u 1:i+balls*2+2 every ::1::j w l;
	unset multiplot
}
