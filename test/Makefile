LEX = flex -I
YACC = bison -d

srcdir = .

BZDIR = /home/collis/dist/blitz
MTLDIR = /home/collis/dist/mtl-2.1.2-20
ATLASDIR = /home/collis/dist/atlas
TNTDIR = ../ 

CXX = g++
CXXFLAGS = -ftemplate-depth-30 -O2 -funroll-loops -fstrict-aliasing \
-fno-gcse -I$(BZDIR) -I$(MTLDIR) -I$(ATLASDIR)/include -I$(TNTDIR)
LDFLAGS = 

CC = gcc
CCFLAGS = -O2 -I.

LIBS = -L$(BZDIR)/lib -lblitz -L$(ATLASDIR)/lib -llapack -lcblas -latlas \
-lblas -lg2c -lm 

############################################################################

.SUFFIXES: .o .cpp .y .l 

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $(srcdir)/$*.cpp

.c.o:
	$(CC) $(CCFLAGS) -c $(srcdir)/$*.c

table:
	$(CXX) $(LDFLAGS) $@.o -o $@

matrix:
	$(CXX) $(LDFLAGS) $@.o mmio.o -o $@ $(LIBS)

blitz:
	$(CXX) $(LDFLAGS) $@.o mmio.o -o $@ $(LIBS)

mtl:
	$(CXX) $(LDFLAGS) $@.o mmio.o -o $@ $(LIBS)

parser:
	$(YACC) $@.y
	$(LEX) $@.l
	$(CXX) -I.. lex.yy.c $@.tab.c -o $@

mpiio: mpiio.cpp
	mpicxx mpiio.cpp -o mpiio

###########################################################################

table: table.o Table.h

table.o: Table.h

matrix: matrix.o mmio.o

matrix.o: Matrix.h

blitz: blitz.o mmio.o

mtl: mtl.o mmio.o

parser: parser.y parser.l parser.h

###########################################################################

clean:
	rm -f *.o *.ii *.int.c *.s $(EXAMPLES)
