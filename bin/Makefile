C++IncludeFlags = -I src/include -I SDL/include/SDL2
C++LibFlags = -L SDL/lib -l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
ProgramName = main
# Finds all .cpp files, and makes a string with the cpp file's original name, but with the .o extension
.oFiles = $(patsubst %.cpp, %.o, $(wildcard src/*.cpp))
ObjectFiles = $(subst src/, bin/obj/, $(.oFiles))

# Tells make to look for the .cpp files in src
vpath %.cpp src
# Tells make to look for the .h files in src/include
vpath %.h src/include

# Compiling all the .cpp files into .o files
bin/obj/%.o: %.cpp
	@g++ -c $^ -o $@ $(C++IncludeFlags) $(C++LibFlags)

# Uses the ObjectFiles list as a dependency, linking all .o files into one executable
bin/$(ProgramName): $(ObjectFiles)
	@g++ $^ -o $@.exe $(C++IncludeFlags) $(C++LibFlags)

# Replace "bin/obj/" to "bin\obj\" for all the .o file names, then deleting the .o files
clean: $(subst bin/obj/, bin\obj\, $(ObjectFiles))
	@del $^