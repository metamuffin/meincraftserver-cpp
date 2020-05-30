debug : LDFLAGS += -Og -g
release : LDFLAGS += -Os

BUILDDIR = $(shell pwd)/build
export BUILDDIR

.PHONY: debug release clean

debug:
	$(MAKE) --directory=src
	$(CXX) $(BUILDDIR)/*.o $(LDFLAGS) -o $(BUILDDIR)/main

release:
	$(MAKE) --directory=src
	$(CXX) $(BUILDDIR)/*.o $(LDFLAGS) -o $(BUILDDIR)/main

clean:
	$(RM) $(BUILDDIR)/*.o $(BUILDDIR)/main

