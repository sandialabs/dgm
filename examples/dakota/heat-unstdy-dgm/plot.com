# This plots the initial, final and target solutions
set key bottom
set xlabel "x"
set ylabel "u"
set title "Optimal Unsteady Robin Boundary Control"
plot "heat.0.dat" u 1:2 w l title "Initial condition"
replot "heat.50.dat" u 1:2 w l title "Final (optimal) solution"
replot sin(pi*tan(1.3*(2.0*x-1.0))/tan(1.3)) t "Terminal target"
