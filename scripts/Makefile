C++IncludeFlags = -std=c++17 -I include -I SDL/include/SDL2
C++LibFlags = -L SDL/lib -l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
ProgramName = main
# Finds all .cpp files, and makes a string with the cpp file's original name, but with the .o extension
# Replace the "src/" in the file name with "bin/obj/"
ObjectFiles = $(subst src/, build/obj/, $(patsubst %.cpp, %.o, $(wildcard src/*.cpp)))
# Replace the "src/ui" in the file name with "bin/obj/"
ObjectFiles += $(subst src/ui/, build/obj/, $(patsubst %.cpp, %.o, $(wildcard src/ui/*.cpp)))

# Tells make to look for the .cpp files in src and src/ui
vpath %.cpp src src/ui

# Compiling all the .cpp files into .o files
build/obj/%.o: %.cpp
	@g++ -c $^ -o $@ $(C++IncludeFlags) $(C++LibFlags)

# Uses the ObjectFiles list as a dependency, linking all .o files into one executable
build/bin/$(ProgramName): $(ObjectFiles)
	@g++ $^ -o $@.exe $(C++IncludeFlags) $(C++LibFlags)