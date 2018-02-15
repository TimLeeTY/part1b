set term svg size 1600,800 
set output "plot1.svg"
set multiplot layout 1, 2
set xrange [-1.5:1.5]
set yrange [-2:2] 
plot 'out.txt' u 2:3 w l lc rgb "red",'out.txt' u 5:6 w l lc rgb "blue",'out.txt' u 8:9 w l lc rgb "green"
set xrange [0:40]
set yrange [-20:20]
plot 'out.txt' u 1:11 w l lc rgb "purple",'out.txt' u 1:12 w l lc rgb "grey",'out.txt' u 1:13 w l lc rgb "black" 
unset multiplot

set term gif animate delay 20 size 1600, 800
set output "point1.gif"
unset key
do for [j=1:50] {
    set multiplot layout 1, 2
    set xrange [-1.5:1.5]
    set yrange [-2:2]
    i=j*4000
    plot 'out.txt' u 2:3 every ::1::i w l lc rgb "red",'out.txt' u 2:3 every ::i::i w p lc rgb "red" ps 5, 'out.txt' u 5:6 every ::1::i w l lc rgb "blue" ,'out.txt' u 5:6 every ::i::i w p lc rgb "blue" ps 5, 'out.txt' u 8:9 every ::1::i w l lc rgb "green", 'out.txt' u 8:9 every ::i::i w p lc rgb "green" ps 5
    set xrange [0:40]
    set yrange [-20:20]
    plot 'out.txt' u 1:11 every ::1::i w l lc rgb "purple",'out.txt' u 1:12 every ::1::i w l lc rgb "grey",'out.txt' u 1:13 every ::1::i w l lc rgb "black"
    unset multiplot
}

