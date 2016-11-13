USE_SDL := 0

# This will likely need to be changed to suit your installation.
ALE := ../Arcade-Learning-Environment-0.5.1

FLAGS := -c -O2 -I$(ALE)/src -I$(ALE)/src/controllers -I$(ALE)/src/os_dependent -I$(ALE)/src/environment -I$(ALE)/src/external
CXX := g++
SOURCES := tt.cpp utilities.cpp FunctionAproximation.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LDFLAGS :=  -L$(ALE) -lale -lz
EXECUTABLE=Agent

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	FLAGS += -Wl,-rpath=$(ALE)
endif
ifeq ($(UNAME_S),Darwin)
	FLAGS += -framework Cocoa
endif

ifeq ($(strip $(USE_SDL)), 1)
	DEFINES += -D__USE_SDL -DSOUND_SUPPORT
	FLAGS += $(shell sdl-config --cflags)
	LDFLAGS += $(shell sdl-config --libs)
endif

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(DEFINES) $(FLAGS) $<

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
