C++IncludeFlags = -I src/headers -I SDL/include/SDL2
C++LibFlags = -L SDL/lib -l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
ProgramName = main
# Finds all .cpp files, and makes a string with the cpp file's original name, but with the .o extension
ObjectFiles = $(patsubst %.cpp, %.o, $(wildcard src/*.cpp))

# Tells make to look for the .cpp files in src
vpath %.cpp src
# Tells make to look for the .h files in src/headers
vpath %.h src/headers 

# Uses the ObjectFiles list as a dependency, linking all .o files into one executable
$(ProgramName): $(ObjectFiles)
	@g++ $^ -o bin/$(ProgramName) $(C++IncludeFlags) $(C++LibFlags)

# Compiling all the .cpp files into .o files
%.o: %.cpp
	@g++ -c $^ -o $@ $(C++IncludeFlags) $(C++LibFlags)

# Replace "src/" to "src\" for all the file names
clean: $(subst src/, src\, $(ObjectFiles))
	@del $^