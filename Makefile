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

%.o: %.cpp
	@echo "compiling" $<
	$(GCC) -o $<_gcc $< $(CXXFLAGS) -std=c++17
	$(CLANG) -o $<_clang $< $(CXXFLAGS) -stdlib=libc++ -std=c++17

# GCC:
	# $(GCC) -o main_gcc main.cpp $(CXXFLAGS) -std=c++17

# CLANG:
	# $(CLANG) -o main_clang main.cpp $(CXXFLAGS) -stdlib=libc++ -std=c++17

clean:
	rm -f *_gcc *_clang *.orig

