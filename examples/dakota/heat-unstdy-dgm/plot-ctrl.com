# This plots the initial, final and target solutions
set key bottom
set xlabel "x"
set ylabel "phi_Rr"
set title "Optimal Unsteady Robin Boundary Control"
plot "phi_Rr.1.dat" u 1:2 w l title "iter = 1"
replot "phi_Rr.2.dat" u 1:2 w l title "iter = 2"
replot "phi_Rr.3.dat" u 1:2 w l title "iter = 3"
replot "phi_Rr.4.dat" u 1:2 w l title "iter = 4"
replot "phi_Rr.5.dat" u 1:2 w l title "iter = 5"
