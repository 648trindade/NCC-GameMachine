CXX = g++
NAME = Game

# ECHO colors
CNORMAL = \033[0m
CGREEN  = \033[32m

MFLAGS = -f Makefile

SDL2_CFLAGS     = $(shell sdl2-config --cflags)

SDL2_LDFLAGS    = $(shell sdl2-config --libs) \
                  -lSDL2_image -lSDL2_ttf \
                  -static-libgcc -static-libstdc++

CXXFLAGS        = -c -g -pedantic -Wall -Wpointer-arith -Wcast-qual -std=c++11 \
                  -Iinclude $(SDL2_CFLAGS)

DISTDIR     = .

LD          = g++
LDFLAGS     = $(SDL2_LDFLAGS)
RM          = rm
ECHO        = echo
CP          = cp
MV          = mv

OBJDIR              = obj
DEPS                = $(shell find src/ -name *.h)
EXECUTABLE          = $(DISTDIR)/Game
PROG_SOURCES        = $(shell find src/ -name *.cpp)
PROG_OBJECTS        = $(shell find src/ -name *.cpp | sed "s/src\(.*\)cpp/obj\1o/g")

LIBRARIES           = 

.PHONY: $(LIBRARIES) $(OBJDIR) libs default clean cleanall copyresources buildzip

default: $(OBJDIR)  
	@$(ECHO) "$(CGREEN)Creating distribution directory $(DISTDIR)$(CNORMAL)"
	@mkdir -p $(DISTDIR)
	@$(MAKE) $(MFLAGS) --no-print-directory libs
	@$(ECHO) "$(CGREEN)Building $(EXECUTABLE)...$(CNORMAL)"
	@$(MAKE) $(MFLAGS) --no-print-directory '$(EXECUTABLE)'
	@$(ECHO) "$(CGREEN)Building $(EXECUTABLE) complete$(CNORMAL)"
	#@$(ECHO) "$(CGREEN)Copying resources$(CNORMAL)"
	#@$(MAKE) $(MFLAGS) --no-print-directory copyresources
	#@$(ECHO) "$(CGREEN)Creating zip file$(CNORMAL)"
	#@$(MAKE) $(MFLAGS) --no-print-directory buildzip
	@$(ECHO) "$(CGREEN)Done$(CNORMAL)"

all: default

libs: $(LIBRARIES)

$(EXECUTABLE): $(PROG_OBJECTS) $(DEPS)
	$(LD) $(PROG_OBJECTS) -o $@ $(LDFLAGS)

$(OBJDIR):
	@mkdir -p `tree src -dif | grep src | sed "s/src/obj/g"`

$(OBJDIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(LIBRARIES):
	@$(ECHO) "$(CGREEN)Building $@lib...$(CNORMAL)"
	@$(MAKE) -C $@ $(MFLAGS)
	@$(ECHO) "$(CGREEN)Building $@lib complete$(CNORMAL)"

copyresources:
	@$(CP) -r etc $(DISTDIR)/.

buildzip:
	zip -r Game.zip $(DISTDIR)

clean:
	@$(ECHO) Cleaning project
	@$(RM) -f $(EXECUTABLE) $(PROG_OBJECTS)

cleanall:
	@$(ECHO) Cleaning project and all libraries
	@for d in $(LIBRARIES); do (cd $$d; $(MAKE) $(MFLAGS) --no-print-directory clean ); done
	@$(RM) -f $(EXECUTABLE) $(PROG_OBJECTS)
