d2f.py --n1 100 --n2 100 -o tmp.bin $1
ximage style=normal n1=100 n2=100 wbox=500 hbox=500 legend=1 \
bclip=1.99606 wclip=0.00394265 blockinterp=0 f1=0.02 f2=0.02 d1=0.04 d2=0.04 xbox=1 ybox=0 cmap=hsv2 < tmp.bin
/bin/rm tmp.bin
