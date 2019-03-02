GCC = g++
CLANG = clang++

# override from command line
# CXXFLAGS ?= -Wall
# in addition append flags
# CXXFLAGS += -Wunused -Wshadow
CXXFLAGS += -Wshadow

dirs := $(shell pwd)
srcfiles := $(shell find $(dirs) -type f -iname "*.cpp" -exec basename {} ";")
objfiles := $(patsubst %.cpp, %.o, $(srcfiles))
depfiles := $(patsubst %.cpp, %.d, $(srcfiles))

srcs := $(wildcard *.cpp)
objs := $(srcs:.cpp=.o)
deps := $(srcs:.cpp=.d)

.phony: all clean

# all: GCC CLANG
	# @echo ver1
	# @echo $(srcfiles) $(objfiles) $(depfiles)
	# @echo ver2
	# @echo $(srcs) $(objs) $(deps)

all: $(objs)
	@echo $(objs)
	@echo

%.o: %.cpp
	@echo "compiling" $<
	@# just compile using GCC, so .o is created from .cpp and make will use timestamp for this file
	@$(GCC) -c $< $(CXXFLAGS) -std=c++17
	$(GCC) -o $<_gcc $< $(CXXFLAGS) -std=c++17
	$(CLANG) -o $<_clang $< $(CXXFLAGS) -stdlib=libc++ -std=c++17

clean:
	rm -f *.o *_gcc *_clang *.orig *.stackdump

