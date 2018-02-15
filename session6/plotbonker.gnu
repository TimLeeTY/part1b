stats 'out.txt' nooutput
set style data points
set term png size 800,800 
set output "plot1.png"
set yrange [0:1]
unset key
balls=10
plot for [i=1:balls] 'out.txt' u 1:2*i  w l, 
set term png size 800,800 
set output "plot2.png"
unset key
plot 'out.txt' u 1:12  w l, 
frames=100
N=floor(15000/frames)
set term gif animate delay 20 size 1000, 800 
set output "point1.gif"
unset key
do for[i=1:frames]{``
	set yrange [0:1]
	set xrange [0:15]
	j=i*N
	plot for [k=1:balls] 'out.txt' u 1:2*k  every ::1::j w l, for [k=1:balls] 'out.txt' u 1:2*k  every ::j::j w p pointtype 5 ps 3
}
