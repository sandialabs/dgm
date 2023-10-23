# convert mesh from my format to NekTar

awk '($1=="ELEMENT") {print $1,$2+1} ($1!="ELEMENT") {print $1,$2,$3,$4}' 

# convert NekTar mesh to my format

awk '($1=="ELEMENT") {print $1,$2-1,"TRI"} ($1!="ELEMENT") {print $1,$2,$3,$4}' 
# convert con from my format to NekTar

awk '($1=="E") {print $1,$2+1,$3+1,$4+1,$5+1,0} ($1!="E") {print}' 

# convert NekTar con to my format

awk '($1=="E") {print $1,$2-1,$3-1,$4-1,$5-1} ($1!="E") {print}' 

# Adds offset to element numbers and switches edge ids

awk 'BEGIN {eoff=26;x[0]=0;x[1]=2;x[2]=1;} (NR<3) {print} (NR>1 && $1=="E") {print $1,$2+eoff,x[$3],$4+eoff,x[$5]}' < bump.con > b.con

awk 'BEGIN {eoff=26;x[0]=0;x[1]=2;x[2]=1;} (NR<3) {print} (NR>2) {print $1,$2+eoff,x[$3]}' < bump.bc >! b.bc

# triangles

awk 'BEGIN {eoff=26;ysign=-1;n=1;} (NR<3) {print} ($1=="ELEMENT") {print $1,$2+eoff,$3} ($1!="ELEMENT" && NR>2 && n%2) {printf("%9.5f %9.5f %9.5f\n",$2,$1,$3)} ($1!="ELEMENT" && NR>2 && n%2==0) {printf("%9.5f %9.5f %9.5f\n",ysign*$2,ysign*$1,ysign*$3)} ($1!="ELEMENT" && NR>2) {n++}' < bump.msh > b.msh
