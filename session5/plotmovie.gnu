set term gif animate delay 30 size 400, 400
set output "point.gif"
set xrange [-3:3]
set yrange [-3:3]
stats 'out.txt' nooutput
do for [i=1:int(STATS_blocks)] {
    plot 'out.txt' u 2:3 index (i-1) w l, 'out.txt' index (i-1) every ::1::1 u 2:3:4:5 w vector, 'sun' w p
    unset key
}
