# Compiler Info ('g++-4.8 --version')
# g++-4.8 (GCC) 4.8.2 20140120 (Red Hat 4.8.2-15)
# Copyright (C) 2013 Free Software Foundation, Inc.
# This is free software; see the source for copying conditions.  There is NO
# warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# End Compiler Info Output
CXX ?= g++
#CXX ?= g++-4.8
#LINK ?= g++-4.8
LINK ?= g++
#NDKDIR ?= /opt/foundry/nuke11/
NDKDIR ?= /opt/foundry/nuke16/Nuke16.0v8
#You will need to set the path to boost for psdReader only
#BOOSTDIR ?= REPLACE_ME_WITH_BOOST_DIR
#You will need to set the path to openEXR for exr plugins only
#OPENEXRDIR ?= REPLACE_ME_WITH_OPENEXR_DIR
CXXFLAGS ?= -g -c \
            -DUSE_GLEW \
            -I"$(NDKDIR)"/include \
            -DFN_EXAMPLE_PLUGIN -fPIC -msse 
CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=1
LINKFLAGS ?=-L"$(NDKDIR)" \
	-L./ 
LIBS ?= -lDDImage
LINKFLAGS += -shared 
all: Add.so \
     SimpleBlur.so \
     AddInputs.so \
	 CatoGamma.so \
	 CatoContrast.so \
	 CatoSharpen.so \
	 CatoEdge.so \
	 CatoMedian.so \
	 CatoColorDifference.so

.PRECIOUS : %.os
%.os: %.cpp
	$(CXX) $(CXXFLAGS) -o $(@) $<
%.so: %.os
	$(LINK) $(LINKFLAGS) -o $(@) $< $(LIBS)
%.a: %.cpp
	$(CXX) $(CXXFLAGS) -o lib$(@) $<

ndkexists:
	if test -d $(NDKDIR); \
	then echo "using NDKDIR from ${NDKDIR}"; \
	else echo "NDKDIR dir not found! Please set NDKDIR"; exit 2; \
	fi
clean:
	rm -rf *.os \
	       *.o \
	       *.a \
	       *.so
