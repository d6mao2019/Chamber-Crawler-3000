CXX = g++                   # compiler
CXXFLAGS = -std=c++14 -g -Wall -MMD # compiler flags
OBJECTS = character.o enemy.o player.o enemy_generator.o floor.o potion.o main.o    # object files for the executable
EXEC = cc3k                 # executable name
DEPENDS = ${OBJECTS:.o=.d}  # substitute ".o" with ".d"

########## Targets ##########

.PHONY : all clean          # not file names

${EXEC} : ${OBJECTS}                # link step executable
	${CXX} ${CXXFLAGS} $^ -o $@     # additional object files before $^

-include ${DEPENDS}         # include *.d files containing program dependences

clean :                     # remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC} 