#
# Make a gnuplot of a Tecplot profile.dat file
#
plot "profile.dat" u 1:3 title "R" w l
replot "profile.dat" u 1:4 title "U" w l
replot "profile.dat" u 1:5 title "V" w l
replot "profile.dat" u 1:6 title "E" w l
set xlabel "x"
set ylabel "R, U, V, E"
set title "2d Cylinder flow:  M_ref = 2.0"
set key left
set term post eps color 14 lw 2
set output "p=2_M=2.eps"
replot
set term x11
replot
#
# End of gnuplot command file
#