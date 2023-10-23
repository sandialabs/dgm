TARGET = libjson

ALL = json_value json_reader json_writer

OBJS = $(foreach module, $(ALL) $(SPECIAL), $(module).o)

DEST = ..

VPATH = ../src

CXXFLAGS = -I ../include

ifdef DGM_SHARED
  lib: $(TARGET).a $(TARGET).$(SO)
	@echo Making JSON lib 
else
  lib: $(TARGET).a
endif

$(TARGET).a: $(OBJS)
	$(AR) $(ARFLAGS) $(TARGET).a $(OBJS)
	ranlib $(TARGET).a
	$(MAKE) install

$(TARGET).$(SO): $(OBJS)
ifdef INSTALL_HOME
	@echo INSTALL_HOME is defined
	$(LD) $(SHARED) $(INSTALL_HOME)
else
	$(LD) $(SHARED) $(OBJS) $(LIBS) -o $(TARGET).$(SO)
endif

install:
	@echo Insalling the JSON library to $(DEST)
	mkdir -p $(DEST)
	mkdir -p $(DEST)/lib
	rsync -t *.a $(DEST)/lib

.cpp.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(VPATH)/$*.cpp 

.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $(VPATH)/$*.c

.PHONY: clean
clean :
	rm -r $(OBJS)
