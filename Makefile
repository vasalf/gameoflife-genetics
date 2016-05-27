SRCDIR=src
OBJDIR=obj
SUBDIRS=$(shell find $(SRCDIR) -type d)
OBJSUBDIRS=$(subst $(SRCDIR),$(OBJDIR),$(SUBDIRS))

CXX=g++
CXXFLAGS=--std=c++0x -O2 -Wall -Wextra -I$(SRCDIR)
LD=g++

SUFFIXES=.cpp
SRCS=$(foreach subd,$(SUBDIRS),$(foreach suf,$(SUFFIXES),$(wildcard $(subd)/*$(suf))))
OBJS=$(foreach subd,$(SUBDIRS),$(foreach suf,$(SUFFIXES),$(subst $(SRCDIR),$(OBJDIR),$(subst $(suf),.o,$(wildcard $(subd)/*$(suf))))))

all: test

test: $(OBJS) Makefile
	$(LD) $(CXXFLAGS) $(OBJS) -o test

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp Makefile | $(OBJSUBDIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJSUBDIRS):
	mkdir -p $@

clean:
	rm -Rf test $(OBJDIR)

.PHONY: all clean
