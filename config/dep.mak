
#  Automatically make dependencies
%.d: %.cu
	@echo Making dependencies for $*
ifdef VERBOSE
	@echo nvcc -M $<
endif
	@set -e; nvcc -M $< \
	| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
	[ -s $@ ] || rm -f $@
	@cp -f $*.d $*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	 sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

%.d: %.cpp
	@echo Making dependencies for $*
ifdef VERBOSE
	@echo $(CXX) $(DEP) $(CPPFLAGS) $(CXXFLAGS) $<
endif
	@set -e; $(CXX) $(DEP) $(CPPFLAGS) $(CXXFLAGS) $< \
	| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
	[ -s $@ ] || rm -f $@
	@cp -f $*.d $*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	 sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

#  Automatically make dependencies
%.d: %.c
	@echo Making dependencies for $*
ifdef VERBOSE
	@echo $(CC) $(DEP) $(CPPFLAGS) $(CFLAGS) $<
endif
	@set -e; $(CC) $(DEP) $(CPPFLAGS) $(CFLAGS) $< \
	| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
	[ -s $@ ] || rm -f $@
	@cp -f $*.d $*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	 sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp
