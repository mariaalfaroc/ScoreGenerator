
#Color for the compliation message -> Blue with emphasis
COM_COLOR = \033[1;34m	
#Color for the success message -> Green with emphasis				   
SUCCESS_COLOR = \033[1;32m
#No special color				  
NO_COLOR =  \033[m				

#Generic compilation message string that won't change for now
COM_STRING = "COMPILING..."
#Generic success message string that won't change for now			   
COM_END = "SUCCESS!"
#Generic compilation message string that won't change for now
COM_STRING = "COMPILING..."
LINK_STRING = "LINKING..."
#Generic success message string that won't change for now			   
COM_END = "SUCCESS!"

RELEASEFOLDER=bin/
PROGRAM=generador
OBJDIR=bin/obj
SRCDIR=src

SOURCES := $(wildcard src/*.cpp)				#All the source files in our project (located in src folder)
FIRSTOBJECTS := $(subst  .cpp,.o,$(SOURCES))	#All the object files in our project. We pick all the cpp files and change it's extention with an o in order to obtain, for example, src/Game.cpp -> src/Game.o
OBJECTS:= $(subst src/,bin/obj/,$(FIRSTOBJECTS))	#This was a quick soultion as the last function picked up the src/ part of the path. We change all src to obj (where our binaries are), src/Game.o -> obj/Game.o  	

all: mkdir $(RELEASEFOLDER)$(PROGRAM)

$(RELEASEFOLDER)$(PROGRAM):$(OBJECTS)
	@printf "%b" "$(COM_COLOR)$(LINK_STRING) $(OBJ_COLOR)$(^)$(NO_COLOR)\n "
	@g++ -g -Wall -std=c++17 -o $@ $(OBJDIR)/*.o
	@printf "%b" "$(SUCCESS_COLOR)"Compilation_proccess_successfull"$(NO_COLOR)\n"	

$(OBJDIR)/%.o:$(SRCDIR)/%.cpp
	@printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(^)$(NO_COLOR)\n "
	@g++ -g -Wall -std=c++17 -o $@ -c $^ -I .
	@printf "%b" "$(SUCCESS_COLOR)$(COM_END)$(NO_COLOR)\n"; \

clean:
	@rm -f $(RELEASEFOLDER)$(PROGRAM)
	@rm -f $(OBJECTS)

cleancorpus:
	@rm -f data/agnostic/*
	@rm -f data/kern/*

mkdir:
	@mkdir -p bin
	@mkdir -p bin/obj
	@mkdir -p data
	@mkdir -p data/agnostic
	@mkdir -p data/kern

info:
	$(info $(SOURCES))									
	$(info $(OBJECTS))